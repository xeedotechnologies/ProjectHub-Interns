#include <LPC21XX.H>                          // LPC21XX Peripheral Registers


long timeval;


void tc0 (void) __irq  {
  ++timeval;
  T0IR        = 1;                            // Clear interrupt flag
  VICVectAddr = 0;                            // Acknowledge Interrupt
}


void init_timer (void) {
  T0MR0 = 149999; //149999;                            // 10mSec = 150.000-1 counts
  T0MCR = 3;                                  // Interrupt and Reset on MR0
  T0TCR = 1;                                  // Timer0 Enable
  VICVectAddr0 = (unsigned long)tc0;          // set interrupt vector in 0
  VICVectCntl0 = 0x20 | 4;                    // use it for Timer 0 Interrupt
  VICIntEnable = 0x00000010;                  // Enable Timer0 Interrupt
}
