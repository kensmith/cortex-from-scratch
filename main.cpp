#include "lpc1766-stk.hpp"

int main(void)
{
   using board = lpc1766::stk;

   board::init();

   while (1)
   {
      for (int i = 6400000; i > 0; --i)
      {
         board::led_t::on();
      }
      for (int i = 6400000; i > 0; --i)
      {
         board::led_t::off();
      }
   }
}
