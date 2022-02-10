#include <iostream>
#include <thread>
#include <vector>
#include <cassert>
#include <atomic>
#include "debug.h"

int main(int argc, char** argv) {
    assert(argc == 2);
    int N = std::stoi(argv[1]);
    DEBUG(N);

    // shared between threads
    std::atomic<int> x = 0;
    auto inc_x = [&x] () {
        x++;
    };

    // create N threads
    std::vector<std::thread> ts;
    for (int i = 0; i < N; i++) {
        ts.push_back(std::thread(inc_x));
    }

    // wait for all threads to finish
    for (auto& t : ts) {
        t.join();
    }

    // will be == N since we use atomic<int>
    std::cout << "x = " << x << std::endl;
}
