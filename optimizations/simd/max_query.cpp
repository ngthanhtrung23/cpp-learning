// Tested on https://oj.vnoi.info/problem/segtree_itez1
// Near 8x speedup

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
const int INF = 1000111000;

int a[MN];
int res[8], inf[8];

int main() {
    int n = IO::get<int>();
    for (int i = 1; i <= n; i++) {
        a[i] = IO::get<int>();
    }
    int q = IO::get<int>();

    for (int i = 0; i < 8; i++) {
        inf[i] = -INF;
    }

    while (q--) {
        int typ = IO::get<int>();
        int x = IO::get<int>();
        int y = IO::get<int>();
        if (typ == 1) a[x] = y;
        else {
            // load (-INF, -INF, ..., -INF) into 256-bit register max_val
            __m256i max_val = _mm256_loadu_si256((__m256i*) (inf));

            int l = x;
            // Process groups of 8 int
            for (; l+7 <= y; l += 8) {
                // load a[l] a[l+1] a[l+2] ... a[l+7] to 256-bit register
                __m256i vals = _mm256_loadu_si256((__m256i*) &a[l]);

                // update max_val
                max_val = _mm256_max_epi32(max_val, vals);
            }

            // save 256-bit register max_val to an array res
            _mm256_storeu_si256((__m256i*) &res[0], max_val);
            
            // r = final result.
            int r = -INF;
            for (int i = 0; i < 8; i++) {
                r = (r < res[i]) ? res[i] : r;
            }

            // add extra elements at the end
            for (int i = l; i <= y; i++) {
                r = (r < a[i]) ? a[i] : r;
            }
            cout << r << '\n';
        }
    }
    return 0;
}
