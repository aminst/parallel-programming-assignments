#ifndef __UTILITY_HPP__
#define __UTILITY_HPP__
#include <cstdio>
#include <sys/time.h>

const int SIZE = 1 << 22;
const int MICROS = int(1e6);

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
    printf("serial time is: %f\n", to_float(serial_time));
    printf("parallel time is: %f\n", to_float(parallel_time));
    printf ("Speedup = %4.2f\n", to_float(serial_time) / to_float(parallel_time));
}

timeval operator-(timeval end, timeval start) {
    long start_usec = start.tv_sec * MICROS + start.tv_usec;
    long end_usec = end.tv_sec * MICROS + end.tv_usec;
    long diff_usec = end_usec - start_usec;
    return timeval {diff_usec / MICROS, diff_usec % MICROS};

}

#endif