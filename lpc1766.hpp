#include "reg_t.hpp"
#include "rw_t.hpp"
#include "ro_t.hpp"
#include "wo_t.hpp"

/**
 * The MMIO registers for the LPC1766 that is integrated
 * into the Olimex LPC1766-STK.
 */
struct lpc1766
{
   struct scs
   {
      static constexpr unsigned addr = 0x400fc1a0;
      using oscrange = reg_t<rw_t, addr, 4, 1>;
      using oscen = reg_t<rw_t, addr, 5, 1>;
      using oscstat = reg_t<rw_t, addr, 6, 1>;
      using whole = reg_t<rw_t, addr, 0, 32>;
   };

   template <int which_fio>
   struct fio
   {
      static_assert(0 <= which_fio && which_fio <= 4, "invalid fio");
      static constexpr unsigned base_addr = 0x2009c000 + 0x20*which_fio;

      template <int which_pin>
      struct pin
      {
         static_assert(0 <= which_pin && which_pin <= 31, "invalid pin");
         using dir = reg_t<rw_t, base_addr, which_pin, 1>;
         using set = reg_t<rw_t, base_addr + 0x18, which_pin, 1>;
         using clr = reg_t<wo_t, base_addr + 0x1c, which_pin, 1>;
      };
   };

   template <int which_pll>
   struct pll
   {
      static_assert(0 <= which_pll && which_pll <= 1, "invalid pll");
      static constexpr unsigned base_addr = 0x400fc080+0x20*which_pll;

      struct con
      {
         using plle = reg_t<rw_t, base_addr, 0, 1>;
         using pllc = reg_t<rw_t, base_addr, 1, 1>;
      };
   };
};
