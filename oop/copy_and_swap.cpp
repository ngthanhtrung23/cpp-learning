#include <algorithm>

class DumbArray {
public:
    // default constructor
    DumbArray(int _sz = 0)
        : sz(_sz), arr(sz ? new int[sz]() : nullptr) {}

    // copy constructor
    DumbArray(const DumbArray& other)
            : sz(other.sz), arr(sz ? new int[sz] : nullptr) {
        std::copy(other.arr, other.arr + sz, arr);
    }

    // copy assignment operator, copy and swap idiom
    // Note that other is passed by value
    DumbArray& operator = (DumbArray other) {
        swap(*this, other);
        return *this;
    }

    // move constructor, copy and swap idiom
    DumbArray(DumbArray&& other) : DumbArray() {
        swap(*this, other);
    }

    // move assignment
    DumbArray& operator = (DumbArray&& other) {
        swap(*this, other);
        return *this;
    }

    // for copy and swap
    void swap(DumbArray& a, DumbArray& b) {
        std::swap(a.sz, b.sz);
        std::swap(a.arr, b.arr);
    }

private:
    int sz;
    int *arr;
};

int main() {}
