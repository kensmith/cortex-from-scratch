#include "board.hpp"

int main(void)
{
   const int start_val = 4800000;
   const int end_val = 0;
   while (1)
   {
      for (int i = start_val; i > end_val; --i)
      {
         board::led::on();
         board::uart_t::put_char('1');
      }
      for (int i = start_val; i > end_val; --i)
      {
         board::led::off();
         board::uart_t::put_char('0');
      }
   }
}
