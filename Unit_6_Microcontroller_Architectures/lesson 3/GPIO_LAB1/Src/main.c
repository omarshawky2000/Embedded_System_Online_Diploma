//Learn in depth
//Copyrights Omar Shawky
#include "stdint.h"
typedef volatile unsigned int vuint32_t;
//Register addresses

//NVIC Registers
#define NVIC_BASE		0xE000E100
#define NVIC_EXTIE0		*(volatile uint32_t *)(	NVIC_BASE+	0x00)

//GPIO Registers
#define GPIOA_BASE		0x40010800
#define GPIOA_CRL		*(volatile uint32_t *)(	GPIOA_BASE+	0x00)
#define GPIOA_CRH		*(volatile uint32_t *)(	GPIOA_BASE+	0x04)
#define GPIOA_ODR		*(volatile uint32_t *)(	GPIOA_BASE+	0x0C)
#define GPIOA_IDR		*(volatile uint32_t *)(	GPIOA_BASE+	0x08)
#define	GPIOA13			(1UL<<13)

#define GPIOB_BASE		0x40010C00
#define GPIOB_CRL		*(volatile uint32_t *)(	GPIOB_BASE+	0x00)
#define GPIOB_CRH		*(volatile uint32_t *)(	GPIOB_BASE+	0x04)
#define GPIOB_ODR		*(volatile uint32_t *)(	GPIOB_BASE+	0x0C)
#define GPIOB_IDR		*(volatile uint32_t *)(	GPIOB_BASE+	0x08)


//RCC Registers
#define RCC_BASE		0x40021000
#define RCC_CFGR		*(volatile uint32_t *)(	RCC_BASE+	0x04)
#define RCC_APB2ENR		*(volatile uint32_t *)(	RCC_BASE+	0x18)


//Bit fields
#define RCC_IOPAEN		(1<<2)
#define RCC_IOPBEN		(1<<3)



void clock_init(void)
{
	//Set prescaler to APB2 (4)
	RCC_CFGR |= (0b101 < 11);
	//Set prescaler to APB1 (2)
	RCC_CFGR |= (0b100 < 8);


}

void gpio_init(void)
{
	//Enable Port A
	RCC_APB2ENR |= RCC_IOPAEN;
	//Enable Port B
	RCC_APB2ENR |= RCC_IOPBEN;

	//PA1 input HighZ
	GPIOA_CRL |= 1 << 6;

	//PB1 output push pull mode
	//CNF 00: General purpose output push pull
	GPIOB_CRL &= ~(0b11 << 6);
	// 01: Output mode max speed 10 MHz.
	GPIOB_CRL |=  (0b01 << 4);

	//PA13 input HighZ
	GPIOA_CRH &= ~(0b11 << 20);
	GPIOA_CRH |=  (0b01 << 22);

	//PB13 output push pull mode
	GPIOB_CRH &= ~(0b01 << 20);
	GPIOB_CRH |=  (0b11 << 22);
}


void main(void)
{
	clock_init();
	gpio_init();
	//Enable EXTI Line 0 (Mask 1)

	while(1)
	{
		// Check on PA1 >> connected to external PUR
		if(((GPIOA_IDR &(1<<1))>>1) == 0)
		{
			GPIOB_ODR ^= 1<<1;
			while (((GPIOA_IDR &(1<<1))>>1) == 0); //single press
		}

		// Check on PA13 >> connected to external PDR
		if(((GPIOA_IDR &(1<<13))>>13) == 1)
		{
			GPIOB_ODR ^= 1<<13;
			//delay
			for(int i = 0; i < 400000; i++);
		}
	}

}