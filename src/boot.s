
.global start, delay, enable_irq
.text
start:
  	/*
	* Vetor de interrupções
	* Deve ser copiado no enderço 0x0000
	*/
	ldr pc, _reset
	ldr pc, _undef
	ldr pc, _swi
	ldr pc, _iabort
	ldr pc, _dabort
	nop
	ldr pc, _irq
	ldr pc, _fiq

	_reset:    .word   reset
	_undef:    .word   panic
	_swi:      .word   panic
	_iabort:   .word   panic
	_dabort:   .word   panic
	_irq:      .word   irq
	_fiq:      .word   panic

/*
* Vetor de reset: início do programa aqui.
*/
reset:
	/*
	* configura os stacks pointers do sistema
	*/
	mov r0, #0xd2           // Modo IRQ
	msr cpsr, r0
	ldr sp, =stack_irq

	mov r0, #0xd3           // Modo SVC, interrupções mascaradas
	msr cpsr, r0
	ldr sp, =stack_sys

	// Continua executando no modo supervisor (SVC), interrupções desabilitadas

	/*
	* Move o vetor de interrupções para o endereço 0
	*/
	ldr r0, =start
	mov r1, #0x0000
	ldmia r0!, {r2,r3,r4,r5,r6,r7,r8,r9}
	stmia r1!, {r2,r3,r4,r5,r6,r7,r8,r9}
	ldmia r0!, {r2,r3,r4,r5,r6,r7,r8,r9}
	stmia r1!, {r2,r3,r4,r5,r6,r7,r8,r9}
   /*
	* Zera segmento BSS
	*/
   ldr r0, =bss_begin
   ldr r1, =bss_end
   mov r2, #0

loop_bss:
   cmp r0, r1
   bge done_bss
   strb r2, [r0], #1
   b loop_bss
done_bss:
	/*
	* Executa a função main
	*/
  	b main

/**
* Trava o processador (panic)
*/
panic:
   wfe
   b panic

enable_irq:
   movs r0, r0
   beq disable
   mrs r0, cpsr
   bic r0, r0, #(1 << 7)
   msr cpsr, r0
   mov pc, lr
disable:
   mrs r0, cpsr
   orr r0, r0, #(1 << 7)
   msr cpsr, r0
   mov pc, lr

irq:
   sub lr, lr, #4
   // Salva o endereco de retorno
   push {lr}
   bl trata_irq  // função em C
	pop {lr}
   movs pc, lr

delay:
   subs r0, r0, #1
   bne delay
   mov pc, lr
