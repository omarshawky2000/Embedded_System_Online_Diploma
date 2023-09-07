/*
 *      Omar_Types.h
 *
 *      Created on: Jul 27, 2023
 *      Author: Omar Shawky
 */

 #ifndef OMAR_TYPES_H_
 #define OMAR_TYPES_H_

 #define CPU_TYPE       CPU_TYPE_32
 #define CPU_Bit_Order  MSB_First
 #define CPY_Byte_Order Highest_Byte_first

 #ifndef _BOOL
 #define _BOOL unsigned char
 #endif

 #ifndef FALSE
 #define FALSE (boolean) false
 #endif

 #ifndef TRUE
 #define TRUE  (boolean) true
 #endif

 typedef signed char              int8_t;
 typedef signed short             int16_t;
 typedef signed int               int32_t;
 typedef signed long long         int64_t;

 typedef unsigned char            uint8_t;
 typedef unsigned short           uint16_t;
 typedef unsigned int             uint32_t;
 typedef unsigned long long       uint64_t;

 typedef _BOOL                    boolean;
 typedef char                     char_t;
 typedef int8_t                   sint8;
 typedef int16_t                  sint16;
 typedef int32_t                  sint32;
 typedef int64_t                  sint64;
 typedef uint8_t                  uint8;
 typedef uint16_t                 uint16;
 typedef uint32_t                 uint32;
 typedef uint64_t                 uint64;

 typedef volatile int8_t          vsint8;
 typedef volatile uint8_t         vuint8;

 typedef volatile int16_t         vsint16;
 typedef volatile uint16_t        vuint16;

 typedef volatile int32_t         vsint32;
 typedef volatile uint32_t        vuint32;

 typedef volatile int64_t         vsint64;
 typedef volatile uint64_t        vuint64;

 #endif /* OMAR_TYPES_H_ */

