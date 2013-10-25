#pragma once

/**
 * A read-only mutability policy for use with reg_t.
 */
struct ro_t
{
   static unsigned read(
      volatile unsigned * device,
      unsigned offset,
      unsigned mask
   )
   { return (*device & mask) >> offset; } 
};
