#include <algorithm>
#include <cmath>
#include <iostream>

const int N = 1e9;
int a[N];

int main() {
    for (int i = 0; i < N; i++) {
        a[i] = rand() % 100;
    }

    // mark that s can be modified externally, so that compiler can't optimize
    volatile int s = 0;
    for (int i = 0; i < N; i++) {
        if (a[i] < 90) { [[likely]]
            s = s + a[i];
        }
    }
    std::cout << s << std::endl;
}
