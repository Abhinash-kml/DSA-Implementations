#pragma once

#include <memory>
#include <limits>

template<typename T>
class allocator 
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using this_type = allocator<T>;

    allocator() = default;
    
    ~allocator() = default;

public:
    pointer allocate(size_t amount)
    {
        return static_cast<pointer>(::operator new(sizeof(T) * amount));
    }

    void deallocate(pointer ptr, size_t capacity)
    {
        ::operator delete(ptr);
    }

    template<typename U, typename... Types>
    void construct(U* ptr, Types&&... args)
    {
        new (ptr) U(std::forward<Types>(args)...);
    }

    template<typename U>
    void destruct(U* ptr)
    {
        ptr->~U();
    }

    size_type max_size() const
    {
        return std::numeric_limits<size_type>::max();
    }
    
    template<typename U>
    struct rebind 
    {
        using other = allocator<U>;
    };

private:

};