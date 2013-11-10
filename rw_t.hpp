#pragma once

#include "ro_t.hpp"

/**
 * A read-only mutability policy for use with reg_t.
 */
struct rw_t : ro_t
{
   static void write(
      volatile unsigned * device,
      unsigned offset,
      unsigned mask,
      unsigned value
   )
   { *device = (*device & ~mask) | ((value << offset) & mask); }

   static void set(
      volatile unsigned * device,
      unsigned mask
   )
   { *device |= mask; }

   static void clear(
      volatile unsigned * device,
      unsigned mask
   )
   { *device &= ~mask; }
};
