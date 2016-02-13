#include <iostream>
#include <math.h>
#include "utils.h"
using namespace std;

template <class T> float get_mean(T* data, int n) {
    // mean
    float mean = 0.0;
    for (int i = 0; i < n; ++i) {
        mean += float(data[i]);
    }
    mean = mean / n;
    return mean;
}

template <class T> float get_std(T* data, int n) {
    // mean
    float mean = get_mean(data, n);
    // std
    float sum_deviation = 0.0;
    for (int i = 0; i < n; ++i) {
        sum_deviation += (float(data[i]) - mean) * (float(data[i]) - mean);
    }
    return sqrt(sum_deviation / n);
}