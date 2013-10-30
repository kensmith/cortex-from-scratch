#pragma once

#include "lpc1766-reg.hpp"

extern char __bss_start__;
extern char __bss_end__;
extern char __data_size__;
extern unsigned __data_start;
extern unsigned __end_of_flash;

/**
 * TODO enable timer tick, ch 23
 */
namespace lpc1766
{
   struct stk
   {
      static void zero_bss_segment()
      {
         for (
            volatile char* c = &__bss_start__;
            c < &__bss_end__;
            ++c)
         {
            *c = 0;
         }
      }

      static void init_data_segment()
      {
         volatile int data_size = reinterpret_cast<int>(&__data_size__);
         volatile unsigned* src = &__end_of_flash;
         volatile unsigned* dst = &__data_start;
         for (volatile int i = 0; i < data_size; i += sizeof(unsigned))
         {
            dst[i] = src[i];
         }
      }

      static void init()
      {
         pconp::whole::write(~0U);
         pll_t::configure();
         led_t::enable();

         zero_bss_segment();
         init_data_segment();
      }

      struct led_t
      {
         static void enable() { fio<1>::pin<25>::dir::set(); }
         static void on() { fio<1>::pin<25>::clr::set(); }
         static void off() { fio<1>::pin<25>::set::set(); }
      };

      /**
       * PLL configuration for driving the main CPU clock.
       * The input clock is 12MHz. A particularly useful and
       * divisible PLL value is 480MHz. The max CPU
       * frequency is 100MHz so the closest we get with that
       * PLL is 96MHz (div=5). Other values are:
       *
       * div, cpu_freq
       * 5, 96
       * 6, 80
       * 8, 60
       * 10, 48
       * 12, 40
       * 15, 32
       * 16, 30
       * 20, 24
       * 24, 20
       * 30, 16
       * 32, 15
       * 40, 12
       * 48, 10
       * 60, 8
       * 80, 6
       * 96, 5
       * 120, 4
       * 160, 3
       * 240, 2
       *
       * Of course, messing with the main clock makes JTAG
       * configuration more fun.
       */
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

      using led = led_t;
   };
}
