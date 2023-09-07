//Startup.c
//Eng. Omar Shawky

#include <stdint.h>
#define STACK_SIZE  256
extern void main(void);
void Reset_Handler();

void Default_Handler(){
	Reset_Handler();
}

// Booking 1024 Byte in the bss by making an array of size (size of long "4 bytes")*256 = 1024 byte
static unsigned long _STACK[STACK_SIZE] ;

void NMI_Handler()__attribute__((weak ,alias("Default_Handler")));
void H_fault_Handler()__attribute__((weak ,alias("Default_Handler")));
void MM_fault_Handler()__attribute__((weak ,alias("Default_Handler")));
void BUS_fault_Handler()__attribute__((weak ,alias("Default_Handler")));
void Usage_fault_Handler()__attribute__((weak ,alias("Default_Handler")));

void(* const g_p_fn_Vector[])() __attribute__((section(".vectors"))) = 
 {
    (void(*)())  _STACK + STACK_SIZE ,
    &Reset_Handler,
    &NMI_Handler,
    &H_fault_Handler,
    &MM_fault_Handler,
    &BUS_fault_Handler,
    &Usage_fault_Handler
 };

extern uint32_t _E_TEXT ; 
extern uint32_t _S_DATA ;
extern uint32_t _E_DATA ;
extern uint32_t _S_BSS ;
extern uint32_t _E_BSS ;

void Reset_Handler()
{
    //copy data from flash to ram
    uint32_t DATA_SIZE = (unsigned char*)&_E_DATA  -  (unsigned char*)&_S_DATA ;
    unsigned char * P_src  = (unsigned char*)&_E_TEXT;
    unsigned char * P_dest = (unsigned char*)&_S_DATA;
    for(int i = 0 ; i < DATA_SIZE ; i++){
        *((unsigned char*)P_dest++) = *((unsigned char*)P_src++);
    }
    
    //initialize .bss section in sram with zeros
    uint32_t BSS_SIZE = (unsigned char*)&_E_BSS  -  (unsigned char*)&_S_BSS ;
    P_dest = (unsigned char*)&_S_BSS;
    for(int i = 0 ; i < BSS_SIZE ; i++){
        *((unsigned char*)P_dest++) = (unsigned char) 0;
    }
    //Jump to main
    main();
}

