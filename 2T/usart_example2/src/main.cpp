// VECT_TAB_SRAM
// The symbol VECT_TAB_SRAM needs to be defined when building the project
// if code has been located to RAM and interrupts are used.

#include <stm32f10x.h>
#include <string.h>

// ����� ������������ ���������� UART2 ���������������� STM32F100RB.
// ���� �� ������������ �������������� �������, �� ���
// ����������� ������������ (�� FT-������):
// TX: PA2 (pin 16 ��� ������� LQFP64);
// RX: PA3 (pin 17 ��� ������� LQFP64).

// ������������ ��������� USART: 8 ��� ������ �� ������;
// ��� �������� ��������; 1 ����-���; 16-������� ������������
// (��� OVER8=0).

// �������� �������� ������:
#define BAUD_RATE 2400

// ����� ��� ������������ ����� USART �����.
const uint32_t tbuf_size=16;
char tbuf[tbuf_size];
// ������� ���������� ������������� ������� � ������;
// -1 - � ������ ��� ������ ��� ��������.
volatile int tpos=-1;

// ������� ��� �������� ������ (�������� ������
// � ����� �������� � ���������� ������� ��������).
// ���������� ����� ���������� � ����� ������ (�������� ����������� 0).
// ���� ����� �� ����, ����� �� �������������� �
// ������� ����� ���������� 0.
// ���� ������ ������� ������� ��� ������, ��� ���������.
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
	// ��������� ���������� � ������ ������� ��������
	// ������������ ������.
	USART2->CR1|=USART_CR1_TXEIE;
	return len+1;
}

// ������� ��� ��������� ������� - ��������� ������.
void on_receive_str(const char *str)
{
	if(strcmpi(str, "Hello, MCU!")==0)
		send_str("Hello, PC!");
	else
		send_str("Aha!");
}

extern "C" void USART2_IRQHandler()
{
	// � ���� ������� ���������� �� ������� ���������
	// ��������� ��������.

	// ����� ��� ����������� ������ � ��������� ������� ������� � ��.
	const uint32_t rbuf_size=16;
	static char rbuf[rbuf_size];
	static uint32_t pos=0;

	uint16_t sr=USART2->SR;

	if(sr&USART_SR_RXNE) // ������ ������.
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

	if(sr&USART_SR_TXE) // ���� ����������� ��������� ������.
	{
		// ���� ������ ����������, ��������� ��������� ����������
		// ��� ������ �������� ������������ ������.
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
	// �������� �������� ������ ��� ������������ ���������.
	RCC->APB1ENR|=RCC_APB1ENR_USART2EN;
	RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;

	// �������� USART (��� USART_CR1_UE=1);
	// ���������� ����� ������ 8 ��� (��� USART_CR1_M=0);
	// ���������� 1 ����-��� (���� USART_CR2_STOP=00).
	USART2->CR1=USART_CR1_UE;

	// ����� �������� �������� (� �����) � ������ �������������
	// �� ��������� �������� ���� OVER8=0.
	USART2->BRR=SystemCoreClock/BAUD_RATE;

	// �������� ���������� USART.
	USART2->CR1|=USART_CR1_TE;

	// ����� TX (PA2) - push-pull ����� ��� �������������� �������:
	// MODE: bx10 (����� �� 2 ���), CNF: bx10 (push-pull, alt).

	// ���� RX (PA3) - �������� ���� � ������������� � ��������
	// ������ ����������: MODE: bx00 (����);
	// CNF: bx10 (� ������������� ����������); GPIO_ODR_ODR3=1 (� �������� ������).
	GPIOA->BSRR=GPIO_BSRR_BS3;
	uint32_t mask=~(GPIO_CRL_MODE2|GPIO_CRL_CNF2|
			GPIO_CRL_MODE3|GPIO_CRL_CNF3);
	GPIOA->CRL=GPIOA->CRL&mask|
			(GPIO_CRL_MODE2_1|GPIO_CRL_CNF2_1|
					GPIO_CRL_CNF3_1);

	// ����������� ���������� ����������:
	// ����� ��������� ���������� (������������� �����������
	// ��� ������� ����������) � ��������� ��������� ����������
	// �� USART2.
	NVIC_SetPriority (USART2_IRQn, (1<<__NVIC_PRIO_BITS) - 1);
	NVIC_EnableIRQ(USART2_IRQn);

	// �������� ������� � ��������� ���������� ��� ��������� �������.
	USART2->CR1|=USART_CR1_RE|USART_CR1_RXNEIE;

	while(true);
}
