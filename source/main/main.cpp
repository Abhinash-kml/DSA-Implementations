#include <iosfwd>
#include <iostream>

// #include "..\Containers\stack.hpp"
// #include "..\Containers\vector.hpp"
// #include "..\Containers\fixedstack.hpp"
// #include "..\Containers\fixedqueue.hpp"
// #include "..\Containers\SinglyList.hpp"
// #include "..\Containers\llstack.hpp"
// #include "..\Containers\llqueue.hpp"
// #include "..\Containers\array.hpp"

#include "..\SmartPointers\unique_ptr.hpp"
#include "..\SmartPointers\shared_ptr.hpp"

#include "..\Types\pair.hpp"
#include "..\Types\string.hpp"

#define NL '\n'

struct test
{
    test() = default;
    test(int a, int b) : a(a), b(b) {}
    int a{100};
    int b{200};
    void print() { std::cout << "LOLOLOLO" << NL; }
};

int main(int argc, char** argv)
{
    std::cout << "Hello World" << NL;

    string<> str = "Lolwa hai Lolwa";
    std::cout << str;

}