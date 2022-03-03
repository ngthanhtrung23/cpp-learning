#include <bits/stdc++.h>
#include "../debug.h"

int compute(int x) {
    int res = 0;
    for (int i = 0; i < x; i++) {
        res += rand() % 1000;
    }
    return res;
}

int main() {
    std::future<int> f = std::async(&compute, static_cast<int> (1e6));

    DEBUG(f.get());
    return 0;
}
