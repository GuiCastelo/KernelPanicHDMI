#include "interrupt.h"

uint32_t tick = 0;

/**
 * Chamado pelo serviço de interrupção irq
 * Deve ser a interrupção do core timer ou de UART
 */
void trata_irq(void) {
    /*
    * Interrupção do timer a cada xx ms -> definir intervalo de tempo entre interrupcao de timer
    */
    //mini_uart_puts("Trata_irq\n");
    if(bit_is_set(IRQ_REG(pending_basic), 0)) {
        TIMER_REG(ack) = 1;                       // reconhece a interrupção
        tick ++;
        if(tick > 5) {
            //mini_uart_puts("Tick_interrupt\n");
            update_interface();
            tick = 0;
        }
        return;
    }

    /*
    * Interrupção da mini UART
    */
    if(bit_is_set(IRQ_REG(pending_1), 29)) { // verifica interrução AUX
        if(bit_is_set(AUX_REG(irq), 0)) { // verifica interrupção mini UART
            mini_uart_puts("        Uart_interrupt\n");
            uint8_t reg_io = MU_REG(io) & 0xFF;
            check_action(reg_io);
            // mini_uart_debug_puts("MU_REG(stat)[19:16] (receive FIFO fill level): ",(MU_REG(stat) & (0b01111 << 16) >> 16));
            // mini_uart_debug_puts("MU_REG(stat)[9] (transmitter done): ",(MU_REG(stat) & __bit(9) >> (9)));
            // mini_uart_debug_puts("MU_REG(stat)[8] (transmit fifo is empty): ",(MU_REG(stat) & __bit(8) >> (8)));
            // mini_uart_debug_puts("MU_REG(stat)[7] (cts line): ",(MU_REG(stat) & __bit(7) >> (7)));
            // mini_uart_debug_puts("MU_REG(stat)[6] (rts status): ",(MU_REG(stat) & __bit(6) >> (6)));
            // mini_uart_debug_puts("MU_REG(stat)[5] (transmit fifo is full): ",(MU_REG(stat) & __bit(5) >> (5)));
            // mini_uart_debug_puts("MU_REG(stat)[4] (receiver overrun): ",(MU_REG(stat) & __bit(4) >> (4)));
            // mini_uart_debug_puts("MU_REG(stat)[3] (transmitter is idle): ",(MU_REG(stat) & __bit(3) >> (3)));
            // mini_uart_debug_puts("MU_REG(stat)[2] (receive is idle): ",(MU_REG(stat) & __bit(2) >> (2)));
            // mini_uart_debug_puts("MU_REG(stat)[1] (space available): ",(MU_REG(stat) & __bit(1) >> (1)));
            // mini_uart_debug_puts("MU_REG(stat)[0] (symbol available): ",(MU_REG(stat) & __bit(0) >> (0)));
            // mini_uart_debug_puts("MU_REG(io)[7:0] (received data): ",(MU_REG(io) & 0b011111111));
            // mini_uart_debug_puts("MU_REG(iir)[2:1] (interrupt ID): ",(MU_REG(iir) & (0b011 << 1) >> 1));
            // mini_uart_debug_puts("MU_REG(iir)[0] (interrupt pending): ",(MU_REG(iir) & 0b01));
            // // MU_REG(iir) = set_bit(MU_REG(iir),1); // clear the receive FIFO
            // mini_uart_debug_puts("MU_REG(stat)[23:20] (receive FIFO fill level): ",(MU_REG(stat) & (0b01111 << 20) >> 20));
            // mini_uart_puts("\n");
        };
        // ... demais interrupcoes sao dos spi_1 e spi_2
    }
}

void irq_init(void) {
    enable_irq();
    enable_timer_irq();
    enable_mini_uart_irq();
}

/*
* Configura interrupção do timer.
*/
void enable_timer_irq(void) {
    TIMER_REG(load) = 1000;             // 1MHz / 10000 = 100 Hz -> Definir intervalo de tempo
    TIMER_REG(control) = __bit(9)        // habilita free-running counter
                        | __bit(7)       // habilita timer
                        | __bit(5)       // habilita interrupção
                        | __bit(1);      // timer de 23 bits

    IRQ_REG(enable_basic) = __bit(0);   // habilita interrupção básica 0 (timer)
}

/*
* Configura interrupção da mini UART
*/
void enable_mini_uart_irq(void) {
    MU_REG(ier) = __bit(3) |
                  __bit(2) |
                //__bit(1) |       // habilita interrupcao na transmissão
                  __bit(0);        // habilita interrupcao na recepção
                
    IRQ_REG(enable_1) = __bit(29); // habilita interrupção da mini UART
}