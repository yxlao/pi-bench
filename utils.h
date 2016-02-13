#ifndef UTILS_H
#define UTILS_H

#include <math.h>

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
extern unsigned long time_trials[NUM_TRIAL];

// start and end time
extern unsigned long time_start;
extern unsigned long time_end;
extern unsigned long time_total;

// util template functions
template <class T> float get_mean(T* data, int n) {
    // mean
    float mean = 0.0;
    for (int i = 0; i < n; ++i) {
        mean += float(data[i]);
    }
    mean = mean / n;
    return mean;
}

template <class T> float get_sd(T* data, int n) {
    // mean
    float mean = get_mean(data, n);
    // std
    float sum_deviation = 0.0;
    for (int i = 0; i < n; ++i) {
        sum_deviation += (float(data[i]) - mean) * (float(data[i]) - mean);
    }
    return sqrt(sum_deviation / n);
}

template <class T> void print_stats(T* data, int n) {
    float mean = get_mean(data, n);
    float sd = get_sd(data, n);
    std::cout << "num_trial: " << NUM_TRIAL << std::endl
              << "nnum_iter: " << NUM_ITER << std::endl
              << "mean_op: " << mean / float(NUM_ITER) << std::endl
              << "mean_trial: " << mean << std::endl
              << "std_trail: " << sd << std::endl;
}

#endif