/*
 * Stm32_F103C6_GPIO_Driver.c
 *
 *  Created on: Sep 26, 2023
 *      Author: omar pc
 */
 #include "Data_Manipulation.h"

 //========================================================================
 //								   APIs
 //========================================================================
/* =================================================================
 * @FN			- _WriteByte
 * @Brief		- Helper Function to write a byte at once in a register
 * @param(in)	- Address: the base address of the register
 * @param(in)	- Offset: the offset of the byte to write onto (0,1,2,3)
 * @param(in)	- Byte: the byte to be written on the register
 * @retval		- NONE
 * Note-		- NONE
 * =================================================================
 */
void _WriteByte (uint32_t* address , uint8_t offset , uint8_t byte)
{
    if(offset > 3){return;}
    * ((uint8_t*)(address)+offset) = byte;
}
/* =================================================================
 * @FN			- _WriteWord
 * @Brief		- Helper Function to write a Word at once in a register
 * @param(in)	- Address: the base address of the register
 * @param(in)	- Word: the word to be written on the register
 * @retval		- NONE
 * Note-		- NONE
 * =================================================================
 */
void _WriteWord (uint32_t* address , uint32_t word)
{
    *address = word;
}

/* =================================================================
 * @FN			- _WriteHalfByte
 * @Brief		- Helper Function to write a Word at once in a register
 * @param(in)	- Address: the base address of the register
 * @param(in)	- Offset: the offset of the half byte to write onto (0,1,2,3,4,5,6,7)
 * @param(in)	- hbyte: the hbyte to be written on the register
 * @retval		- NONE
 * Note-		- NONE
 * =================================================================
 */
void _WriteHalfByte (uint32_t* address , uint8_t offset , uint8_t hbyte)
{
    uint8_t counter = 0;
	while(counter < 4)
	{
	   //safety
	   if(hbyte>=0x10 || offset > 7){break;}

	   if(hbyte&(1<<counter))
	   {
	       * address |= (1<<((offset*4)+counter));
	   }
	   else
	   {
	       * address &= ~(1<<((offset*4)+counter));
	   }
	   counter ++;
	}
}
/* =================================================================
 * @FN			- _WriteHalfWord
 * @Brief		- Helper Function to write a Word at once in a register
 * @param(in)	- Address: the base address of the register
 * @param(in)	- Offset: the offset of the half word to write onto (0,1)
 * @param(in)	- hword: the half word to be written on the register
 * @retval		- NONE
 * Note-		- NONE
 * =================================================================
 */
void _WriteHalfWord (uint32_t* address , uint8_t offset , uint16_t hword)
{
    if(offset > 1){return;}
    *((uint16_t*)(address)+offset) = hword;
}

/* =================================================================
 * @FN			- _WriteNBits
 * @Brief		- Helper Function to write n number of bits to a register at a certain offset
 * @param(in)	- Address: the base address of the register
 * @param(in)	- Offset: the offset of the byte to write onto (0,1,2,3)
 * @param(in)	- Nbits: the bits written on the register
 * @param(in)	- N: the number of bits to be written on the register
 * @retval		- NONE
 * Note-		- NONE
 * =================================================================
 */
void _WriteNBits (uint32_t* address , uint8_t offset , uint32_t nbits , uint8_t n )
{
    uint8_t counter = 0;
	while(counter < n)
	{
	   if(nbits&(1<<counter))
	   {
	       * address |= (1<<(offset+counter));
	   }
	   else
	   {
	       * address &= ~(1<<(offset+counter));
	   }
	   counter ++;
	}
}
