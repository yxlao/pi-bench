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
#define NUM_TRIAL  1000
#define NUM_ITER   100
#define NUM_UNROLL 10

// store time of each trail
unsigned long time_trials[NUM_TRIAL];

// start and end time
unsigned long time_start;
unsigned long time_end;
unsigned long time_total = 0;

// utilities functions
template <class T> float get_mean(T* data, int n);
template <class T> float get_std(T* data, int n);

#endif