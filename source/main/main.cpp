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

int main()
{
    List<int> list{};
    list.insert(120)
        .insert(240)
        .insert(480)
        .insert(240)
        .insert(240)
        .insert(240);

    list.print();

    list.erase(240, true)
        .print();
    list.search(120);
}