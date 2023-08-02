#include <iosfwd>
#include <iostream>

#include "..\Containers\stack.hpp"
#include "..\Containers\vector.hpp"
#include "..\Containers\fixedstack.hpp"
#include "..\Containers\fixedqueue.hpp"

#define NL '\n'

int main(int argc, char** argv)
{
    std::cout << "Hello World" << NL;

    fqueue<int, 3> aa{};
    aa.enqueue(1);
    aa.enqueue(2);
    aa.enqueue(3);
    std::cout << std::boolalpha << aa.empty() << std::noboolalpha << aa.count() << std::boolalpha << aa.full() << NL;

    for (auto it = aa.begin(); it != aa.end(); ++it)
        std::cout << *it << " ";
    std::cout << NL;

    aa.enqueue(4);
    aa.dequeue();
    aa.dequeue();
    aa.dequeue();
    aa.dequeue();

}