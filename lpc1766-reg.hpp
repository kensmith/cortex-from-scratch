#include "reg_t.hpp"
#include "rw_t.hpp"
#include "ro_t.hpp"
#include "wo_t.hpp"

/**
 * The MMIO registers for the LPC1766 that is integrated
 * into the Olimex LPC1766-STK. Chapter references cite
 * UM10360 LPC17xx User manual Rev. 2 — 19 August 2010.
 */
namespace lpc1766
{
   /**
    * 3.7.1 System Controls and Status register (SCS -
    * 0x400F C1A0)
    */
   struct scs
   {
      static constexpr unsigned addr = 0x400fc1a0;
      using oscrange = reg_t<rw_t, addr, 4, 1>;
      using oscen = reg_t<rw_t, addr, 5, 1>;
      using oscstat = reg_t<rw_t, addr, 6, 1>;
   };

   struct oscillator
   {
      static void enable()
      {
         scs::oscen::set();
         while (!ready())
         {
         }
      }
      static bool ready() {return scs::oscstat::read() == 1;}
   };

   /**
    * Chapter 9: LPC17xx General Purpose Input/Output (GPIO)
    */
   template <int which_fio>
   struct fio
   {
      static_assert(0 <= which_fio && which_fio <= 4, "invalid fio");
      static constexpr unsigned base_addr = 0x2009c000 + 0x20*which_fio;

      template <int which_pin>
      struct pin
      {
         using dir = reg_t<rw_t, base_addr, which_pin, 1>;
         using set = reg_t<rw_t, base_addr + 0x18, which_pin, 1>;
         using clr = reg_t<wo_t, base_addr + 0x1c, which_pin, 1>;
      };
   };

   /**
    * 4.4.1 Clock Source Select register (CLKSRCSEL - 0x400F
    * C10C)
    */
   struct clksrcsel
   {
      using clksrc = reg_t<rw_t, 0x400fc10c, 0, 2>;
      static void use_internal_rc_oscillator() { clksrc::write(0); }
      static void use_main_oscillator() { clksrc::write(1); }
      static void use_rtc_oscillator() { clksrc::write(2); }
   };

   /**
    * 5.4 Flash Accelerator Configuration register (FLASHCFG
    * - 0x400F C000)
    */
   struct flashcfg
   {
      using flashtim = reg_t<rw_t, 0x400fc000, 12, 4>;

      template <int num_clocks>
      struct use
      {
         static_assert(0 <= num_clocks && num_clocks <= 6, "invalid flash timing");
         static void clocks()
         {
            flashtim::write(num_clocks);
         }
      };
   };

   /**
    * 4.5.2 PLL0 register description
    */
   template <int which_pll>
   struct pll
   {
      static_assert(0 <= which_pll && which_pll <= 1, "invalid pll");
      static constexpr unsigned base_addr = 0x400fc080+0x20*which_pll;

      /**
       * 4.5.3 PLL0 Control register (PLL0CON - 0x400F C080)
       */
      struct con
      {
         using plle = reg_t<rw_t, base_addr, 0, 1>;
         using pllc = reg_t<rw_t, base_addr, 1, 1>;

      };
      static void enable()
      {
         con::plle::write(1);
         feed();
         wait_for_lock();
      }
      static void disable() { con::plle::write(0); feed();}
      static void connect() { con::pllc::write(1); feed();}
      static void disconnect() { con::pllc::write(0); feed();}

      struct cfg
      {
         static constexpr unsigned addr = base_addr+4;
         using msel = reg_t<rw_t, addr, 0, 14>;
         using nsel = reg_t<rw_t, addr, 16, 8>;
      };

      static constexpr void M(unsigned m)
      {
         cfg::msel::write(m - 1);
         feed();
      }

      static constexpr void N(unsigned n)
      {
         cfg::nsel::write(n - 1);
         feed();
      }

      /**
       * 4.5.5 PLL0 Status register (PLL0STAT - 0x400F C088)
       */
      struct stat
      {
         static constexpr unsigned addr = base_addr+8;
         using msel = reg_t<ro_t, addr, 0, 14>;
         using nsel = reg_t<ro_t, addr, 16, 8>;
         using plle = reg_t<ro_t, addr, 24, 1>;
         using pllc = reg_t<ro_t, addr, 25, 1>;
         using plock = reg_t<ro_t, addr, 26, 1>;
      };

      static bool locked()
      {
         return stat::plock::read() == 1;
      }

      static void wait_for_lock()
      {
         while (!locked())
         {
         }
      }

      /**
       * 4.5.8 PLL0 Feed register (PLL0FEED - 0x400F C08C)
       */
      struct feed
      {
         using pllfeed = reg_t<wo_t, base_addr+0xc, 0, 8>;

         ~feed()
         {
            pllfeed::write(0xaa);
            pllfeed::write(0x55);
         }
      };
   };

   /**
    * 4.7.3 Peripheral Clock Selection registers 0 and 1
    * (PCLKSEL0 - * 0x400F C1A8 and PCLKSEL1 - 0x400F C1AC)
    */
   template <int which>
   struct pclksel
   {
      static_assert(0 <= which && which <= 1, "invalid pclksel");
      static constexpr unsigned addr = 0x400fc1a8+which*4;
      using whole = reg_t<rw_t, addr, 0, 32>;
   };

   /**
    * 4.7.1 CPU Clock Configuration register (CCLKCFG -
    * 0x400F C104)
    */
   struct cclkcfg
   {
      static constexpr unsigned addr = 0x400fc104;
      using cclksel = reg_t<rw_t, addr, 0, 8>;

      template <int value>
      struct divider
      {
         static_assert(1 <= value && value <= 256, "invalid clock divider");
         ~divider()
         {
            cclksel::write(value - 1);
            pll<0>::wait_for_lock();
         }
      };
   };
}
