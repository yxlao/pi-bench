#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include <iostream>

// reset counter
#define RESET_CCNT\
    asm volatile("FMSTAT");\
    asm volatile("mcr p15, 0, %0, c15, c12, 0" : : "r"(5));\
    asm volatile("FMSTAT")

// get counter
#define GET_CCNT(value)\
    asm volatile("FMSTAT");\
    asm volatile("mrc p15, 0, %0, c15, c12, 1" : "=r"(value));\
    asm volatile("FMSTAT")

// experiment repetitions
#define NUM_TRIAL  1000
#define NUM_ITER   200
#define NUM_UNROLL 5

// store time of each trail
extern unsigned long time_trials[NUM_TRIAL];

// start and end time
extern unsigned long time_start;
extern unsigned long time_end;
extern unsigned long time_total;

// util template functions
float get_mean(unsigned long* data, int num_trial);
float get_sd(unsigned long* data, int num_trial);
float get_min(unsigned long* data, int num_trial);
float get_max(unsigned long* data, int num_trial);

// returns the trimmed num_trial
int trim_outlier(unsigned long* data, int num_trial);

// print funcs
void print_stats(unsigned long* data, int num_trial, int num_iter,
                 int num_unroll);
void print_all_stats(unsigned long* data, int num_trial, int num_iter,
                     int num_unroll);

#endif