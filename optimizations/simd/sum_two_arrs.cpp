// No time measure since I didn't have time to prevent O3 optimization..

#pragma GCC target("avx2")
#pragma GCC optimize("O3")

#include <x86intrin.h>
#include <bits/stdc++.h>
#include "../../debug.h"
using namespace std;


int main() {
    const int N = 100;
    const int N_TURNS = 1e7;

    double a[N], b[N], c[N];

    // double = 64-bit -> fits 4 double in a 256-bit register
    for ([[maybe_unused]] int turn : std::views::iota(0, N_TURNS)) {
        for (int i = 0; i < N; i++) {
        }
        for (int i = 0; i < N; i += 4) {
            // load into registers
            __m256d x = _mm256_loadu_pd(&a[i]);
            __m256d y = _mm256_loadu_pd(&b[i]);

            // add 4+4 64-bit numbers
            __m256d z = _mm256_add_pd(x, y);

            // write result
            _mm256_storeu_pd(&c[i], z);
        }
    }
}
