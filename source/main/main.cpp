#include <iostream>
#include <vector>

#include "../Allocators/allocator.hpp"
#include "../Containers/array.hpp"

#define NL "\n"

int main()
{
    array v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::cout << "Hello World" << NL;

    for (const auto& a : v)
        std::cout << a << " ";
}