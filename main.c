#include "main.hpp"

static volatile unsigned * const scs = (volatile unsigned *) 0x400fc1a0;
static volatile unsigned * const pll0stat = (volatile unsigned *) 0x400fc088;
static volatile unsigned * const pll0con = (volatile unsigned *) 0x400fc080;
static volatile unsigned * const pll0feed = (volatile unsigned *) 0x400fc08c;
static volatile unsigned * const clksrcsel = (volatile unsigned *) 0x400fc10c;
static volatile unsigned * const pll0cfg = (volatile unsigned *) 0x400fc084;
static volatile unsigned * const cclkcfg = (volatile unsigned *) 0x400fc104;
static volatile unsigned * const pclksel0 = (volatile unsigned *) 0x400fc1a8;

static volatile unsigned * const u0lcr = (volatile unsigned *) 0x4000c00c;
static volatile unsigned * const u0dll = (volatile unsigned *) 0x4000c000;
static volatile unsigned * const u0dlm = (volatile unsigned *) 0x4000c004;
static volatile unsigned * const u0fdr = (volatile unsigned *) 0x4000c028;
static volatile unsigned * const u0fcr = (volatile unsigned *) 0x4000c008;
static volatile unsigned * const pinsel0 = (volatile unsigned *) 0x4002c000;
static volatile unsigned * const pinmode0 = (volatile unsigned *) 0x4002c040;
static volatile unsigned * const u0thr = (volatile unsigned *) 0x4000c000;
static volatile unsigned * const u0lsr = (volatile unsigned *) 0x4000c014;

#define start_critical() do {/*TODO*/} while (0);
#define end_critical() do {/*TODO*/} while (0);

#define feed_pll() do { \
   start_critical(); \
   *pll0feed = 0xaa; \
   *pll0feed = 0x55; \
   end_critical(); \
} while (0)

void configure_pll0(void)
{
   *scs = (1<<5); // enable main oscillator
   while (0 == (*scs & (1<<6)))
   {
      // wait for the main oscilator to stabilize
   }
   // lpc17xx_um.pdf, 4.5.13 PLL0 setup sequence
   // 1. Disconnect PLL0 with one feed sequence if PLL0 is already connected.
   // ks: not necessary after reboot, defaults to disconnected    


   if (*pll0stat & (1<<25))
   {
      unsigned pll0con_value = *pll0con;
      pll0con_value &= ~((unsigned) 1<<1);
      *pll0con = pll0con_value;
      feed_pll();
   }

   // 2. Disable PLL0 with one feed sequence.
   // ks: not necessary after reboot, defaults to disabled

   *pll0con = 0;
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
   feed_pll();

   // 6. Enable PLL0 with one feed sequence.

   *pll0con = 1;
   feed_pll();

   // 7. Change the CPU Clock Divider setting for the operation with PLL0. It
   //    is critical to do this before connecting PLL0.
   // PLL0 output is 480e6 Hz
   // Desired clock <= 100e6 Hz
   // 480e6 / 100e6 = 4.8 => 5
   // 480e6 / 5 = 96e6 MHz (CCLK)
   // CCLKSEL = 5 - 1 = 4

   *cclkcfg = 4;
   feed_pll();

   // 8. Wait for PLL0 to achieve lock by monitoring the PLOCK0 bit in the
   //    PLL0STAT register, or using the PLOCK0 interrupt, or wait for a fixed
   //    time when the input clock to PLL0 is slow (i.e. 32 kHz). The value of
   //    PLOCK0 may not be stable when the PLL reference frequency (FREF, the
   //    frequency of REFCLK, which is equal to the PLL input frequency divided by
   //    the pre-divider value) is less than 100 kHz or greater than 20 MHz. In
   //    these cases, the PLL may be assumed to be stable after a start-up time
   //    has passed. This time is 500 μs when FREF is greater than 400 kHz and 200
   //    / FREF seconds when FREF is less than 400 kHz.

   while (0 == (*pll0stat & (1<<26)))
   {
      // wait
   }

   // 9. Connect PLL0 with one feed sequence.

   *pll0con = 3;
   feed_pll();

}

int main(void)
{
   //configure_pll0();

   // set pclk to cclk / 8
   // cclk = 96MHz
   // pclk = 12MHz
   unsigned x = *pclksel0;
   x = x | (3<<6);
   *pclksel0 = x;
   *u0lcr =
      0x3 // 8 bits
      | (0<<2) // 1 stop bit
      | (0<<3) // no parity
      | (1<<7) // enable access to divisor latches
      ;

   // 115200
   *u0dll = 4;
   *u0dlm = 0;
   *u0fdr =
      (5<<0) // divaddval = 5
      | (8<<4) // mulval = 8
      ;

   *u0fcr =
      (1<<0) // enable FIFO
      | (1<<2) // reset the TX FIFO
      ;

   x = *pinsel0;
   x |=
      (1<<4) // enable TXD0 pin, GPIO Port 0.2
      | (1<<6) // enable RXD0 pin, GPIO Port 0.3
      ;
   *pinsel0 = x;

   // 00, pin has a pull-up resistor enabled.
   // 01, pin has repeater mode enabled.
   // 10, pin has neither pull-up nor pull-down.
   // 11, has a pull-down resistor enabled.
   //*pinmode0   
   // Do nothing to leave pull-up's enabled for now
      
   // dlab
   x = *u0lcr;
   x &= ~(1<<7);
   *u0lcr = x;

   volatile int i=0,j=0;
   while(1)
   {
      
      x = *u0lsr;
      *u0thr = 'a';
      ++i;
      --j;
   }
}
