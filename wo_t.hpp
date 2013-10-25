#pragma once

/**
 * A write-only mutability policy for use with reg_t.
 */
struct wo_t
{
   static void write(
      volatile unsigned * device,
      unsigned offset,
      unsigned mask,
      unsigned value
   )
   { *device = ((value << offset) & mask); }

   static void set(
      volatile unsigned * device,
      unsigned mask
   )
   { *device = mask; }
};
