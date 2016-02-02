
#define RESET           asm volatile("FMSTAT");asm volatile("mcr p15, 0, %0, c15, c12, 0" : : "r"(5));asm volatile("FMSTAT");
#define GET_CCNT(value) asm volatile("FMSTAT");asm volatile("mrc p15, 0, %0, c15, c12, 1" : "=r"(value));asm volatile("FMSTAT");
#define STD_ITER 1000
unsigned long start_time;
unsigned long end_time;
