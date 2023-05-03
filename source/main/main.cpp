#include <iosfwd>

#include "../Allocators/allocator.hpp"

#include "../Containers/vector.hpp"
#include "../Types/string.hpp"
#include "../Types/string_view.hpp"
#include "../Containers/list.hpp"

#define NL "\n"

using namespace std::string_literals;

template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const string<T, A>& str)
{
    for (size_t i = 0; i < str.size(); ++i)
        out << str[i];
    
    return out;
}

std::ostream& operator<<(std::ostream& out, string_view& str)
{
    for (size_t i = 0; i < str.size(); ++i)
        out << str[i];
    
    return out;
}

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

auto print = [](string_view view) { std::cout << view << NL; };
auto println = [](const char* str) { 
    std::cout << str << '\n';
};

template<typename T, typename... ArgTypes>
void push_multiple(SinglyList<T>& list, ArgTypes&&... value)
{
    (list.PushBack(value), ...);
}

int main()
{
    SinglyList<int> list{};
    push_multiple(list, 1, 2, 3, 4, 5);
    list.Print().ReverseWithStack().Print();
}