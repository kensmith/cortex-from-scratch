#include "main.hpp"

//TODO refactor register access
// 1720 bytes before refactor
// candidate instructions
// SBFX Rd, Rn, #lsb, #width Signed Bit Field Extract - page 3-58
// STR Rt, [Rn, #offset] Store Register word - page 3-17
// STRB, STRBT Rt, [Rn, #offset] Store Register byte - page 3-17
// STRD Rt, Rt2, [Rn, #offset] Store Register two words - page 3-19
// STREX Rd, Rt, [Rn, #offset] Store Register Exclusive - page 3-31
// STREXB Rd, Rt, [Rn] Store Register Exclusive Byte - page 3-31
// STREXH Rd, Rt, [Rn] Store Register Exclusive Halfword - page 3-31

struct ro_t
{
   static unsigned read(
      volatile unsigned * device,
      unsigned offset,
      unsigned mask
   )
   { return (*device & mask) >> offset; } 
};

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
   { *device = *device | mask; }

   static void clear(
      volatile unsigned * device,
      unsigned mask
   )
   { *device = *device & ~mask; }
};

template <unsigned width>
struct generate_unshifted_mask_t
{
   enum { value = (generate_unshifted_mask_t<width - 1>::value << 1) | 1 };
};

template <>
struct generate_unshifted_mask_t<0>
{
   enum { value = 0 };
};

template <unsigned offset, unsigned width>
struct generate_mask_t
{
   enum { value = generate_unshifted_mask_t<width>::value << offset };
};

template
<
   typename mutability_policy_t,
   unsigned address,
   unsigned offset,
   unsigned width
>
struct reg_t
{
   static unsigned read()
   {
      return
         mutability_policy_t::read(
            reinterpret_cast<volatile unsigned *>(address),
            offset,
            generate_mask_t<offset, width>::value
         );
   }

   static void write(unsigned value)
   {
      mutability_policy_t::write(
         reinterpret_cast<volatile unsigned *>(address),
         offset,
         generate_mask_t<offset, width>::value,
         value
      );
   }

   static void set()
   {
      mutability_policy_t::set(
         reinterpret_cast<volatile unsigned *>(address),
         generate_mask_t<offset, width>::value
      );
   }

   static void clear()
   {
      mutability_policy_t::clear(
         reinterpret_cast<volatile unsigned *>(address),
         generate_mask_t<offset, width>::value
      );
   }
};

struct lpc
{
   struct scs
   {
      static constexpr unsigned addr = 0x400fc1a0;
      using oscrange = reg_t<rw_t, addr, 4, 1>;
      using oscen = reg_t<rw_t, addr, 5, 1>;
      using oscstat = reg_t<rw_t, addr, 6, 1>;
      using whole = reg_t<rw_t, addr, 32, 0>;
   };

   template <int which_fio>
   struct fio
   {
      static_assert(0 <= which_fio && which_fio <= 4, "invalid fio");
      static constexpr unsigned base_addr = 0x2009c000 + 0x20*which_fio;

      template <int which_pin>
      struct pin
      {
         static_assert(0 <= which_pin && which_pin <= 31, "invalid pin");
         using dir = reg_t<rw_t, base_addr, which_pin, 1>;
         using set = reg_t<rw_t, base_addr + 0x18, which_pin, 1>;
         using clr = reg_t<wo_t, base_addr + 0x1c, which_pin, 1>;
      };
   };
};

static volatile unsigned * const scs = (volatile unsigned *) 0x400fc1a0;
static volatile unsigned * const pll0stat = (volatile unsigned *) 0x400fc088;
static volatile unsigned * const pll0con = (volatile unsigned *) 0x400fc080;
static volatile unsigned * const pll0feed = (volatile unsigned *) 0x400fc08c;
static volatile unsigned * const clksrcsel = (volatile unsigned *) 0x400fc10c;
static volatile unsigned * const pll0cfg = (volatile unsigned *) 0x400fc084;
static volatile unsigned * const cclkcfg = (volatile unsigned *) 0x400fc104;
static volatile unsigned * const pclksel0 = (volatile unsigned *) 0x400fc1a8;
static volatile unsigned * const pclksel1 = (volatile unsigned *) 0x400fc1ac;

