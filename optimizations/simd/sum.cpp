// Initial code -> 3.2s
// Adding avx2 + O3 -> 0.5s
#pragma GCC target("avx2")
#pragma GCC optimize("O3")

#include <x86intrin.h>
#include <bits/stdc++.h>
#include "../../debug.h"
using namespace std;

const int N_TURNS = 1e5;

int main() {
    const int N = 1e5;
    // Align as 32-bytes
    alignas(32) int a[N];

    int sum = 0;
    for (int turn = 0; turn < N_TURNS; turn++) {
        for (int i = 0; i < N; i++) {
            sum += a[i];
        }
    }
    DEBUG(sum);
}
