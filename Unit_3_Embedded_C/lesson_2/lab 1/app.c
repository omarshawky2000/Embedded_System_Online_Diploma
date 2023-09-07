#include "uart.h"

unsigned char Buffer[100] = "Omar Shawky";
const unsigned char Buffer2[100] = "Learn_in_depth";

void main(void)
{
	UART_Send_String(Buffer);
}
