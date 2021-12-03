#include <x86intrin.h>
#include <iostream>
#include <limits>
#include <cstring>
#include <sys/time.h>
#include "utility.hpp"

using namespace std;

const __m128i INCREMENT = _mm_set_epi32(4, 4, 4, 4);

int min_idx_serial(float* a, int n) {
    int min_idx = 0;
    for (int i = 0; i < n; ++i)
        min_idx = (a[i] < a[min_idx]) ? i : min_idx;

    return min_idx;
}

union float_vec {
    __m128 v;
    float vec[4];
};

union int_vec {
    __m128i v;
    int vec[4];
};

int min_idx_parallel(float* a, int n) {
    __m128i indices = _mm_setr_epi32(0, 1, 2, 3);
    __m128i min_indices = indices;
    __m128 min_vals = _mm_load_ps(a);

    for (size_t i = 0; i < n; i += 4) {
        __m128 values = _mm_load_ps(a + i);
        __m128 lt = _mm_cmplt_ps(values, min_vals);
        min_indices = _mm_blendv_epi8(min_indices, indices, __m128i(lt));
        min_vals = _mm_min_ps(values, min_vals);
        indices = _mm_add_epi32(indices, INCREMENT);
    }

    float_vec f_vec = {min_vals};
    int min_idx = min_idx_serial(f_vec.vec, 4);
    int_vec idx_vec = {min_indices};
    return int(idx_vec.vec[min_idx]);
}

float a[SIZE];

int main() {
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
    int result_s = min_idx_serial(a, n);
    gettimeofday(&end, NULL);

    timeval serial_time;
    

    cout << "Serial Min. Index: " << result_s << endl;
    print_time(start, end);
    
    gettimeofday(&start, NULL);
    int result_p = min_idx_parallel(a, n);
    gettimeofday(&end, NULL);

    cout << "Parallel Min. Index: " << result_p << endl;
    print_time(start, end);
}