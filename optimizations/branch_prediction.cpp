#include <algorithm>
#include <cmath>
#include <iostream>
#include <chrono>

const int N = 1e9;
int a[N];

int main() {
    for (int i = 0; i < N; i++) {
        a[i] = rand() % 100;
    }

    auto start = std::chrono::high_resolution_clock::now();
    // mark that s can be modified externally, so that compiler can't optimize
    volatile int s = 0;
    for (int i = 0; i < N; i++) {
        if (a[i] < 90) { [[likely]]
            s = s + a[i];
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = stop - start;
    std::cout << "time = " << duration.count() / (double) 1e6 << std::endl;
    std::cout << s << std::endl;
}
