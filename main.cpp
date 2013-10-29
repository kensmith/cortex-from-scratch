#include "board.hpp"

int main(void)
{
   while (1)
   {
      for (int i = 6400000; i > 0; --i)
      {
         board::led::on();
      }
      for (int i = 6400000; i > 0; --i)
      {
         board::led::off();
      }
   }
}
