#include <iostream>
#include <vector>

class A {
public:
    virtual void print() {
        std::cout << "class A" << std::endl;
    }
};

class B : public A {
public:
    virtual void print() override {
        std::cout << "class B" << std::endl;
    }
};

int main() {
    std::vector<A*> as;
    as.push_back(new A());
    as.push_back(new B());

    for (auto& a : as) {
        a->print();
    }
}
