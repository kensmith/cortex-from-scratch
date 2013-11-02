#include "isr_vectors.hpp"
#include "board.hpp"

[[noreturn]] void reset_handler(void)
{
   board::init();
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
   using hfsr = lpc1766::scb::hfsr;
   using ufsr = lpc1766::scb::ufsr;

   if (hfsr::debugevt::read())
   {
      while(1);
   }
   else if (hfsr::forced::read())
   {
      volatile unsigned ufsr_val = ufsr::whole::read();
      volatile unsigned bx_bit = lpc1766::id_isar1::bx_instruction_t_bit::read();
      volatile unsigned blx_bit = lpc1766::id_isar1::blx_instruction::read();
      while(ufsr::undefinstr::read());
      while(ufsr_val);
      while(bx_bit);
      while(blx_bit);
      while(1);
   }
   else if (hfsr::vecttbl::read())
   {
      while(1);
   }
   while(1);
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

[[noreturn]] void wdt_handler(void)
{
   while (1);
}

[[noreturn]] void timer0_handler(void)
{
   while (1);
}

[[noreturn]] void timer1_handler(void)
{
   while (1);
}

[[noreturn]] void timer2_handler(void)
{
   while (1);
}

[[noreturn]] void timer3_handler(void)
{
   while (1);
}

[[noreturn]] void uart0_handler(void)
{
   while (1);
}

[[noreturn]] void uart1_handler(void)
{
   while (1);
}

[[noreturn]] void uart2_handler(void)
{
   while (1);
}

[[noreturn]] void uart3_handler(void)
{
   while (1);
}

[[noreturn]] void pwm1_handler(void)
{
   while (1);
}

[[noreturn]] void i2c0_handler(void)
{
   while (1);
}

[[noreturn]] void i2c1_handler(void)
{
   while (1);
}

[[noreturn]] void i2c2_handler(void)
{
   while (1);
}

[[noreturn]] void spi_handler(void)
{
   while (1);
}

[[noreturn]] void ssp0_handler(void)
{
   while (1);
}

[[noreturn]] void ssp1_handler(void)
{
   while (1);
}

[[noreturn]] void pll0_handler(void)
{
   while (1);
}

[[noreturn]] void rtc_handler(void)
{
   while (1);
}

[[noreturn]] void eint0_handler(void)
{
   while (1);
}

[[noreturn]] void eint1_handler(void)
{
   while (1);
}

[[noreturn]] void eint2_handler(void)
{
   while (1);
}

[[noreturn]] void eint3_handler(void)
{
   while (1);
}

[[noreturn]] void adc_handler(void)
{
   while (1);
}

[[noreturn]] void bod_handler(void)
{
   while (1);
}

[[noreturn]] void usb_handler(void)
{
   while (1);
}

[[noreturn]] void can_handler(void)
{
   while (1);
}

[[noreturn]] void dma_handler(void)
{
   while (1);
}

[[noreturn]] void i2s_handler(void)
{
   while (1);
}

[[noreturn]] void emac_handler(void)
{
   while (1);
}

[[noreturn]] void rit_handler(void)
{
   while (1);
}

[[noreturn]] void mc_pwm_handler(void)
{
   while (1);
}

[[noreturn]] void qei_handler(void)
{
   while (1);
}

[[noreturn]] void pll1_handler(void)
{
   while (1);
}

[[noreturn]] void usb_activity_handler(void)
{
   while (1);
}

[[noreturn]] void can_activity_handler(void)
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

void (* const isr_vector_rest[])() =
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
