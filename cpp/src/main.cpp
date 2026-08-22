#include <iostream>
#include <memory>
#include <string_view>

int main() {
    auto message = std::make_unique<std::string_view>("C++ environment scaffold is ready");
    std::cout << *message << '\n';
    return 0;
}
