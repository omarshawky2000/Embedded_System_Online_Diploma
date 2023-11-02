/*
 * Stm32_F103C6_GPIO_Driver.h
 *
 *  Created on: Sep 26, 2023
 *      Author: omar pc
 */

#ifndef INC_DATA_MANIPULATION_
#define IINC_DATA_MANIPULATION_


//----------------------------------------------------------
//Includes
//----------------------------------------------------------
#include "stdint.h"

/*
 * ===============================================
 * MACROS Supported by "DATA_MANIPULATION"
 * ===============================================
 */
#define 	SetBit(REG,N)			REG |= 	(1<<N)
#define 	SetHalfByte(REG,N)		REG |= 	(0XF<<(N*4))
#define 	SetByte(REG,N)			REG |= 	(0XFF<<(N*8))
#define 	SetHalfWord(REG,N)		REG |= 	(0XFFFF<<(N*16))
#define 	SetWord(REG)			REG |= 	(0XFFFFFFFF)

#define 	ClearBit(REG,N)			REG &= ~(1<<N)
#define 	ClearHalfByte(REG,N)	REG &= ~(0XF<<(N*4))
#define 	ClearByte(REG,N)		REG &= ~(0XFF<<(N*8))
#define 	ClearHalfWord(REG,N)	REG &= ~(0XFFFF<<(N*16))
#define 	ClearWord(REG)			REG &= ~(0XFFFFFFFF)

#define 	ToggleBit(REG,N)		REG ^= 	(1<<N)
#define 	ToggleHalfByte(REG,N)	REG ^= 	(0XF<<(N*4))
#define 	ToggleByte(REG,N)		REG ^= 	(0XFF<<(N*8))
#define 	ToggleHalfWord(REG,N)	REG ^= 	(0XFFFF<<(N*16))
#define 	ToggleWord(REG)			REG ^= 	(0XFFFFFFFF)

#define 	ReadBit(REG,N)			REG & 	(1<<N)
#define 	ReadHalfByte(REG,N)		REG & 	(0XF<<(N*4))
#define 	ReadByte(REG,N)			REG & 	(0XFF<<(N*8))
#define 	ReadHalfWord(REG,N)		REG & 	(0XFFFF<<(N*16))
#define 	ReadWord(REG)			REG & 	(0XFFFFFFFF)

/*
 * ===============================================
 * APIs Supported by "DATA_MANIPULATION"
 * ===============================================
 */
 void WriteNBits (uint32_t* address , uint8_t offset , uint32_t nbits , uint8_t n );

 void WriteHalfWord (uint32_t* address , uint8_t offset , uint16_t hword);

 void WriteHalfByte (uint32_t* address , uint8_t offset , uint8_t hbyte);

 void WriteWord (uint32_t* address , uint32_t word);

 void WriteByte (uint32_t* address , uint8_t offset , uint8_t byte);



#endif /* INC_STM32_F103C6_GPIO_DRIVER_H_ */
