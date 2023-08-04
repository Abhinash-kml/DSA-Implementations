#include <iosfwd>
#include <iostream>

#include "..\Containers\stack.hpp"
#include "..\Containers\vector.hpp"
#include "..\Containers\fixedstack.hpp"
#include "..\Containers\fixedqueue.hpp"
#include "..\Containers\SinglyList.hpp"
#include "..\Containers\llstack.hpp"
#include "..\Containers\llqueue.hpp"
#include "..\Containers\array.hpp"

#define NL '\n'

consteval int mul(const int& a, const int& b)
{
    return a * b;
}

int main(int argc, char** argv)
{
    std::cout << "Hello World" << NL;

    array arr = {1, 2, 3, 4, 5};
    for (auto it = arr.begin(); it != arr.end(); ++it)
        std::cout << *it << " ";
    
    std::cout << NL;
    
    vector vec = {1, 2, 3, 4, 5, 6, 7};
    for (auto it = vec.begin(); it != vec.end(); ++it)
        std::cout << *it << " ";

    mul(100, 200);
}