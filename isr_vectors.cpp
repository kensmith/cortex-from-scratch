#include "isr_vectors.hpp"
#include "board.hpp"

[[noreturn]] void reset_handler()
{
   asm("b main");
   while(1);
}

[[noreturn]] void nmi_handler()
{
   while (1);
}

[[noreturn]] void hard_fault_handler()
{
   while (1);
}

[[noreturn]] void memory_management_fault_handler()
{
   while (1);
}

[[noreturn]] void bus_fault_handler()
{
   while (1);
}

[[noreturn]] void usage_fault_handler()
{
   while (1);
}

[[noreturn]] void sv_call_handler()
{
   while (1);
}

[[noreturn]] void pend_sv_handler()
{
   while (1);
}

[[noreturn]] void sys_tick_handler()
{
   while (1);
}

[[noreturn]] void default_handler()
{
   while (1);
}

void (* const isr_vectors[])() =
{
    reset_handler,
    nmi_handler,
    hard_fault_handler,
    memory_management_fault_handler,
    bus_fault_handler,
    usage_fault_handler,
};

void (* const isr_sv_call[])() =
{
   sv_call_handler,
};

void (* const isr_vector_last_sys[])() =
{
   pend_sv_handler,
   sys_tick_handler,
};

#if 0 // use this to determine if the mapping is correct
#define use_default_handler_for(peripheral) \
   reinterpret_cast<void(*)()>(__LINE__)
#else
#define use_default_handler_for(peripheral) \
   default_handler
#endif

void (* const isr_vector_rest0[])() =
{
   use_default_handler_for(gpio_port_a),
   use_default_handler_for(gpio_port_b),
   use_default_handler_for(gpio_port_c),
   use_default_handler_for(gpio_port_d),
   use_default_handler_for(gpio_port_e),
   use_default_handler_for(uart0),
   use_default_handler_for(uart1),
   use_default_handler_for(ssi0),
   use_default_handler_for(i2c0),
};

void (* const isr_vector_rest1[])() =
{
   use_default_handler_for(adc0_sequence0),
   use_default_handler_for(adc0_sequence1),
   use_default_handler_for(adc0_sequence2),
   use_default_handler_for(adc0_sequence3),
   use_default_handler_for(wdt0_1),
   use_default_handler_for(timer0a_16_32),
   use_default_handler_for(timer0b_16_32),
   use_default_handler_for(timer1a_16_32),
   use_default_handler_for(timer1b_16_32),
   use_default_handler_for(timer2a_16_32),
   use_default_handler_for(timer2b_16_32),
   use_default_handler_for(analog_comparator0),
   use_default_handler_for(analog_comparator1),
};

void (* const isr_vector_rest2[])() =
{
   use_default_handler_for(system_control),
   use_default_handler_for(flash_memory_and_eeprom),
   use_default_handler_for(gpio_port_f),
};

void (* const isr_vector_rest3[])() =
{
   use_default_handler_for(uart2),
   use_default_handler_for(ssi1),
   use_default_handler_for(timer3a_16_32),
   use_default_handler_for(timer3b_16_32),
   use_default_handler_for(i2c1),
};

void (* const isr_vector_rest4[])() =
{
   use_default_handler_for(can0),
};

void (* const isr_vector_rest5[])() =
{
   use_default_handler_for(hibernation_module),
   use_default_handler_for(usb),
};

void (* const isr_vector_rest6[])() =
{
   use_default_handler_for(udma_software),
   use_default_handler_for(udma_error),
   use_default_handler_for(adc1_sequence0),
   use_default_handler_for(adc1_sequence1),
   use_default_handler_for(adc1_sequence2),
   use_default_handler_for(adc1_sequence3),
};

void (* const isr_vector_rest7[])() =
{
   use_default_handler_for(ssi2),
   use_default_handler_for(ssi3),
   use_default_handler_for(uart3),
   use_default_handler_for(uart4),
   use_default_handler_for(uart5),
   use_default_handler_for(uart6),
   use_default_handler_for(uart7),
};

void (* const isr_vector_rest8[])() =
{
   use_default_handler_for(i2c2),
   use_default_handler_for(i2c3),
   use_default_handler_for(timer4a_16_32),
   use_default_handler_for(timer4b_16_32),
};

void (* const isr_vector_rest9[])() =
{
   use_default_handler_for(timer5a_16_32),
   use_default_handler_for(timer5b_16_32),
   use_default_handler_for(timer0a_32_64),
   use_default_handler_for(timer0b_32_64),
   use_default_handler_for(timer1a_32_64),
   use_default_handler_for(timer1b_32_64),
   use_default_handler_for(timer2a_32_64),
   use_default_handler_for(timer2b_32_64),
   use_default_handler_for(timer3a_32_64),
   use_default_handler_for(timer3b_32_64),
   use_default_handler_for(timer4a_32_64),
   use_default_handler_for(timer4b_32_64),
   use_default_handler_for(timer5a_32_64),
   use_default_handler_for(timer5b_32_64),
   use_default_handler_for(system_exception),
};
