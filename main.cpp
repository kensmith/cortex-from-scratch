#include "main.hpp"

//TODO refactor register access

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
   *pll0feed = 0x55;
}

void configure_pll0(void)
{
   // max wait state while configuring pll0
   *flashcfg = (5<<12) | 0x3a;

   *scs = (1<<5); // enable main oscillator
   while (0 == (*scs & (1<<6)))
   {
      // wait for the main oscilator to stabilize
   }
   // lpc17xx_um.pdf, 4.5.13 PLL0 setup sequence
   // 1. Disconnect PLL0 with one feed sequence if PLL0 is already connected.
   // ks: not necessary after reboot, defaults to disconnected    
   *pll0con &= ~((unsigned) 1<<1);
   feed_pll();

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
}

int main(void)
{
   configure_pll0();

   // light up all the peripherals
   *pconp = ~0;

   // light led1
   // pin 39 p1[25]
   // pinsel3
   //*pinsel3 = 0;
   *fio1dir = 1<<25;

   // light led2
   // pin 81 p0[4]
   // pinsel0
   while (1)
   {
      for (int i = 6400000; i > 0; --i) *fio1clr = 1<<25;
      for (int i = 6400000; i > 0; --i) *fio1set = 1<<25;
   }
}
