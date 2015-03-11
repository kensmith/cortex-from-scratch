#include "isr_vectors.hpp"
#include "board.hpp"

[[noreturn]] void reset_handler(void)
{
   asm("b main");
   while(1);
}

[[noreturn]] void nmi_handler(void)
{
   while (1);
}

/**
 * 34.4.3.12 Hard Fault Status Register
 */
[[noreturn]] void hard_fault_handler(void)
{
   while (1);
}

[[noreturn]] void memory_management_fault_handler(void)
{
   while (1);
}

[[noreturn]] void bus_fault_handler(void)
{
   while (1);
}

[[noreturn]] void usage_fault_handler(void)
{
   while (1);
}

[[noreturn]] void sv_call_handler(void)
{
   while (1);
}

[[noreturn]] void pend_sv_handler(void)
{
   while (1);
}

[[noreturn]] void sys_tick_handler(void)
{
   while (1);
}

[[noreturn]] void default_handler(void)
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

void (* const isr_vector_rest[])() =
{
   default_handler, default_handler, default_handler, default_handler,
   default_handler, default_handler, default_handler, default_handler,
   default_handler, default_handler, default_handler, default_handler,
   default_handler, default_handler, default_handler, default_handler,
   default_handler, default_handler, default_handler, default_handler,
   default_handler, default_handler, default_handler, default_handler,
   default_handler, default_handler, default_handler, default_handler,
   default_handler, default_handler, default_handler, default_handler,
   default_handler, default_handler, default_handler, default_handler,
   default_handler, default_handler, default_handler, default_handler,
   default_handler, default_handler, default_handler, default_handler,
   default_handler, default_handler, default_handler, default_handler,
   default_handler, default_handler, default_handler, default_handler,
   default_handler, default_handler, default_handler, default_handler,
   default_handler, default_handler, default_handler, default_handler,
   default_handler, default_handler, default_handler, default_handler,
   default_handler, default_handler, default_handler, default_handler,
   default_handler, default_handler, default_handler, default_handler,
   default_handler, default_handler, default_handler, default_handler,
   default_handler, default_handler, default_handler, default_handler,
   default_handler, default_handler, default_handler, default_handler,
   default_handler, default_handler, default_handler, default_handler,
   default_handler, default_handler, default_handler, default_handler,
   default_handler, default_handler, default_handler, default_handler,
   default_handler, default_handler, default_handler, default_handler,
   default_handler, default_handler, default_handler, default_handler,
   default_handler, default_handler, default_handler,
};
