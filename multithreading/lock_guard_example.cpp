#include <iostream>
#include <thread>
#include <vector>
#include <cassert>
#include <mutex>
#include "debug.h"

int main(int argc, char** argv) {
    assert(argc == 2);
    int N = std::stoi(argv[1]);
    DEBUG(N);

    // shared between threads
    int x = 0;
    std::mutex m;
    auto inc_x = [&x, &m] () {
        std::lock_guard<std::mutex> lock(m);
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

    // will be < N because of race condition
    std::cout << "x = " << x << std::endl;
}
