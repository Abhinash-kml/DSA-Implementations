#include <iosfwd>
#include <iostream>

// #include "..\Containers\stack.hpp"
#include "..\Containers\vector.hpp"
// #include "..\Containers\fixedstack.hpp"
// #include "..\Containers\fixedqueue.hpp"
// #include "..\Containers\SinglyList.hpp"
// #include "..\Containers\llstack.hpp"
// #include "..\Containers\llqueue.hpp"
// #include "..\Containers\array.hpp"
#include "..\Containers\queue.hpp"
#include "..\Containers\priority_queue.hpp"


// #include "..\SmartPointers\unique_ptr.hpp"
// #include "..\SmartPointers\shared_ptr.hpp"

// #include "..\Types\pair.hpp"
// #include "..\Types\string.hpp"
#include "..\Types\delegate.hpp"

#define NL '\n'

void Print(const char* str)
{
    std::cout << str << '\n';
}

struct test
{
    test() = default;
    test(int a, int b) : a(a), b(b) {}
    int a{100};
    int b{200};
    void print() { std::cout << "LOLOLOLO" << NL; }
};

class entity
{
public:
    entity() = default;

    void printnc()
    {
        std::cout << "Ptr to Mem Func" << NL;
    }

    void print() const
    {
        std::cout << "Ptr to Const Mem Func" << NL;
    }

    ~entity() { std::cout << "Destroyed" << NL; }
};

int main(int argc, char** argv)
{
    std::cout << "Hello World" << NL;
    delegate<void(const char*)> function;
    function.Bind(&Print);
    function("Lolda lele tu");

    entity tetris;
    delegate<void()> function2;
    function2.Bind(tetris, &entity::print);
    function2();

    priority_queue<int, 10> p;
    p.enqueue(10, 50);
    p.enqueue(20, 40);
    p.enqueue(30, 300);
    p.enqueue(40, 20);
    p.enqueue(50, 10);
    

    for (size_t i = 0; i < 5; ++i)
    {
        const auto& object = p.dequeue();
        std::cout << object.value << " | " << object.priority << NL;
    }
}