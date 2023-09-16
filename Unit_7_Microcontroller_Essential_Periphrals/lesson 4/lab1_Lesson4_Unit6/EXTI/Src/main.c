//Learn in depth
//Copyrights Omar Shawky
#include "stdint.h"
typedef volatile unsigned int vuint32_t;
//Register addresses

//NVIC Registers
#define NVIC_BASE		0xE000E100
#define NVIC_EXTIE0		*(volatile uint32_t *)(	NVIC_BASE+	0x00)

//GPIO Registers
#define GPIO_BASE		0x40010800
#define GPIO_CRL		*(volatile uint32_t *)(	GPIO_BASE+	0x00)
#define GPIO_CRH		*(volatile uint32_t *)(	GPIO_BASE+	0x04)
#define GPIO_ODR		*(volatile uint32_t *)(	GPIO_BASE+	0x0C)


//AFIO Registers
#define AFIO_BASE		0x40010000
#define AFIO_EXTICR1	*(volatile uint32_t *)(	AFIO_BASE+	0x08)

//RCC Registers
#define RCC_BASE		0x40021000
#define RCC_CFGR		*(volatile uint32_t *)(	RCC_BASE+	0x04)
#define RCC_APB2ENR		*(volatile uint32_t *)(	RCC_BASE+	0x18)


//EXTI Registers
#define EXTI_BASE		0x40010400
#define EXTI_IMR		*(volatile uint32_t *)(	EXTI_BASE+	0x00)
#define EXTI_RTSR		*(volatile uint32_t *)(	EXTI_BASE+	0x08)
#define EXTI_PR			*(volatile uint32_t *)(	EXTI_BASE+	0x14)

//Bit fields
#define RCC_IOPAEN		(1<<2)
#define	GPIOA13			(1UL<<13)

unsigned char g_variables[3] = {1,2,3};
unsigned char const const_variables[3] = {1,2,3};

typedef union{
	vuint32_t	ALL_FIELDS;
	struct{
		vuint32_t	RESERVED:13;
		vuint32_t	P_13:1;
	} PIN;
} R_ODR_t;

volatile R_ODR_t* R_ODR = (volatile R_ODR_t*)(	GPIO_BASE+	0x0C);

void clock_init(void)
{
	//Set prescaler to APB2 (4)
	RCC_CFGR |= (0b101 < 11);
	//Set prescaler to APB1 (2)
	RCC_CFGR |= (0b100 < 8);


}

void gpio_init(void)
{
	RCC_APB2ENR |= RCC_IOPAEN;

	GPIO_CRH    &= 0xFF0FFFFF;
	GPIO_CRH    |= 0x00200000;
	//pin A0 input floating (reset state)
	GPIO_CRL |= (1<<2);

}
void EXTI0_init(void)
{
	//Initialize EXTI

	//Enable EXTI Line 0 (Mask 1)
	EXTI_IMR |= 1;

	//Enable Rising Edge
	EXTI_RTSR |= 1;

	//EXTI0 configuration to PortA0
	AFIO_EXTICR1 = 0 ;

	//Enable the RCC for the AFIO
	RCC_APB2ENR |= (1<0);

	//Enable NVIC EXTI0 Mask
	NVIC_EXTIE0 |= (1<<6);

}
void EXTI0_IRQHandler(void)
{
	//IRQ is Happened EXTI0 >>>> PORT A PIN 0 _|- rising edge
	//toggle Led pin A13
	GPIO_ODR ^= 0x1;
	//clear Pending request for line 0
	EXTI_PR |= 0x1;
}

void main(void)
{
	clock_init();
	gpio_init();
	EXTI0_init();
	//Enable EXTI Line 0 (Mask 1)

	while(1);

}
