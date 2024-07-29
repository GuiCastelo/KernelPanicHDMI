
FONTES = main.c fb.c boot.s stubs.c
LDSCRIPT = linker.ld
RPICPU = bcm2835
PROJECT = hdmi

#
# Arquivos de saída 
#
EXEC = ${PROJECT}.elf
MAP = ${PROJECT}.map
IMAGE = ${PROJECT}.img
HEXFILE = ${PROJECT}.hex
LIST = ${PROJECT}.list

PREFIXO = arm-none-eabi-
AS = ${PREFIXO}as
LD = ${PREFIXO}ld
GCC = ${PREFIXO}gcc
OBJCPY = ${PREFIXO}objcopy
OBJDMP = ${PREFIXO}objdump

LDOPTS = -lc -L/usr/lib/arm-none-eabi/newlib
LDOPTS += -lgcc -L/usr/lib/gcc/arm-none-eabi/13.2.1/ # Mudar versao dependendo da instalação presente no computador

ifeq (${RPICPU}, bcm2836)
	# Raspberry Pi v.2 ou v.3
	ASMOPTIONS = -g --defsym RPICPU=2
	COPTIONS = -march=armv7-a -mtune=cortex-a7 -g -D RPICPU=2
else
	ifeq (${RPICPU}, bcm2835)
  		# Raspberry Pi v.0 ou v.1
   	ASMOPTIONS = -march=armv6zk -g --defsym RPICPU=0
   	COPTIONS = -march=armv6zk -mtune=arm1176jzf-s -g -D RPICPU=0
	endif
endif

OBJ = $(FONTES:.s=.o)
OBJETOS = $(OBJ:.c=.o)

all: ${EXEC} ${IMAGE} ${LIST} ${HEXFILE}

#
# Gerar executável
#
${EXEC}: ${OBJETOS}
	${LD} -T ${LDSCRIPT} -M=${MAP} ${OBJETOS} -o $@ ${LDOPTS}

#
# Gerar imagem
#
${IMAGE}: ${EXEC}
	${OBJCPY} ${EXEC} -O binary ${IMAGE}

#
# Gerar intel Hex
#
${HEXFILE}: ${EXEC}
	${OBJCPY} ${EXEC} -O ihex ${HEXFILE}

#
# Gerar listagem
#
${LIST}: ${EXEC}
	${OBJDMP} -d ${EXEC} > ${LIST}

#
# Compilar arquivos em C
#
.c.o:
	${GCC} ${COPTIONS} -c -o $@ $<

#
# Montar arquivos em assembler
#
.s.o:
	${AS} ${ASMOPTIONS} -o $@ $<

#
# Limpar tudo
#
clean:
	rm -f *.o ${EXEC} ${MAP} ${LIST} ${IMAGE}
