#include <iostream>
#include <math.h>
#include "utils.h"
using namespace std;

// store time of each trail
unsigned long time_trials[NUM_TRIAL];

// start and end time
unsigned long time_start;
unsigned long time_end;
unsigned long time_total = 0;

// notes: template functions must be put in utils.h for
//        type resolving
//        non template functions must be put in utils.cc to
//        avoid multiple definition

// util template functions
float get_mean(unsigned long* data, int num_trial) {
    // mean
    float mean = 0.0;
    for (int i = 0; i < num_trial; ++i) {
        mean += (float) data[i];
    }
    mean = mean / num_trial;
    return mean;
}

float get_sd(unsigned long* data, int num_trial) {
    // mean
    float mean = get_mean(data, num_trial);
    // std
    float sum_deviation = 0.0;
    for (int i = 0; i < num_trial; ++i) {
        sum_deviation += ((float) data[i] - mean) * ((float) data[i] - mean);
    }
    return sqrt(sum_deviation / num_trial);
}

float get_min(unsigned long* data, int num_trial) {
    float min_val = 0;
    if (num_trial > 0) {
        min_val = (float) data[0];
    }
    for (int i = 0; i < num_trial; ++i) {
        if ((float) data[i] < min_val) {
            min_val = data[i];
        }
    }
    return min_val;
}

float get_max(unsigned long* data, int num_trial) {
    float max_val = 0;
    if (max_val > 0) {
        max_val = (float) data[0];
    }
    for (int i = 0; i < num_trial; ++i) {
        if ((float) data[i] > max_val) {
            max_val = data[i];
        }
    }
    return max_val;
}

// returns the trimmed num_trial
int trim_outlier(unsigned long* data, int num_trial) {
    float mean = get_mean(data, num_trial);
    float sd = get_sd(data, num_trial);
    float min_val = get_min(data, num_trial);
    float max_bound = mean + 3 * sd;
    max_bound = min(max_bound, min_val * 2);
    int write_idx = 0;
    for (int i = 0; i < num_trial; i++) {
        if ((float) data[i] <= max_bound) {
            data[write_idx] = data[i];
            write_idx++;
        }
    }
    return write_idx;
}

void print_stats(unsigned long* data, int num_trial, int num_iter,
                 int num_unroll) {
    float mean = get_mean(data, num_trial);
    float sd = get_sd(data, num_trial);
    float min_val = get_min(data, num_trial);
    float max_val = get_max(data, num_trial);
    float mean_op = mean / (float) num_iter / (float) num_unroll;
    std::cout << "num_trial: " << num_trial << std::endl
              << "num_iter: " << num_iter << std::endl
              << "mean_op: " << mean_op << std::endl
              << "mean_trial: " << mean << std::endl
              << "std_trail: " << sd << std::endl
              << "min_trial: " << min_val << std::endl
              << "max_trial: " << max_val << std::endl;
}

void print_all_stats(unsigned long* data, int num_trial, int num_iter,
                     int num_unroll) {
    std::cout << "# original stats" << std::endl;
    print_stats(data, num_trial, num_iter, num_unroll);

    int trimmed_num_trail = trim_outlier(data, num_trial);
    std::cout << "# trimmed stats" << std::endl;
    print_stats(data, trimmed_num_trail, num_iter, num_unroll);
}
