#pragma once

#include "lpc1766.hpp"

namespace lpc1766
{
   struct stk
   {
      struct led_t
      {
         static void enable()
         {
            fio<1>::pin<25>::dir::set();
         }

         static void on()
         {
            fio<1>::pin<25>::clr::set();
         }

         static void off()
         {
            fio<1>::pin<25>::set::set();
         }
      };
   };
}
