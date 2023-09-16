/* Linker script Cortex M3
Eng. Omar Shawky */

MEMORY
{
    flash(RX): ORIGIN = 0x08000000 , LENGTH = 128K  /*Define flash memory from address 0x08000000 with length 128K READ ONLY*/
    sram(RWX): ORIGIN = 0x20000000 , LENGTH = 20K   /*Define sram  memory from address 0x20000000 with length 20k  READ WRITE*/
}

SECTIONS
{  
    .text :{    /*output a section called .text*/
            *(.vectors*)    /*take input called .vectors section found in any .o file */
            *(.rodata)      /*take input called .rodata  section found in any .o file */
            *(.text*)       /*take input called .text    section found in any .o file */
            _E_TEXT = . ;   /*save the current location to the variable name _E_TEXT  */
    } > flash               /*put the output section in the memory defined as flash in both runtime and loadtime*/
    
    .data :{    /*output a section called .data*/
            _S_DATA = . ;   /*save the current location to the variable name _S_DATA  */
            *(.data)        /*take input called .data section found in any .o file */
            . = ALIGN(4);   /*Align the counter to a 4 byte address*/
            _E_DATA = . ;   /*save the current location to the variable name _E_DATA  */
    } > sram AT> flash      /*put the output section in the memory defined as flash loadtime then copy it to flash at runtime*/

    .bss  :{    /*output a section called .text*/
            _S_BSS = . ;    /*save the current location to the variable name _S_BSS  */
            *(.bss)         /*take input called .bss section found in any .o file */
            _E_BSS = . ;    /*save the current location to the variable name _E_BSS  */
            . = ALIGN(4);   /*Align the counter to a 4 byte address*/
            . = . + 0x1000; /*Increment the counter by the stack size*/
            _STACK_TOP = .;
    } > sram                /*put the output section in the memory defined as sram in both runtime and loadtime*/
}