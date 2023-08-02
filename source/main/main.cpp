#include <iosfwd>
#include <iostream>

#include "..\Containers\stack.hpp"
#include "..\Containers\vector.hpp"
#include "..\Containers\fixedstack.hpp"

#define NL '\n'

int main(int argc, char** argv)
{
    std::cout << "Hello World" << NL;

    fstack<int, 10> stack{};
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);

    for (int i = 0; i < stack.size(); ++i)
        std::cout << stack[i] << " ";

}