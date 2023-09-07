//Learn in depth (TIVA C Project) 
//Copyrights Omar Shawky
#include "stdint.h"
typedef volatile unsigned long vuint32_t;
//Register addresses
#define SYSCTL_BASE		0x400FE000
#define GPIO_BASE		0x40025000
#define SYSCTL_RCGC2_R				*(volatile uint32_t *)(	SYSCTL_BASE+	0x108)
#define GPIO_PORTF_DEN_R			*(volatile uint32_t *)(	GPIO_BASE  +	0x51C)
#define GPIO_PORTF_DIR_R			*(volatile uint32_t *)(	GPIO_BASE  +	0x400)
#define GPIO_PORTF_DATA_R			*(volatile uint32_t *)(	GPIO_BASE  +	0x3FC)
//Bit fields
#define RCC_PORTF				(1<<5)
#define	GPIO_PORTF_PIN3			(1<<3)

unsigned char g_variables[3] = {1,2,3};
unsigned char const const_variables[3] = {1,2,3};

typedef union{
	vuint32_t	ALL_FIELDS;
	struct{
		vuint32_t	RESERVED:2;
		vuint32_t	P_3:1;
	} PIN;
} R_PORTF_DEN_t;

typedef union{
	vuint32_t	ALL_FIELDS;
	struct{
		vuint32_t	RESERVED:2;
		vuint32_t	P_3:1;
	} PIN;
} R_PORTF_DIR_t;

typedef union{
	vuint32_t	ALL_FIELDS;
	struct{
		vuint32_t	RESERVED:13;
		vuint32_t	P_3:1;
	} PIN;
} R_PORTF_DATA_t;

volatile R_PORTF_DEN_t  * R_PORTF_DEN  = (volatile R_PORTF_DEN_t*)  (GPIO_BASE  +	0x51C);
volatile R_PORTF_DIR_t  * R_PORTF_DIR  = (volatile R_PORTF_DIR_t*)  (GPIO_BASE  +	0x400);
volatile R_PORTF_DATA_t * R_PORTF_DATA = (volatile R_PORTF_DATA_t*) (GPIO_BASE  +	0x3FC);

void main(void)
{	
	SYSCTL_RCGC2_R |= RCC_PORTF;
	//Make sure the PortF is ready
	for(volatile int i = 0 ; i <= 5000 ; i++);		//Arbitrary delay
	R_PORTF_DEN->PIN.P_3	=	1;					//Enable the Digital functionallity pin 
	R_PORTF_DIR->PIN.P_3	=	1;					//Make the direction of the pin OUTPUT
	while(1){
	R_PORTF_DATA->PIN.P_3	=	1;					
	for(int i = 0 ; i <= 5000 ; i++);				//Arbitrary delay
	R_PORTF_DATA->PIN.P_3	=	0;
	for(int i = 0 ; i <= 5000 ; i++);				//Arbitrary delay
	}
}
