	.cpu arm926ej-s
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"app.c"
	.global	Buffer
	.data
	.align	2
	.type	Buffer, %object
	.size	Buffer, 100
Buffer:
	.ascii	"Omar Shawky\000"
	.space	88
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	ldr	r0, .L2
	bl	UART_Send_String
	ldmfd	sp!, {fp, pc}
.L3:
	.align	2
.L2:
	.word	Buffer
	.size	main, .-main
	.ident	"GCC: (GNU) 4.7.2"
