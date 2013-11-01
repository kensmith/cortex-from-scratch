#include "board.hpp"

namespace
{
   // goes in .data
   int start_val = 6400000;
   double start_val2 = 6400000.;
}

int foo();

// goes in .bss
static int end_val;

int main(void)
{
   end_val = foo();
   while (1)
   {
      start_val2 *= 2;
      ++start_val;
      ++end_val;
      for (int i = start_val; i > end_val; --i)
      {
         board::led::on();
      }
      for (int i = static_cast<int>(start_val2); i > end_val; --i)
      {
         board::led::off();
      }
      --end_val;
      --start_val;
      start_val2 /= 2;
   }
}
