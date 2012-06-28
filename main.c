#include "main.hpp"

int main(void)
{
   volatile int i=0,j=0;
   while(1)
   {
      ++i;
      --j;
   }
}
