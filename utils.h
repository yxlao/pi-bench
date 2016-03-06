#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include <iostream>
#include <sys/time.h>

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

// start and end time
extern unsigned long time_start;
extern unsigned long time_end;
extern unsigned long time_total;

unsigned long tval_to_usec(timeval t);
unsigned long tval_diff_to_usec(timeval tval_start, timeval tval_end);

// util template functions
double get_mean(unsigned long* data, int num_trial);
double get_sd(unsigned long* data, int num_trial);
double get_min(unsigned long* data, int num_trial);
double get_max(unsigned long* data, int num_trial);

// returns the trimmed num_trial
int trim_outlier(unsigned long* data, int num_trial);

// print funcs
void print_stats(unsigned long* data, int num_trial, int num_iter,
                 int num_unroll);
void print_all_stats(unsigned long* data, int num_trial, int num_iter,
                     int num_unroll);
void print_trimmed_mean_std(unsigned long* data, int num_trial, int num_iter,
                            int num_unroll);

#endif
