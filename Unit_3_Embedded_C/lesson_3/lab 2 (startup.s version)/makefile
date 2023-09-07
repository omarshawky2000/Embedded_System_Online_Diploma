#Copyright Omar Shawky
#---------------------------------------------------------#
#Define target name
Target_Name = learn_in_depth_cortex_m3
#Define the cross-toolchain	
CC=arm-none-eabi-
#Define the flags for the cross-toolchain (Debugging info enabled , processor specified)				
CFLAGS = -g -mcpu=cortex-m3 -mthumb
#Define the includes
INCS = -I.
#Define the libraries
LIBS =				
#---------------------------------------------------------#
#Get all .c files inside the folder 
SRC = $(wildcard *.c)
#Get all .s files inside the folder 
ASM = $(wildcard *.s)
#Get all .c and convert it to .o
OBJ = $(SRC:.c=.o)
#Get all .S and convert it to .o
OBJASM = $(ASM:.s=.o)
#---------------------------------------------------------#
#Build all
all: $(Target_Name).bin
	@echo "==========BUILD IS DONE=========="

#Assemble .o file from .s files
%.o: %.s
	$(CC)as.exe  $(CFLAGS)  $< -o $@

#Compile .o file from .c files
%.o: %.c
	$(CC)gcc.exe -c  $(CFLAGS) $(INCS) $< -o $@

#Link all files with the linkerscript
$(Target_Name).elf:  $(OBJ) $(OBJASM)
	$(CC)ld.exe  -T  linkerscript.ld $(OBJ) $(OBJASM) $(LIBS) -o $@

#Get the binary image of the .elf output
$(Target_Name).bin: $(Target_Name).elf
	$(CC)objcopy.exe  -O binary  $< $(Target_Name).bin
#---------------------------------------------------------#
#Clean the previous build
clean_all: 
	rm *.o
	rm *.elf
	rm *.bin
clean:
	rm *.elf 
	rm *.bin

