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
// #include "..\Containers\queue.hpp"
// #include "..\Containers\priority_queue.hpp"
// #include "..\Containers\dequeue.hpp"
#include "..\Containers\hashtable.hpp"

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

    HashTable<int, const char*> map(5);
    map.insert(1, "Awinash");
    map.insert(2, "komal");
    map.insert(3, "Bikki");
    map.insert(4, "Puspa");
    map.insert(5, "Basanta");

    std::cout << *map.get(1) << NL;
}