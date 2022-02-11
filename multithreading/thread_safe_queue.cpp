#include "thread_safe_queue.hpp"
#include "../debug.h"

int main(int argc, char** argv) {
    assert(argc == 2);
    int N = std::stoi(argv[1]);
    DEBUG(N);

    ThreadSafeQueue<int> qu;
    
    // create N threads
    std::vector<std::thread> ts;
    std::set<int> all_values;
    for (int i : std::views::iota(0, N)) {
        ts.push_back(std::thread(
                [&qu] (int x) { qu.push(x); },
                i));
        ts.push_back(std::thread(
                [&qu, &all_values] () { all_values.insert(qu.pop()); }));
    }

    for (auto& t : ts) {
        t.join();
    }

    DEBUG(all_values.size());
}
