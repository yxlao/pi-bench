#ifndef UTILS_H
#define UTILS_H

// reset counter
#define RESET_CCNT\
    asm volatile("FMSTAT");\
    asm volatile("mcr p15, 0, %0, c15, c12, 0" : : "r"(5));\
    asm volatile("FMSTAT");

// get counter
#define GET_CCNT(value)\
    asm volatile("FMSTAT");\
    asm volatile("mrc p15, 0, %0, c15, c12, 1" : "=r"(value));\
    asm volatile("FMSTAT");

// experiment repetitions
#define NUM_TRAIL  1
#define NUM_ITER   100
#define NUM_UNROLL 10

// start and end time
unsigned long start_time;
unsigned long end_time;

#endif