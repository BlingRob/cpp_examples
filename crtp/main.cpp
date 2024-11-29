#include <iostream>

template <typename Derived>
class Base {
public:
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }

    void implementation() {
        std::cout << "Default implementation in Base" << std::endl;
    }
};

class Derived1 : public Base<Derived1> {
public:
    void implementation() {
        std::cout << "Custom implementation in Derived1" << std::endl;
    }
};

class Derived2 : public Base<Derived2> {
    // No custom implementation, so Base::implementation will be used.
};

int main() {
    Derived1 d1;
    d1.interface();  // Output: "Custom implementation in Derived1"

    Derived2 d2;
    d2.interface();  // Output: "Default implementation in Base"

    return 0;
}