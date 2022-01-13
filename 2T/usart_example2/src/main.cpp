// VECT_TAB_SRAM
// The symbol VECT_TAB_SRAM needs to be defined when building the project
// if code has been located to RAM and interrupts are used.

#include <stm32f10x.h>
#include <string.h>

// Будем использовать устройство UART2 микроконтроллера STM32F100RB.
// Если не использовать переназначения выводов, то для
// подключения используются (не FT-выводы):
// TX: PA2 (pin 16 для корпуса LQFP64);
// RX: PA3 (pin 17 для корпуса LQFP64).

// Используются настройки USART: 8 бит данных во фрейме;
// без контроля чётности; 1 стоп-бит; 16-кратный оверсэмплинг
// (бит OVER8=0).

// Скорость передачи данных:
#define BAUD_RATE 2400

// Буфер для отправляемых через USART строк.
const uint32_t tbuf_size=16;
char tbuf[tbuf_size];
// Позиция очередного передаваемого символа в буфере;
// -1 - в буфере нет данных для передачи.
volatile int tpos=-1;

// Функция для отправки строки (помещает строку
// в буфер передачи и настравает позицию передачи).
// Возвращает объём помещённых в буфер данных (учитывая завершающий 0).
// Если буфер не пуст, буфер не модифицируется и
// функция сразу возвращает 0.
// Если строка слишком длинная для буфера, она усекается.
uint32_t send_str(const char *str)
{
	if(tpos>=0)
		return 0;
	uint32_t len=strlen(str);
	if(len>=tbuf_size)
		len=tbuf_size-1;
	memcpy(tbuf, str, len);
	tbuf[len]=0;
	tpos=0;
	// Разрешаем прерывание в случае пустого регистра
	// передаваемых данных.
	USART2->CR1|=USART_CR1_TXEIE;
	return len+1;
}

// Функция для обработки события - получения строки.
void on_receive_str(const char *str)
{
	if(strcmpi(str, "Hello, MCU!")==0)
		send_str("Hello, PC!");
	else
		send_str("Aha!");
}

extern "C" void USART2_IRQHandler()
{
	// В этой функции определённо не хватает обработки
	// ошибочных ситуаций.

	// Буфер для принимаемой строки и указатель текущей позиции в нём.
	const uint32_t rbuf_size=16;
	static char rbuf[rbuf_size];
	static uint32_t pos=0;

	uint16_t sr=USART2->SR;

	if(sr&USART_SR_RXNE) // Принят символ.
	{
		rbuf[pos]=USART2->DR;
		if(pos==rbuf_size-1)
			rbuf[pos]=0;
		if(rbuf[pos]==0)
		{
			pos=0;
			on_receive_str(rbuf);
		}
		else
			pos++;
	}

	if(sr&USART_SR_TXE) // Есть возможность отправить символ.
	{
		// Если нечего передавать, отключаем генерацию прерывания
		// при пустом регистре передаваемых данных.
		if(tpos<0)
			USART2->CR1&=~USART_CR1_TXEIE;
		else
		{
			USART2->DR=tbuf[tpos];
			if(tbuf[tpos]==0)
				tpos=-1;
			else
				tpos++;
		}
	}
}

int main()
{
	// Включаем тактовый сигнал для используемых устройств.
	RCC->APB1ENR|=RCC_APB1ENR_USART2EN;
	RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;

	// Включаем USART (бит USART_CR1_UE=1);
	// используем слово длиной 8 бит (бит USART_CR1_M=0);
	// используем 1 стоп-бит (биты USART_CR2_STOP=00).
	USART2->CR1=USART_CR1_UE;

	// Задаём скорость передачи (и приёма) с учётом используемого
	// по умолчанию значения бита OVER8=0.
	USART2->BRR=SystemCoreClock/BAUD_RATE;

	// Включаем передатчик USART.
	USART2->CR1|=USART_CR1_TE;

	// Выход TX (PA2) - push-pull выход для альтернативной функции:
	// MODE: bx10 (выход до 2 МГц), CNF: bx10 (push-pull, alt).

	// Вход RX (PA3) - цифровой вход с подтягивающим к высокому
	// уровню резистором: MODE: bx00 (вход);
	// CNF: bx10 (с подтягивающим резистором); GPIO_ODR_ODR3=1 (к высокому уровню).
	GPIOA->BSRR=GPIO_BSRR_BS3;
	uint32_t mask=~(GPIO_CRL_MODE2|GPIO_CRL_CNF2|
			GPIO_CRL_MODE3|GPIO_CRL_CNF3);
	GPIOA->CRL=GPIOA->CRL&mask|
			(GPIO_CRL_MODE2_1|GPIO_CRL_CNF2_1|
					GPIO_CRL_CNF3_1);

	// Настраиваем контроллер исключений:
	// задаём приоритет прерывания (устанавливаем минимальный
	// для данного процессора) и разрешаем обработку прерывания
	// от USART2.
	NVIC_SetPriority (USART2_IRQn, (1<<__NVIC_PRIO_BITS) - 1);
	NVIC_EnableIRQ(USART2_IRQn);

	// Включаем приёмник и разрешаем прерывание при получении символа.
	USART2->CR1|=USART_CR1_RE|USART_CR1_RXNEIE;

	while(true);
}
