#pragma once

#include <memory>
#include <numeric>

template<typename T>
class allocator 
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = T&; 
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;

    allocator() = default;
    allocator(const allocator& other) = default;
    allocator& operator=(const allocator& other) = default;
    ~allocator() = default;

public:
    pointer allocate(size_t amount)
    {
        return static_cast<pointer>(::operator new(sizeof(T) * amount));
    }

    void deallocate(pointer ptr, size_t amount)
    {
        ::operator delete(ptr);
    }

    size_t max_size() const 
    {
        return std::numeric_limits<size_type>::max();
    }

    template<typename U, typename... Args>
    void construct(U* ptr, Args&&... args)
    {
        new (ptr) U(std::forward<Args>(args)...);
    }

    template<typename U>
    void destruct(U* ptr)
    {
        ptr->~U();
    }

public: 
    template<typename U>
    struct rebind
    {
        using other = allocator<U>;
    };

private:

};