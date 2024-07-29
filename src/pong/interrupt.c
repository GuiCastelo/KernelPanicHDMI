#include "interrupt.h"

/**
 * Chamado pelo serviço de interrupção irq
 * Deve ser a interrupção do core timer ou de UART
 */
void trata_irq(void) {
    /*
    * Interrupção do timer a cada xx ms -> definir intervalo de tempo entre interrupcao de timer
    */
    if(bit_is_set(IRQ_REG(pending_basic), 0)) {
        TIMER_REG(ack) = 1;                       // reconhece a interrupção
        update_ball();
        return;
    }

    // outras interrupções aqui...
}

void irq_init(void) {
    /*
    * Configura interrupção do timer.
    */
    TIMER_REG(load) = 10000;             // 1MHz / 10000 = 100 Hz -> Definit intervalo de tempo
    TIMER_REG(control) = __bit(9)        // habilita free-running counter
                        | __bit(7)       // habilita timer
                        | __bit(5)       // habilita interrupção
                        | __bit(1);      // timer de 23 bits

    IRQ_REG(enable_basic) = __bit(0);   // habilita interrupção básica 0 (timer)
}