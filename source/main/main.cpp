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
    vector<test> vec{5, test{10, 20, 30, 40}};

    for (size_t i = 0; i < vec.size(); ++i)
        std::cout << vec[i].a << " " << vec[i].b << " " << vec[i].c << " " << vec[i].d << NL;
}