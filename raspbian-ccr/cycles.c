static inline void ccnt_init (void) {
  __asm__ volatile ("mcr p15, 0, %0, c15, c12, 0" : : "r" (4));
  __asm__ volatile ("mcr p15, 0, %0, c15, c12, 0" : : "r" (1));
}


static inline unsigned ccnt_read (void)
{
  unsigned cc;
  __asm__ volatile ("mrc p15, 0, %0, c15, c12, 1":"=r" (cc));
  return cc;
}
