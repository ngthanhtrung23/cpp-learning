// Tested on https://oj.vnoi.info/problem/segtree_itez2
// 3.5x speedup

#pragma GCC target("avx2")

#include <x86intrin.h>
#include "bits/stdc++.h"
using namespace std;

namespace IO {
    const int BUFSIZE = 1<<14;
    char buf[BUFSIZE + 1], *inp = buf;

    bool reacheof;
    char get_char() {
        if (!*inp && !reacheof) {
            memset(buf, 0, sizeof buf);
            int tmp = fread(buf, 1, BUFSIZE, stdin);
            if (tmp != BUFSIZE) reacheof = true;
            inp = buf;
        }
        return *inp++;
    }
    template<typename T>
    T get() {
        int neg = 0;
        T res = 0;
        char c = get_char();
        while (!std::isdigit(c) && c != '-' && c != '+') c = get_char();
        if (c == '+') { neg = 0; }
        else if (c == '-') { neg = 1; }
        else res = c - '0';

        c = get_char();
        while (std::isdigit(c)) {
            res = res * 10 + (c - '0');
            c = get_char();
        }
        return neg ? -res : res;
    }
};

const int MN = 100111;

long long a[MN];
long long res[4];

int main() {
    int n = IO::get<int>();
    int q = IO::get<int>();

    while (q--) {
        int typ = IO::get<int>();
        int x = IO::get<int>();
        int y = IO::get<int>();
        if (typ == 1) a[x] = y;
        else {
            // init 256-bit register sum = 0
            __m256i sum = _mm256_set1_epi32(0);

            int l = x;
            // In each iteration, we add a[l], a[l+1], a[l+2], a[l+3] to sum
            for (; l+3 <= y; l += 4) {
                // load a[l] a[l+1] a[l+2] a[l+3] to 256-bit register
                __m256i vals = _mm256_loadu_si256((__m256i*) &a[l]);

                // update sum
                sum = _mm256_add_epi64(sum, vals);
            }

            // save 256-bit register sum to an array res
            _mm256_storeu_si256((__m256i*) &res[0], sum);

            // s = sum of res
            long long s = 0;
            for (int i = 0; i < 4; i++) s += res[i];

            // add extra elements at the end
            for (int i = l; i <= y; i++) {
                s += a[i];
            }
            cout << s << '\n';
        }
    }
    return 0;
}
