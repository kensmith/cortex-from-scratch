#pragma once

#if defined(__cplusplus)
extern "C" {
#endif

void reset_handler(void) __attribute__ ((interrupt ("IRQ")));
void nmi_handler(void) __attribute__ ((interrupt ("IRQ")));
void hard_fault_handler(void) __attribute__ ((interrupt ("IRQ")));
void memory_management_fault_handler(void) __attribute__ ((interrupt ("IRQ")));
void bus_fault_handler(void) __attribute__ ((interrupt ("IRQ")));
void usage_fault_handler(void) __attribute__ ((interrupt ("IRQ")));
void sv_call_handler(void) __attribute__ ((interrupt ("IRQ")));

void pend_sv_handler(void) __attribute__ ((interrupt ("IRQ")));
void sys_tick_handler(void) __attribute__ ((interrupt ("IRQ")));

void wdt_handler(void) __attribute__ ((interrupt ("IRQ")));
void timer0_handler(void) __attribute__ ((interrupt ("IRQ")));
void timer1_handler(void) __attribute__ ((interrupt ("IRQ")));
void timer2_handler(void) __attribute__ ((interrupt ("IRQ")));
void timer3_handler(void) __attribute__ ((interrupt ("IRQ")));
void uart0_handler(void) __attribute__ ((interrupt ("IRQ")));
void uart1_handler(void) __attribute__ ((interrupt ("IRQ")));
void uart2_handler(void) __attribute__ ((interrupt ("IRQ")));
void uart3_handler(void) __attribute__ ((interrupt ("IRQ")));
void pwm1_handler(void) __attribute__ ((interrupt ("IRQ")));
void i2c0_handler(void) __attribute__ ((interrupt ("IRQ")));
void i2c1_handler(void) __attribute__ ((interrupt ("IRQ")));
void i2c2_handler(void) __attribute__ ((interrupt ("IRQ")));
void spi_handler(void) __attribute__ ((interrupt ("IRQ")));
void ssp0_handler(void) __attribute__ ((interrupt ("IRQ")));
void ssp1_handler(void) __attribute__ ((interrupt ("IRQ")));
void pll0_handler(void) __attribute__ ((interrupt ("IRQ")));
void rtc_handler(void) __attribute__ ((interrupt ("IRQ")));
void eint0_handler(void) __attribute__ ((interrupt ("IRQ")));
void eint1_handler(void) __attribute__ ((interrupt ("IRQ")));
void eint2_handler(void) __attribute__ ((interrupt ("IRQ")));
void eint3_handler(void) __attribute__ ((interrupt ("IRQ")));
void adc_handler(void) __attribute__ ((interrupt ("IRQ")));
void bod_handler(void) __attribute__ ((interrupt ("IRQ")));
void usb_handler(void) __attribute__ ((interrupt ("IRQ")));
void can_handler(void) __attribute__ ((interrupt ("IRQ")));
void dma_handler(void) __attribute__ ((interrupt ("IRQ")));
void i2s_handler(void) __attribute__ ((interrupt ("IRQ")));
void emac_handler(void) __attribute__ ((interrupt ("IRQ")));
void rit_handler(void) __attribute__ ((interrupt ("IRQ")));
void mc_pwm_handler(void) __attribute__ ((interrupt ("IRQ")));
void qei_handler(void) __attribute__ ((interrupt ("IRQ")));
void pll1_handler(void) __attribute__ ((interrupt ("IRQ")));
void usb_activity_handler(void) __attribute__ ((interrupt ("IRQ")));
void can_activity_handler(void) __attribute__ ((interrupt ("IRQ")));

__attribute__ ((section(".isr_vector_first_six"))) extern void (* const isr_vectors[])();
__attribute__ ((section(".isr_sv_call"))) extern void (* const isr_sv_call[])();
__attribute__ ((section(".isr_vector_rest"))) extern void (* const isr_vector_rest[])();

#if defined(__cplusplus)
}
#endif

