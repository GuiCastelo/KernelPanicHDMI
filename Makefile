
ARMGNU ?= arm-none-eabi
#ARMGNU ?= arm-linux-gnueabi

AOPS = --warn --fatal-warnings
COPS = -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding

all : kernel.img

clean :
	rm -f *.o
	rm -f *.bin
	rm -f *.hex
	rm -f *.srec
	rm -f *.elf
	rm -f *.list
	rm -f *.img

boot.o : boot.s
	$(ARMGNU)-as $(AOPS) boot.s -o boot.o

fb.o : fb.c
	$(ARMGNU)-gcc $(COPS) -c fb.c -o fb.o

main.o : main.c
	$(ARMGNU)-gcc $(COPS) -c main.c -o main.o

stubs.o : stubs.c
	$(ARMGNU)-gcc $(COPS) -c stubs.c -o stubs.o

hdmi.elf : linker.ld boot.o fb.o main.o stubs.o
	$(ARMGNU)-ld boot.o fb.o main.o stubs.o -T linker.ld -o hdmi.elf -lc -L/usr/lib/arm-none-eabi/newlib
	$(ARMGNU)-objdump -D hdmi.elf > hdmi.list

kernel.img : hdmi.elf
	$(ARMGNU)-objcopy --srec-forceS3 hdmi.elf -O srec hdmi.srec
	$(ARMGNU)-objcopy hdmi.elf -O binary kernel.img
