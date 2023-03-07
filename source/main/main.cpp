#include <iostream>
#include <vector>

#include "../Allocators/allocator.hpp"

#define NL "\n"

int main()
{
    std::vector<int, allocator<int>> vec(5);

    for (int a : vec)
        std::cout << a << " ";
}