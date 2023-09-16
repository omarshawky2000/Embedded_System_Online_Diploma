/*
	main.c for Atmega32 Interrupt Lab3
	Eng. Omar Shawky
*/

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define IO_BASE 	0x20

//Interrupt Registers
#define MCU_CR 		*(volatile uint32_t *) (IO_BASE + 0x35)
#define MCU_CSR 	*(volatile uint32_t *) (IO_BASE + 0x34)
#define GICR 		*(volatile uint32_t *) (IO_BASE + 0x3B)

//Port Registers
#define PORTD 		*(volatile uint32_t *) (IO_BASE + 0x12)
#define DDRD 		*(volatile uint32_t *) (IO_BASE + 0x11)

void GPIO_init(void){

	//Set PortD-Bit5:7 as output
	DDRD |= (0b111<<5);
}

void INTX_init(void){

	//Configure INT0 to request IRQ when any Logical change occur (bit0)
	//Configure INT1 to request IRQ when on Rising edge (bit3:2)
	MCU_CR |= (0b1101<<0);

	//Configure INT2 to request IRQ when on Falling edge (bit6)
	MCU_CSR |= (0<<6);

	//Enable INT0:2
	GICR |= (0b111<<5);
}

int main(void)
{
	GPIO_init();

	INTX_init();

	// Global interrupt enable
    sei();

	while(1){
		//Clear PortD-Bit5:7
		PORTD |= (0b000<<5);
	}

	return 0;
}

ISR(INT0_vect){
	PORTD |= (1<<5);
	_delay_ms(1000);
}

ISR(INT1_vect){
	PORTD |= (1<<6);
	_delay_ms(1000);
}

ISR(INT2_vect){
	PORTD |= (1<<7);
	_delay_ms(1000);
}