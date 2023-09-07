/* Omar Shawky startup.s code for cortex m3 */


/* SRAM begins at 0x20000000 (The next section will define the addresses for each handler for the vector table )*/
.section .vectors			/* Defining a section called .vectors */
/*---------------------------------------------------------------------------------- */
.word   0x20001000  		/* 00-   stack top     */
.word _reset				/* 01-    Reset 	   */
.word _Vector_handler		/* 02-     NMI   	   */
.word _Vector_handler		/* 03-  Hardware Fault */
.word _Vector_handler		/* 04-   MM Fault	   */
.word _Vector_handler		/* 05-   Bus Fault	   */
.word _Vector_handler		/* 06-  Usage Fault    */
.word _Vector_handler		/* 07- 	  RESERVED	   */
.word _Vector_handler		/* 08- 	  RESERVED	   */
.word _Vector_handler		/* 09- 	  RESERVED	   */
.word _Vector_handler		/* 10- 	  RESERVED	   */
.word _Vector_handler		/* 11- 	   SV Call	   */
.word _Vector_handler		/* 12-  Debug Reserved */
.word _Vector_handler		/* 13-    RESERVED     */
.word _Vector_handler		/* 14-     PendSV      */
.word _Vector_handler		/* 15-     Systick     */
.word _Vector_handler		/* 15-      IRQ_0      */
.word _Vector_handler		/* 15-      IRQ_1      */
.word _Vector_handler		/* 15-      IRQ_2      */
.word _Vector_handler		/* 15-      IRQ_3      */
.word _Vector_handler		/* 15-      IRQ_4      */

/*on to IRQ_67 */
/*---------------------------------------------------------------------------------- */

/*(The next section will define the symbols and the functionallity of each handler of the vector table ) */

.section .text				/* Defining a section called .text */
/*---------------------------------------------------------------------------------- */
_reset:
	bl	main
	b	.
.thumb_func
_Vector_handler:
	b 	_reset
