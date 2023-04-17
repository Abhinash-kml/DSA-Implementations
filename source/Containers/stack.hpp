#pragma once

#include <memory>
#include <deque>

template<typename T, typename Container = std::deque<T>>
class stack final
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    stack() = default;

    stack(const stack& other)
    {
        for (size_t i = 0; i < other.internal.size(); ++i)
            internal[i] = other.internal[i];
    }

    stack& operator=(const stack& other)
    {
        
    }
    
private:
    Container internal{};
};

// Incomplete 