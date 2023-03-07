#pragma once

#include <memory>

template<typename T>
class shared_ptr final
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;

    shared_ptr() = default; 

    shared_ptr(pointer ptr)
        : _ptr{ ptr }
        , count{ new size_t(1) }
    { }

    shared_ptr(const shared_ptr& other)
        : _ptr{ other._ptr }
        , count{ other.count }
    {
        ++(*count);
    }

    shared_ptr& operator=(const shared_ptr& other)
    {
        _ptr = other._ptr;
        count = other.count;

        ++(*count);
    }

    shared_ptr(shared_ptr&& other)
        : _ptr{ other._ptr }
        , count{ other.count }
    {
        other._ptr = nullptr;
        other.count = 0;
    }

    shared_ptr& operator=(shared_ptr&& other)
    {
        _ptr = other._ptr;
        count = other.count;

        other._ptr = nullptr;
        other.count = 0;
    }

    ~shared_ptr()
    {
        --(*count);
        if (*count == 0)
        {
            if (_ptr) delete ptr;
            if (count) delete count;
        }
    }
    
private:
    size_t* count{ nullptr };
    pointer _ptr{ nullptr };
};