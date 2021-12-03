#ifndef __UTILITY_HPP__
#define __UTILITY_HPP__
#include <cstdio>
#include <sys/time.h>

const int SIZE = 1 << 22;

void print_time(timeval start, timeval end, bool is_parallel) {
    long seconds = (end.tv_sec - start.tv_sec);
    long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
    if (is_parallel)
        printf("Parallel Execution time is %ld s and %ld micros\n\n", seconds, micros);
    else
        printf("Serial Execution time is %ld s and %ld micros\n\n", seconds, micros);
}

float to_float(timeval tv) {
    return tv.tv_sec + tv.tv_usec / 1e6;
}

void print_speedup(timeval serial_time, timeval parallel_time) {
    printf ("Speedup = %4.2f\n", to_float(serial_time) / to_float(parallel_time));
}

timeval operator-(timeval start, timeval end) {
    int diff = (end.tv_sec - start.tv_sec) * int(1e6) + ((int)end.tv_usec - (int)start.tv_usec);
    timeval result;
    result.tv_sec = diff / int(1e6);
    result.tv_usec = diff % int(1e6);
}

#endif