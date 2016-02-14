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
#define NUM_TRIAL  10000
#define NUM_ITER   200
#define NUM_UNROLL 5

// store time of each trail
extern unsigned long time_trials[NUM_TRIAL];

// start and end time
extern unsigned long time_start;
extern unsigned long time_end;
extern unsigned long time_total;

// util template functions
template <class T> float get_mean(T* data, int num_trial) {
    // mean
    float mean = 0.0;
    for (int i = 0; i < num_trial; ++i) {
        mean += float(data[i]);
    }
    mean = mean / num_trial;
    return mean;
}

template <class T> float get_sd(T* data, int num_trial) {
    // mean
    float mean = get_mean(data, num_trial);
    // std
    float sum_deviation = 0.0;
    for (int i = 0; i < num_trial; ++i) {
        sum_deviation += (float(data[i]) - mean) * (float(data[i]) - mean);
    }
    return sqrt(sum_deviation / num_trial);
}

template <class T> float get_min(T* data, int num_trial) {
    float min_val = 0;
    if (num_trial > 0) {
        min_val = float(data[0]);
    }
    for (int i = 0; i < num_trial; ++i) {
        if (float(data[i]) < min_val) {
            min_val = data[i];
        }
    }
    return min_val;
}

template <class T> float get_max(T* data, int num_trial) {
    float max_val = 0;
    if (max_val > 0) {
        max_val = float(data[0]);
    }
    for (int i = 0; i < num_trial; ++i) {
        if (float(data[i]) > max_val) {
            max_val = data[i];
        }
    }
    return max_val;
}

// returns the trimmed num_trial
template <class T> int trim_outlier(T* data, int num_trial) {
    float mean = get_mean(data, num_trial);
    float sd = get_sd(data, num_trial);
    T max_bound = T(mean) + 3 * T(sd);
    int write_idx = 0;
    for (int i = 0; i < num_trial; i++) {
        if (data[i] <= max_bound) {
            data[write_idx] = data[i];
            write_idx++;
        }
    }
    return write_idx;
}

template <class T> void print_stats(T* data, int num_trial, int num_iter,
                                    int num_unroll) {
    float mean = get_mean(data, num_trial);
    float sd = get_sd(data, num_trial);
    float min_val = get_min(data, num_trial);
    float max_val = get_max(data, num_trial);
    float mean_op = mean / float(num_iter) / float(num_unroll);
    std::cout << "num_trial: " << num_trial << std::endl
              << "num_iter: " << num_iter << std::endl
              << "mean_op: " << mean_op << std::endl
              << "mean_trial: " << mean << std::endl
              << "std_trail: " << sd << std::endl
              << "min_trial: " << min_val << std::endl
              << "max_trial: " << max_val << std::endl;
}

template <class T> void print_all_stats(T* data, int num_trial, int num_iter,
                                        int num_unroll) {
    std::cout << "# original stats" << std::endl;
    print_stats(data, num_trial, num_iter, num_unroll);

    int trimmed_num_trail = trim_outlier(data, num_trial);
    std::cout << "# trimmed stats" << std::endl;
    print_stats(data, trimmed_num_trail, num_iter, num_unroll);
}

#endif