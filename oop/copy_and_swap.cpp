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
    DumbArray& operator = (DumbArray other) {
        swap(*this, other);
        return *this;
    }

    // move constructor, copy and swap idiom
    DumbArray(DumbArray&& other) : DumbArray() {
        swap(*this, other);
    }

    // move assignment - not needed because we use pass-by-value assignment operator
    /*
    DumbArray& operator = (DumbArray&& other) {
        swap(*this, other);
        return *this;
    }
    */

    // for copy and swap
    void swap(DumbArray& a, DumbArray& b) {
        std::swap(a.sz, b.sz);
        std::swap(a.arr, b.arr);
    }

    ~DumbArray() {
        delete [] arr;
    }

private:
    int sz;
    int *arr;
};

int main() {}
