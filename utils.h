#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include <iostream>
#include <sys/time.h>

#define PMCR_ENABLE_ALL (1 << 0)
#define PMCR_RESET_CTR01 (1 << 1)
#define PMCR_RESET_CCR (1 << 2)
#define PMCR_COUNT_64 (1 << 3)
#define PMCR_EC0 (1 << 4)
#define PMCR_EC1 (1 << 5)
#define PMCR_ECC (1 << 6)
#define PMCR_UNP_SBZ (0 << 7)
#define PMCR_CR0 (1 << 8)
#define PMCR_CR1 (1 << 9)
#define PMCR_CCR (1 << 10)
#define PMCR_X (0 << 11)
#define PMCR_EVTCOUNT1 (0xFF << 12)
#define PMCR_EVTCOUNT0 (0xFF << 20)

#define FLAG (PMCR_ENABLE_ALL | PMCR_RESET_CTR01 | PMCR_RESET_CCR | PMCR_COUNT_64 | PMCR_EVTCOUNT0)

// reset counter
#define RESET_CCNT\
    asm volatile("FMSTAT");\
    asm volatile("mcr p15, 0, %0, c15, c12, 1" : : "r"(0));\
    asm volatile("mcr p15, 0, %0, c15, c12, 0" : : "r"(FLAG));\
    asm volatile("FMSTAT");

// get counter
#define GET_CCNT(value)\
    asm volatile("FMSTAT");\
    asm volatile("mrc p15, 0, %0, c15, c12, 2" : "=r"(value));\
    asm volatile("FMSTAT");

//get low counter, counter increment 1 for each 64 cycles
#define GET_LOW_CCNT(value)\
    asm volatile("FMSTAT");\
    asm volatile("mrc p15, 0, %0, c15, c12, 1" : "=r"(value));\
    asm volatile("FMSTAT");

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
