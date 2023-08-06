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

    shared_ptr<int> ptr;
    {
        shared_ptr<int> ptr2(new int(100));
        ptr = ptr2;
    }

}