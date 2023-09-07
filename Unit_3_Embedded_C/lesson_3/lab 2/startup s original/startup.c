//Startup.c
//Eng. Omar Shawky

#include <stdint.h>
#define STACK_START_SP   (uint32_t) 0x20001000

void Reset_Handler();
void NMI_Handler();
void H_fault_Handler();
void MM_fault_Handler();
void BUS_fault_Handler();
void Usage_fault_Handler();

uint32_t vectors[] __attribute__((section(".vectors")))={
    STACK_START_SP,
    (uint32_t)  &Reset_Handler,
    (uint32_t)  &NMI_Handler,
    (uint32_t)  &H_fault_Handler,
    (uint32_t)  &MM_fault_Handler,
    (uint32_t)  &BUS_fault_Handler,
    (uint32_t)  &Usage_fault_Handler
};

void Reset_Handler()
{
    main();
}

void NMI_Handler()
{
    Reset_Handler();
}

void H_fault_Handler()
{
    Reset_Handler();
}

void MM_fault_Handler()
{
    Reset_Handler();
}

void BUS_fault_Handler()
{
    Reset_Handler();
}

void Usage_fault_Handler()
{
    Reset_Handler();
}