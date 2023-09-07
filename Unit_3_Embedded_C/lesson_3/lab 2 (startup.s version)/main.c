//Learn in depth
//Copyrights Omar Shawky
#include "stdint.h"
typedef volatile unsigned int vuint32_t;
//Register addresses
#define RCC_BASE		0x40021000
#define GPIO_BASE		0x40010800
#define RCC_APB2ENR		*(volatile uint32_t *)(	RCC_BASE+	0x18)
#define GPIO_CRH		*(volatile uint32_t *)(	GPIO_BASE+	0x04)
#define GPIO_ODR		*(volatile uint32_t *)(	GPIO_BASE+	0x0C)
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

void main(void)
{	
	RCC_APB2ENR |= RCC_IOPAEN;
	GPIO_CRH    &= 0xFF0FFFFF;
	GPIO_CRH    |= 0x00200000;
	int i;
	while(1){
	R_ODR->PIN.P_13	=	1;					
	for(i = 0 ; i <= 5000 ; i++);		//Arbitrary delay
	R_ODR->PIN.P_13	=	0;
	for(i = 0 ; i <= 5000 ; i++);		//Arbitrary delay
	}
}
