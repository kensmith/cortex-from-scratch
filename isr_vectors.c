#include "isr_vectors.hpp"
#include "main.hpp"

__attribute__ ((section(".isr_vector"))) void (* const isr_vectors[])() =
{
    (void (*)()) &__stack_top,
    reset_handler,
    //nmi_handler,
#if 0
    hard_fault_handler,
    mem_manage_handler,
    bus_fault_handler,
    usage_fault_handler,
    0,0,0,0,
    sv_call_handler,
    debug_mon_handler,
    pend_sv_handler,
    sys_tick_handler,
    wdt_handler,
    timer0_handler,
    timer1_handler,
    timer2_handler,
    timer3_handler,
    uart0_handler,
    uart1_handler,
    uart2_handler,
    uart3_handler,
    pwm1_handler,
    i2c0_handler,
    i2c1_handler,
    i2c2_handler,
    spi_handler,
    ssp0_handler,
    ssp1_handler,
    pll0_handler,
    rtc_handler,
    eint0_handler,
    eint1_handler,
    eint2_handler,
    eint3_handler,
    adc_handler,
    bod_handler,
    usb_handler,
    can_handler,
    dma_handler,
    i2s_handler,
    emac_handler,
    rit_handler,
    mc_pwm_handler,
    qei_handler,
    pll1_handler,
    usb_activity_handler,
    can_activity_handler
#endif
};

void reset_handler()
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