static volatile unsigned * const flashcfg = (volatile unsigned *) 0x400fc000;
static volatile unsigned * const pconp = (volatile unsigned *) 0x400fc0c4;

static volatile unsigned * const fio1dir = (volatile unsigned *) 0x2009c020;
static volatile unsigned * const fio1set = (volatile unsigned *) 0x2009c038;
static volatile unsigned * const fio1clr = (volatile unsigned *) 0x2009c03c;

#if 0
static volatile unsigned * const u0lcr = (volatile unsigned *) 0x4000c00c;
static volatile unsigned * const u0dll = (volatile unsigned *) 0x4000c000;
static volatile unsigned * const u0dlm = (volatile unsigned *) 0x4000c004;
static volatile unsigned * const u0fdr = (volatile unsigned *) 0x4000c028;
static volatile unsigned * const u0fcr = (volatile unsigned *) 0x4000c008;
static volatile unsigned * const pinsel0 = (volatile unsigned *) 0x4002c000;
static volatile unsigned * const pinmode0 = (volatile unsigned *) 0x4002c040;
static volatile unsigned * const u0thr = (volatile unsigned *) 0x4000c000;
static volatile unsigned * const u0lsr = (volatile unsigned *) 0x4000c014;

static volatile unsigned * const pinsel3 = (volatile unsigned *) 0x4002c00c;
#endif

