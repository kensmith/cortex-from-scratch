#pragma once

extern void (* const isr_vectors[])(void);
extern void * __stack_top;

void reset_handler(void)  __attribute__ ((interrupt ("IRQ")));
#if 0
void nmi_handler();
void hard_fault_handler();
void mem_manage_handler();
void bus_fault_handler();
void usage_fault_handler();
void sv_call_handler();
void debug_mon_handler();
void pend_sv_handler();
void sys_tick_handler();
void wdt_handler();
void timer0_handler();
void timer1_handler();
void timer2_handler();
void timer3_handler();
void uart0_handler();
void uart1_handler();
void uart2_handler();
void uart3_handler();
void pwm1_handler();
void i2c0_handler();
void i2c1_handler();
void i2c2_handler();
void spi_handler();
void ssp0_handler();
void ssp1_handler();
void pll0_handler();
void rtc_handler();
void eint0_handler();
void eint1_handler();
void eint2_handler();
void eint3_handler();
void adc_handler();
void bod_handler();
void usb_handler();
void can_handler();
void dma_handler();
void i2s_handler();
void emac_handler();
void rit_handler();
void mc_pwm_handler();
void qei_handler();
void pll1_handler();
void usb_activity_handler();
void can_activity_handler();
#endif
