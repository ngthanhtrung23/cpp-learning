#include <bits/stdc++.h>

// "Deleter" for type FILE*
struct FileCloser {
    void operator () (FILE *fp) const {
        if (fp != nullptr) {
            fclose(fp);
        }
    }
};

int main() {
    FILE *fp = fopen("input.txt", "r");
    // use unique_ptr to manage resource
    std::unique_ptr<FILE, FileCloser> uptr(fp);
}