inline void feed_pll()
{
   *pll0feed = 0xaa;
#if 0
	movs	r2, #170
	str	r2, [r3, #12]
#endif
   *pll0feed = 0x55;
#if 0
	movs	r2, #85
	str	r2, [r3, #12]
#endif
}

void configure_pll0(void)
{
   // max wait state while configuring pll0
   *flashcfg = (5<<12) | 0x3a;
#if 0
	ldr	r3, .L5
	movw	r2, #20538
	str	r2, [r3]
.L5:
	.word	1074774016
	.word	1074774144
#endif


#if 0
   *scs = (1<<5); // enable main oscillator
/*
	.loc 1 210 0
	add	r3, r3, #416
	movs	r2, #32
	str	r2, [r3]
 */
#else
   lpc::scs::oscen::set();
   /*
	.loc 1 46 0
	add	r3, r3, #416
	ldr	r2, [r3]
	orr	r2, r2, #32
	.loc 1 47 0
	str	r2, [r3]
    */

   //lpc::scs::whole::write(1<<5);
   /*
	.loc 1 34 0
	add	r3, r3, #416
	ldr	r2, [r3]
	.loc 1 36 0
	str	r2, [r3]
    */
#endif



#if 0
   movs	r2, #32
   str	r2, [r3, #416]
#endif

   while (0 == (*scs & (1<<6)))
   {
      // wait for the main oscilator to stabilize
   }
#if 0
.L3:
	.loc 1 66 0 discriminator 1
	ldr	r2, [r3]
	lsls	r2, r2, #25
	bpl	.L3
#endif
   // lpc17xx_um.pdf, 4.5.13 PLL0 setup sequence
   // 1. Disconnect PLL0 with one feed sequence if PLL0 is already connected.
   // ks: not necessary after reboot, defaults to disconnected    
   *pll0con &= ~((unsigned) 1<<1);
#if 0
	ldr	r3, .L5+4
	ldr	r2, [r3]
	bic	r2, r2, #2
	str	r2, [r3]
.L5:
	.word	1074774016
	.word	1074774144
#endif

   feed_pll();
#if 1
   *pll0con &= ~((unsigned) 1<<0);
   feed_pll();

   // 3. Change the CPU Clock Divider setting to speed up operation without
   //    PLL0, if desired.

   // ks: not necessary, we're going to use PLL0

   // 4. Write to the Clock Source Selection Control register to change the
   //    clock source if needed.
   
   *clksrcsel = 1;
   feed_pll();

   // 5. Write to the PLL0CFG and make it effective with one feed sequence. The
   //    PLL0CFG can only be updated when PLL0 is disabled.
   // Fin = 12e6
   // M = 20
   // N = 1
   // Fcco = 480e6
   // PLL0CFG = M-1 = 20-1 = 19 = 0x13

   *pll0cfg = (20-1);
   //*pll0cfg = ((25-1)<<0) | ((2-1)<<16);
   feed_pll();

   // Errata
   // PCLKSELx.1:Peripheral Clock Selection Registers must
   // be set before enabling and connecting
   // PLL0
   // Introduction:A pair of bits in the Peripheral Clock
   // Registers (PCLKSEL0 and PCLKSEL1) controls the rate of
   // the clock signal that will be supplied to APB0 and
   // APB1 peripherals.
   // Problem:If the Peripheral Clock Registers (PCLKSEL0
   // and PCLKSEL1) are set or changed after PLL0 is enabled
   // and connected, the value written into the Peripheral
   // Clock Selection Registers may not take effect. It is
   // not possible to change the Peripheral Clock Selection
   // settings once PLL0 is enabled and connected.
   // Workaround:Peripheral Clock Selection Registers must
   // be set before enabling and connecting PLL0.
   *pclksel0 = 0;
   *pclksel1 = 0;

   // 6. Enable PLL0 with one feed sequence.

   *pll0con = 1;
   feed_pll();

   while (0 == (*pll0stat & (1<<26)))
   {
      // wait
   }


   // 7. Change the CPU Clock Divider setting for the operation with PLL0. It
   //    is critical to do this before connecting PLL0.
   // PLL0 output is 480e6 Hz
   // Desired clock <= 100e6 Hz
   // 480e6 / 100e6 = 4.8 => 5
   // 480e6 / 5 = 96e6 MHz (CCLK)
   // CCLKSEL = 5 - 1 = 4

   *cclkcfg = 4;
   //*cclkcfg = 3-1;
   //feed_pll();

   // 8. Wait for PLL0 to achieve lock by monitoring the PLOCK0 bit in the
   //    PLL0STAT register, or using the PLOCK0 interrupt, or wait for a fixed
   //    time when the input clock to PLL0 is slow (i.e. 32 kHz). The value of
   //    PLOCK0 may not be stable when the PLL reference frequency (FREF, the
   //    frequency of REFCLK, which is equal to the PLL input frequency divided by
   //    the pre-divider value) is less than 100 kHz or greater than 20 MHz. In
   //    these cases, the PLL may be assumed to be stable after a start-up time
   //    has passed. This time is 500 μs when FREF is greater than 400 kHz and 200
   //    / FREF seconds when FREF is less than 400 kHz.
   //

   while (0 == (*pll0stat & (1<<26)))
   {
      // wait
   }


   // 9. Connect PLL0 with one feed sequence.

   *pll0con |= 1<<1;
   feed_pll();

   //*flashcfg = (4<<12) | 0x3a;
#endif
}

struct led_t
{
   static void enable()
   {
      lpc::fio<1>::pin<25>::dir::set();
   }

   static void on()
   {
      lpc::fio<1>::pin<25>::clr::set();
   }

   static void off()
   {
      lpc::fio<1>::pin<25>::set::set();
   }
};


int main(void)
{
   configure_pll0();

   // light up all the peripherals
   *pconp = ~0;

   // light led1
   // pin 39 p1[25]
   // pinsel3
   //*pinsel3 = 0;
   led_t::enable();

   // light led2
   // pin 81 p0[4]
   // pinsel0
   while (1)
   {
      for (int i = 6400000; i > 0; --i)
      {
         led_t::on();
      }
      for (int i = 6400000; i > 0; --i)
      {
         led_t::off();
      }
   }
}
