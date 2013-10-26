#include "isr_vectors.hpp"

__attribute__ ((section(".isr_vector_first_six"))) void (* const isr_vectors[])() =
{
    reset_handler,
    nmi_handler,
    hard_fault_handler,
    memory_management_fault_handler,
    bus_fault_handler,
    usage_fault_handler,
};

__attribute__ ((section(".isr_sv_call"))) void (* const isr_sv_call[])() =
{
   sv_call_handler,
};

__attribute__ ((section(".isr_vector_rest"))) void (* const isr_vector_rest[])() =
{
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
   can_activity_handler,
};

int main();
void reset_handler(void)
{
   main();

   while(1);
}

void nmi_handler(void)
{
   while (1);
}

void hard_fault_handler(void)
{
   while (1);
}

void memory_management_fault_handler(void)
{
   while (1);
}

void bus_fault_handler(void)
{
   while (1);
}

void usage_fault_handler(void)
{
   while (1);
}

void sv_call_handler(void)
{
   while (1);
}

void pend_sv_handler(void)
{
   while (1);
}

void sys_tick_handler(void)
{
   while (1);
}

void wdt_handler(void)
{
	while (1);
}

void timer0_handler(void)
{
	while (1);
}

void timer1_handler(void)
{
	while (1);
}

void timer2_handler(void)
{
	while (1);
}

void timer3_handler(void)
{
	while (1);
}

void uart0_handler(void)
{
	while (1);
}

void uart1_handler(void)
{
	while (1);
}

void uart2_handler(void)
{
	while (1);
}

void uart3_handler(void)
{
	while (1);
}

void pwm1_handler(void)
{
	while (1);
}

void i2c0_handler(void)
{
	while (1);
}

void i2c1_handler(void)
{
	while (1);
}

void i2c2_handler(void)
{
	while (1);
}

void spi_handler(void)
{
	while (1);
}

void ssp0_handler(void)
{
	while (1);
}

void ssp1_handler(void)
{
	while (1);
}

void pll0_handler(void)
{
	while (1);
}

void rtc_handler(void)
{
	while (1);
}

void eint0_handler(void)
{
	while (1);
}

void eint1_handler(void)
{
	while (1);
}

void eint2_handler(void)
{
	while (1);
}

void eint3_handler(void)
{
	while (1);
}

void adc_handler(void)
{
	while (1);
}

void bod_handler(void)
{
	while (1);
}

void usb_handler(void)
{
	while (1);
}

void can_handler(void)
{
	while (1);
}

void dma_handler(void)
{
	while (1);
}

void i2s_handler(void)
{
	while (1);
}

void emac_handler(void)
{
	while (1);
}

void rit_handler(void)
{
	while (1);
}

void mc_pwm_handler(void)
{
	while (1);
}

void qei_handler(void)
{
	while (1);
}

void pll1_handler(void)
{
	while (1);
}

void usb_activity_handler(void)
{
	while (1);
}

void can_activity_handler(void)
{
	while (1);
}

