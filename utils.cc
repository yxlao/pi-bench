#include "utils.h"

// start and end time
unsigned long time_start;
unsigned long time_end;
unsigned long time_total = 0;

// notes: template functions must be put in utils.h for
//        type resolving
//        non template functions must be put in utils.cc to
//        avoid multiple definition

unsigned long tval_to_usec(timeval t) {
    return (unsigned long)t.tv_sec * 1000000 + (unsigned long)t.tv_usec;
}

// Usage:
// struct timeval tval_start, tval_end;
// gettimeofday(&tval_start, NULL);
// sleep(1);
// gettimeofday(&tval_end, NULL);
// unsigned long tval_diff_usec = tval_diff_to_usec(tval_start, tval_end);
// printf("%lu", tval_diff_usec);
unsigned long tval_diff_to_usec(timeval tval_start, timeval tval_end) {
    struct timeval tval_diff;
    timersub(&tval_end, &tval_start, &tval_diff);
    return tval_to_usec(tval_diff);
}

// util template functions
double get_mean(unsigned long* data, int num_trial) {
    // mean
    double mean = 0.0;
    for (int i = 0; i < num_trial; ++i) {
        mean += (double) data[i];
    }
    mean = mean / (double) num_trial;
    return mean;
}

double get_sd(unsigned long* data, int num_trial) {
    // mean
    double mean = get_mean(data, num_trial);
    // std
    double sum_deviation = 0.0;
    for (int i = 0; i < num_trial; ++i) {
        sum_deviation += ((double) data[i] - mean) * ((double) data[i] - mean);
    }
    return sqrt(sum_deviation / num_trial);
}

double get_min(unsigned long* data, int num_trial) {
    double min_val = 0;
    if (num_trial > 0) {
        min_val = (double) data[0];
    }
    for (int i = 0; i < num_trial; ++i) {
        if ((double) data[i] < min_val) {
            min_val = (double) data[i];
        }
    }
    return min_val;
}

double get_max(unsigned long* data, int num_trial) {
    double max_val = 0;
    if (max_val > 0) {
        max_val = (double) data[0];
    }
    for (int i = 0; i < num_trial; ++i) {
        if ((double) data[i] > max_val) {
            max_val = (double) data[i];
        }
    }
    return max_val;
}

// returns the trimmed num_trial
int trim_outlier(unsigned long* data, int num_trial) {
    double mean = get_mean(data, num_trial);
    double sd = get_sd(data, num_trial);
    double min_val = get_min(data, num_trial);
    double max_bound = mean + 3 * sd;
    max_bound = std::min(max_bound, min_val * 2);
    max_bound = std::min(max_bound, mean * 2);
    int write_idx = 0;
    for (int i = 0; i < num_trial; i++) {
        if ((double) data[i] <= max_bound && i > 5) {
            data[write_idx] = data[i];
            write_idx++;
        }
    }
    return write_idx;
}

void print_stats(unsigned long* data, int num_trial, int num_iter,
                 int num_unroll) {
    double mean = get_mean(data, num_trial);
    double sd = get_sd(data, num_trial);
    double min_val = get_min(data, num_trial);
    double max_val = get_max(data, num_trial);
    double mean_op = mean / (double) num_iter / (double) num_unroll;
    std::cout.precision(3);
    std::cout << std::fixed;
    std::cout << "num_trial: " << num_trial << std::endl
              << "num_iter: " << num_iter << std::endl
              << "num_unroll: " << num_unroll << std::endl
              << "mean_op: " << mean_op << std::endl
              << "mean_trial: " << mean << std::endl
              << "std_trial: " << sd << std::endl
              << "min_trial: " << min_val << std::endl
              << "max_trial: " << max_val << std::endl;
}

void print_trimmed_mean_std(unsigned long* data, int num_trial, int num_iter,
                            int num_unroll) {
    // int trimmed_num_trial = trim_outlier(data, num_trial);
    trim_outlier(data, num_trial);
    double mean = get_mean(data, num_trial);
    double sd = get_sd(data, num_trial);
    double mean_op = mean / (double) num_iter / (double) num_unroll;
    double sd_op = sd / (double) num_iter / (double) num_unroll;
    std::cout << "mean_trial: " << mean << std::endl
              << "std_trial: " << sd << std::endl
              << "mean_op: " << mean_op << std::endl
              << "std_op: " << sd_op << std::endl;

}

void print_all_stats(unsigned long* data, int num_trial, int num_iter,
                     int num_unroll) {
    std::cout << "[original stats]" << std::endl;
    print_stats(data, num_trial, num_iter, num_unroll);

    int trimmed_num_trial = trim_outlier(data, num_trial);
    std::cout << "[trimmed stats]" << std::endl;
    print_stats(data, trimmed_num_trial, num_iter, num_unroll);
}
