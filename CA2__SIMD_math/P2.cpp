#include <x86intrin.h>
#include <iostream>
#include <cstring>
#include <sys/time.h>
#include <cmath>
#include "utility.hpp"

using namespace std;

float average_serial(float* a, int n){
    float sum[4] = {0,0,0,0};
    
    for (int i = 0; i < n; ++i)
        sum[i%4] += a[i];
    return (sum[0] + sum[1] + sum[2] + sum[3]) / n;
}

float std_serial(float* a, int n, float avg){
    float sum[4] = {0,0,0,0};
    for (int i = 0; i < n; ++i)
        sum[i%4] += (a[i] - avg) * (a[i] - avg);
    return sqrt((sum[0] + sum[1] + sum[2] + sum[3]) / n);
}

float std_parallel(float* a, int n, float avg){
    __m128 avg_vec = _mm_set_ps1(avg);
    __m128 sum_vec = _mm_setzero_ps();
    for (int i = 0; i < n; i += 4){
        __m128 sub_vec = _mm_sub_ps(_mm_loadu_ps(a + i), avg_vec);
        sum_vec = _mm_add_ps(sum_vec, _mm_mul_ps(sub_vec, sub_vec));
    }
    return sqrt(_mm_cvtss_f32(_mm_hadd_ps(_mm_hadd_ps(sum_vec, sum_vec), sum_vec)) / n);

}

float average_parallel(float* a, int n) {
    __m128 sum = _mm_setzero_ps();
    for (int i = 0; i < n; i += 4)
        sum = _mm_add_ps(sum, _mm_load_ps(a + i));
    return _mm_cvtss_f32(_mm_hadd_ps(_mm_hadd_ps(sum, sum), sum)) / n;
}

float a[SIZE];

int main(){
    cout << "##########################" << endl;
    cout << "Group Members:" << endl;
    cout << "Mahyar Karimi: 810197690" << endl;
    cout << "Amin Setayesh: 810197523" << endl;
    cout << "##########################" << endl << endl;

    struct timeval start, end;

    int n;
    cin >> n;
    memset(a, 0, SIZE * sizeof(float));
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    gettimeofday(&start, NULL);
    float avg = average_serial(a, SIZE);
    float std = std_serial(a, SIZE, avg);
    gettimeofday(&end, NULL);
    long seconds = (end.tv_sec - start.tv_sec);
    long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

    timeval serial_time = end - start;

    printf("Serial Average: %f\n", avg);
    printf("Serial Std: %f\n", std);
    print_time(start, end, false);

    gettimeofday(&start, NULL);
    avg = average_parallel(a, SIZE);
    std = std_parallel(a, SIZE, avg);
    gettimeofday(&end, NULL);
    seconds = (end.tv_sec - start.tv_sec);
    micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

    timeval parallel_time = end - start;

    printf("Parallel Average: %f\n", avg);
    printf("Parallel Std: %f\n", std);
    print_time(start, end, true);

    print_speedup(serial_time, parallel_time);

    return 0;
}