static inline void ccnt_init (void) {
  asm volatile ("mcr p15, 0, %0, c15, c12, 0" : : "r" (1));
}

static inline void ccnt_clr (void) {
  asm volatile ("mcr p15, 0, %0, c15, c12, 0" : : "r" (5));
}


static inline unsigned ccnt_read (void)
{
  unsigned cc;
  asm volatile ("mrc p15, 0, %0, c15, c12, 1":"=r" (cc));
  return cc;
}
