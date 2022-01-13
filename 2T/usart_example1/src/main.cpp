// VECT_TAB_SRAM
// The symbol VECT_TAB_SRAM needs to be defined when building the project
// if code has been located to RAM and interrupts are used.

#include <stm32f10x.h>

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

extern "C" void USART2_IRQHandler()
{
	// � ���� ������� ���������� �� ������� ���������
	// ��������� ��������.

	if(USART2->SR&USART_SR_RXNE) // ���� ���� �������...
	{
		// ������ ���������� ����.
		char d=~USART2->DR;
		// ���� ������� ��� ������������ ������ �� ����,
		// ��� ���� �� �����������.
		while((USART2->SR&USART_SR_TXE)==0) {}
		// ���������� ��������������� ���������� ����.
		USART2->DR=d;
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
