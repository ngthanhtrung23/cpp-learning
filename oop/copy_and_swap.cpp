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
    // Notes:
    // - other is passed by value
    // - no longer needs move assignment operator
    // - fixes self-assignment, and also assignment of recursive DS
    DumbArray& operator = (DumbArray other) noexcept {
        swap(*this, other);
        return *this;
    }

    // move constructor, copy and swap idiom
    DumbArray(DumbArray&& other) noexcept : DumbArray() {
        swap(*this, other);
    }

    /**
     * How to write move constructor without copy and swap?
     * We need to clean up other, otherwise will have double-free
    DumbArray(DumbArray&& other) noexcept
        : sz(std::move(other.sze)),
          arr(std::exchange(other.arr, nullptr)) {}
     */

    // move assignment - not needed because we use pass-by-value assignment operator
    /*
    DumbArray& operator = (DumbArray&& other) {
        swap(*this, other);
        return *this;
    }
    */

    // for copy and swap
    friend void swap(DumbArray& a, DumbArray& b) noexcept {
        std::swap(a.sz, b.sz);
        std::swap(a.arr, b.arr);
    }

    ~DumbArray() noexcept {
        delete [] arr;
    }

private:
    int sz;
    int *arr;
};

int main() {}
