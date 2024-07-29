#
#	Makefile para o Raspberry Pi ZERO W (bcm2835) (ARM1176JZF-S) (ARMv6)
#	
SRC_FOLDER ?= pisca_led
LDSCRIPT = linker.ld
PROJECT = $(SRC_FOLDER)
C_FILES = ${wildcard $(SRC_FOLDER)/*.c}
AS_FILES = ${wildcard $(SRC_FOLDER)/*.s}
SRC_FILES = $(C_FILES) $(AS_FILES)

#
# Arquivos de saída 
#
EXEC = ${PROJECT}.elf
MAP = ${PROJECT}.map
IMAGE = ${PROJECT}.img
HEXFILE = ${PROJECT}.hex
LIST = ${PROJECT}.list

#
# Comandos GNU-Binutils
#
PREFIXO = arm-none-eabi-

AS = ${PREFIXO}as
AS_OPTIONS = --warn --fatal-warnings
AS_OPTIONS += -I ./$(SRC_FOLDER) # Busca os arquivos de include no diretorio indicado
AS_OPTIONS += -march=armv6zk # especifica a arquitetura alvo
#AS_OPTIONS = -g --defsym RPICPU=0

#  o $@ é uma variável automática que representa o nome do alvo (target) da regra que está sendo executada.
LD = ${PREFIXO}ld
LD_OPTIONS = -T ${LDSCRIPT} # especifica o script de linkagem que será utilizado
LD_OPTIONS += -M=${MAP} # gera um arquivo de mapa
LD_OPTIONS += -o $@ # especifica no nome do arqutivo de saida
LD_OPTIONS += $(notdir $^)  # especifica os arquivos objetos
LD_OPTIONS += -lc -L/usr/lib/arm-none-eabi/newlib
LD_OPTIONS += -lgcc -L/usr/lib/gcc/arm-none-eabi/13.2.1/ # Mudar versao dependendo da instalação presente no computador

GCC = ${PREFIXO}gcc
GCC_OPTIONS = -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding
GCC_OPTIONS += -I ./$(SRC_FOLDER)
GCC_OPTIONS += -march=armv6zk # especifica a arquitetura alvo
GCC_OPTIONS += -mcpu=arm1176jzf-s # especifica o processador alvo
GCC_OPTIONS += -g # ativa mensagens de depuracao do compilador
GCC_OPTIONS += -D # Enable debugging in target specific backends, if supported. Otherwise ignored.
#GCC_OPTIONS += -mfpu=vfp
#GCC_OPTIONS = -mtune=arm1176jzf-s

OBJCPY = ${PREFIXO}objcopy
OBJDMP = ${PREFIXO}objdump

OBJ_FILES = $(patsubst %.c,%.o,$(patsubst %.s,%.o,$(SRC_FILES)))

all: ${EXEC} ${IMAGE} ${LIST} ${HEXFILE}

#
# Gerar arquivo .elf
#
${EXEC}: ${OBJ_FILES}
	${LD} ${LD_OPTIONS}

#
# Gerar arquivo .img
#
${IMAGE}: ${EXEC}
	${OBJCPY} ${EXEC} -O binary ${IMAGE}

#
# Gerar arquivo .hex
#
${HEXFILE}: ${EXEC}
	${OBJCPY} ${EXEC} -O ihex ${HEXFILE}

#
# Gerar arquivo .list
#
${LIST}: ${EXEC}
	${OBJDMP} -d ${EXEC} > ${LIST}

#
# Compilar arquivos em C
#
.c.o:
	${GCC} ${GCC_OPTIONS} -c -o $(notdir $@) $<

#
# Montar arquivos em assembler
#
.s.o:
	${AS} ${AS_OPTIONS} -o $(notdir $@) $<

#
# Limpar tudo
#
clean:
	rm -f *.o ${EXEC} ${MAP} ${LIST} ${IMAGE} ${HEXFILE}
