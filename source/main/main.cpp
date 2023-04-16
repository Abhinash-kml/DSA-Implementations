#include <iostream>
#include <vector>

#include "../Allocators/allocator.hpp"
#include "../Containers/array.hpp"
#include "../SmartPointers/unique_ptr.hpp"
#include "../SmartPointers/shared_ptr.hpp"

#define NL "\n"

struct test {
    test() = default;
    test(int a, int b, int c, int d) 
        : a{ a }
        , b{ b }
        , c{ c }
        , d{ d }
    { }

    int a, b, c, d;
};

auto println = [](test* ptr) { std::cout << ptr->a << " " << ptr->b << " " << ptr->c << " " << ptr->d << NL; };

int main()
{
    unique_ptr<int[]> ptr{new int[10]};
    std::cout << ptr[4] << NL;
    ptr[4] = 23532532;
    std::cout << ptr[4] << NL;
}