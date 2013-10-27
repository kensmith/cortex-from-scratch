#pragma once

#include "lpc1766-reg.hpp"

static volatile unsigned * const scs = (volatile unsigned *) 0x400fc1a0;
static volatile unsigned * const pll0stat = (volatile unsigned *) 0x400fc088;
static volatile unsigned * const pll0con = (volatile unsigned *) 0x400fc080;
static volatile unsigned * const pll0cfg = (volatile unsigned *) 0x400fc084;
static volatile unsigned * const cclkcfg = (volatile unsigned *) 0x400fc104;
static volatile unsigned * const pclksel0 = (volatile unsigned *) 0x400fc1a8;
static volatile unsigned * const pclksel1 = (volatile unsigned *) 0x400fc1ac;

static volatile unsigned * const pconp = (volatile unsigned *) 0x400fc0c4;

static volatile unsigned * const fio1dir = (volatile unsigned *) 0x2009c020;
static volatile unsigned * const fio1set = (volatile unsigned *) 0x2009c038;
static volatile unsigned * const fio1clr = (volatile unsigned *) 0x2009c03c;

#if 0
static volatile unsigned * const u0lcr = (volatile unsigned *) 0x4000c00c;
static volatile unsigned * const u0dll = (volatile unsigned *) 0x4000c000;
static volatile unsigned * const u0dlm = (volatile unsigned *) 0x4000c004;
static volatile unsigned * const u0fdr = (volatile unsigned *) 0x4000c028;
static volatile unsigned * const u0fcr = (volatile unsigned *) 0x4000c008;
static volatile unsigned * const pinsel0 = (volatile unsigned *) 0x4002c000;
static volatile unsigned * const pinmode0 = (volatile unsigned *) 0x4002c040;
static volatile unsigned * const u0thr = (volatile unsigned *) 0x4000c000;
static volatile unsigned * const u0lsr = (volatile unsigned *) 0x4000c014;

static volatile unsigned * const pinsel3 = (volatile unsigned *) 0x4002c00c;
#endif

namespace lpc1766
{
   struct stk
   {
      struct led_t
      {
         static void enable() { fio<1>::pin<25>::dir::set(); }
         static void on() { fio<1>::pin<25>::clr::set(); }
         static void off() { fio<1>::pin<25>::set::set(); }
      };

      struct oscillator_t
      {
         static void enable() { scs::oscen::set(); }

         static bool ready() { return scs::oscstat::read() == 1; }
      };

      struct pll_t
      {
         static void configure()
         {
            flashcfg::use<5>::clocks();

            oscillator::enable();

            pll<0>::disconnect();
            pll<0>::disable();
            clksrcsel::use_main_oscillator();
            pll<0>::M(20);
            pll<0>::N(1);

            pclksel<0>::whole::clear();
            pclksel<1>::whole::clear();

            pll<0>::enable();

            while (!pll<0>::locked())
            {
            }


            // 7. Change the CPU Clock Divider setting for the operation with PLL0. It
            //    is critical to do this before connecting PLL0.
            // PLL0 output is 480e6 Hz
            // Desired clock <= 100e6 Hz
            // 480e6 / 100e6 = 4.8 => 5
            // 480e6 / 5 = 96e6 MHz (CCLK)
            // CCLKSEL = 5 - 1 = 4

            *cclkcfg = 4;
            //*cclkcfg = 3-1;
            //pll<0>::feed();

            // 8. Wait for PLL0 to achieve lock by monitoring the PLOCK0 bit in the
            //    PLL0STAT register, or using the PLOCK0 interrupt, or wait for a fixed
            //    time when the input clock to PLL0 is slow (i.e. 32 kHz). The value of
            //    PLOCK0 may not be stable when the PLL reference frequency (FREF, the
            //    frequency of REFCLK, which is equal to the PLL input frequency divided by
            //    the pre-divider value) is less than 100 kHz or greater than 20 MHz. In
            //    these cases, the PLL may be assumed to be stable after a start-up time
            //    has passed. This time is 500 μs when FREF is greater than 400 kHz and 200
            //    / FREF seconds when FREF is less than 400 kHz.
            //

            while (0 == (*pll0stat & (1<<26)))
            {
               // wait
            }


            // 9. Connect PLL0 with one feed sequence.

            *pll0con |= 1<<1;
            pll<0>::feed();

            //*flashcfg = (4<<12) | 0x3a;
         }
      };
   };
}
