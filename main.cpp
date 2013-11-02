#include "board.hpp"

int main(void)
{
   const int start_val = 6400000;
   const int end_val = 0;
   while (1)
   {
      for (int i = start_val; i > end_val; --i)
      {
         board::led::on();
      }
      for (int i = start_val; i > end_val; --i)
      {
         board::led::off();
      }
   }
}
