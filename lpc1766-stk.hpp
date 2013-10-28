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
         static constexpr int base_freq = 480e6;
         static constexpr int divisor = 5;
         static constexpr int cpu_freq = base_freq / divisor;
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

            cclkcfg::divider<divisor>();
            pll<0>::connect();
         }
      };
   };
}
