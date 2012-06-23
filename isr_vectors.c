#include "isr_vectors.hpp"
#include "main.hpp"

__attribute__ ((section(".isr_vector_first_seven"))) void (* const isr_vectors[])() =
{
    (void (*)()) &__stack_top,
    reset_handler,
    reset_handler,
    reset_handler,
    reset_handler,
    reset_handler,
    reset_handler,
    (void (*)()) 0xefff5f3a,
};

void reset_handler(void)
{
    main();
}

#if 0
void nmi_handler()
{
    while (2);
}

void hard_fault_handler()
{
    while (1);
}

void mem_manage_handler()
{
    while (1);
}
#endif
