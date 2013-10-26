#include "stk.hpp"

int main(void)
{
   using stk = lpc1766::stk;

   stk::pll_t::configure();

   // light up all the peripherals
   *pconp = ~0;

   stk::led_t::enable();

   while (1)
   {
      for (int i = 6400000; i > 0; --i)
      {
         stk::led_t::on();
      }
      for (int i = 6400000; i > 0; --i)
      {
         stk::led_t::off();
      }
   }
}
