#include <thread>
#include "../debug.h"

int main() {
    DEBUG(std::thread::hardware_concurrency());
}
