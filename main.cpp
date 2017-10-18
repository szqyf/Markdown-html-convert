#include <iostream>

class A final {
 public:
  A() { std::cout << "Hello"; }
};

int main() {
  A a;
  std::cout << R"(Hello, this is ")";
}