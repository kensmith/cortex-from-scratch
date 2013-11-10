#pragma once

#include <cstring>
#include "lpc1766-reg.hpp"

extern char __bss_start__;
extern char __bss_end__;
extern char __bss_size__;
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
         const int bss_size = reinterpret_cast<int>(&__bss_size__);
         std::memset(&__bss_start__, 0, bss_size);
      }

      static void init_data_segment()
      {
         const int data_size = reinterpret_cast<int>(&__data_size__);
         std::memcpy(&__data_start, &__end_of_flash, data_size);
      }

      static void init()
      {
         pconp::whole::write(~0U);
         pll_t::configure();
         led_t::enable();
         uart_t::configure();

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

      struct uart_t
      {
         static void configure()
         {
            pconp::uart0::set();

            // ideas
            // - do a proper interrupt driven DMA driver
            // - read and double check the values of the
            //   configuration registers in the debugger
            pinsel<0>::pin<2>::function::write(1);
            pinsel<0>::pin<3>::function::write(1);

            pclksel0::uart0::write(3);

            uart<0>::lcr::dlab::set();
            uart<0>::dl::msb::clear();
            uart<0>::dl::lsb::write(4);
            uart<0>::fdr::divaddval::write(5);
            uart<0>::fdr::mulval::write(8);
            uart<0>::lcr::dlab::clear();

            uart<0>::lcr::eight_bits();

            uart<0>::fcr::enable_fifo();
            uart<0>::fcr::reset_tx_fifo();
            uart<0>::fcr::reset_rx_fifo();
            uart<0>::fcr::rx_trigger_level::write(3);

            uart<0>::ter::txen::set();
         }

         static void put_char(char c)
         {
            while (!uart<0>::lsr::thre::read())
            {
               //spin
            }
            uart<0>::thr::value::write(c);
         }

         static int peripheral_clock()
         {
            int divisor = 4;
            switch (pclksel0::uart0::read())
            {
               case 0:
                  break;
               case 1:
                  divisor = 1;
                  break;
               case 2:
                  divisor = 2;
                  break;
               case 3:
                  divisor = 8;
                  break;
               default:
                  // TODO report error
                  break;
            }
            const int result = pll_t::cpu_freq / divisor;
            return result;
         }
      };

      using led = led_t;
   };
}
