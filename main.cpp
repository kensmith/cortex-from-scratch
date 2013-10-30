#include "board.hpp"

namespace
{
   // goes in .data
   int start_val = 6400000;
}

// goes in .bss
static int end_val;

int main(void)
{
   while (1)
   {
      ++start_val;
      ++end_val;
      for (int i = start_val; i > end_val; --i)
      {
         board::led::on();
      }
      for (int i = start_val; i > end_val; --i)
      {
         board::led::off();
      }
      --end_val;
      --start_val;
   }
}
