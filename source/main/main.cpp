#include <iostream>
#include "../Allocators/allocator.hpp"

#include "../Containers/vector.hpp"

#define NL "\n"

struct test {
    test() = default;
    test(int a, int b, int c, int d) 
        : a{ a }
        , b{ b }
        , c{ c }
        , d{ d }
    { }

    test(test&& o)
        : a{ o.a }
        , b{ o.b }
        , c{ o.c }
        , d{ o.d }
    {
        std::cout << "Moved" << NL;
    }

    int a, b, c, d;
};

auto println = [](test* ptr) { std::cout << ptr->a << " " << ptr->b << " " << ptr->c << " " << ptr->d << NL; };

int main()
{
    vector<test> vec(5, test{1, 2, 3, 4});
    vector vec2{1, 2, 3, 4, 5};

    for (const auto& va : vec)
        std::cout << va.a << " " << va.b << " " << va.c << " " << va.d << NL;
}