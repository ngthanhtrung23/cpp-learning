// Tested using https://judge.yosupo.jp/problem/matrix_product

#include <iostream>
#include <cstring>
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

int* read(int n) {
    int* res = new int[n];
    for (int i = 0; i < n; i++) {
        res[i] = IO::get<int>();
    }
    return res;
}

const int MOD = 998244353;

// 5.18s
// https://judge.yosupo.jp/submission/78253
int* naive_matrix_mul(int* a, int* b, int n_row_a, int n_col_a, int n_col_b) {
    int* c = new int[n_row_a * n_col_b];
    for (int i = 0; i < n_row_a; i++) {
        for (int j = 0; j < n_col_b; j++) {
            c[i*n_col_b+j] = 0;
            for (int k = 0; k < n_col_a; k++) {
                c[i*n_col_b + j] = (c[i*n_col_b + j] + a[i*n_col_a + k] * (long long) b[k*n_col_b + j]) % MOD;
            }
        }
    }
    return c;
}

int* transpose(int* a, int n_row, int n_col) {
    int* res = new int[n_row * n_col];
    for (int i = 0; i < n_row; i++) {
        for (int j = 0; j < n_col; j++) {
            res[j*n_row + i] = a[i*n_col + j];
        }
    }
    return res;
}

// https://judge.yosupo.jp/submission/78256
// 3.57s
int* transpose_matrix_mul(int* a, int* b, int n_row_a, int n_col_a, int n_col_b) {
    int* bb = transpose(b, n_col_a, n_col_b);

    int* c = new int[n_row_a * n_col_b];
    for (int i = 0; i < n_row_a; i++) {
        for (int j = 0; j < n_col_b; j++) {
            c[i*n_col_b+j] = 0;
            for (int k = 0; k < n_col_a; k++) {
                c[i*n_col_b + j] = (c[i*n_col_b + j] + a[i*n_col_a + k] * (long long) bb[j*n_col_a + k]) % MOD;
            }
        }
    }
    return c;
}

int main() {
    // read input
    int N = IO::get<int>();
    int M = IO::get<int>();
    int K = IO::get<int>();

    int* a = read(N*M);
    int* b = read(M*K);


    int* c = transpose_matrix_mul(a, b, N, M, K);
    for (int i = 0; i < N*K; i++) {
        cout << c[i] << ' ';
    }
    cout << endl;
}
