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

    allocator() = default;
    ~allocator() = default;

    constexpr pointer allocate(size_t num)
    {
        return static_cast<pointer>(::operator new(sizeof(T) * num));
    }

    constexpr void deallocate(pointer ptr, size_t size)
    {
        ::operator delete(ptr, size);
    }

    template<typename U, typename... Args>
    constexpr U* construct(U* ptr, Args&&... args)
    {
        return new (ptr) U(std::forward<Args>(args)...);
    }

    template<typename U>
    constexpr void destruct(U* ptr)
    {
        ptr->~U();
    }

    constexpr size_t max_size() 
    { 
        return std::numeric_limits<size_type>::max() / sizeof(T); 
    }

    template<typename U>
    struct rebind
    {
        using other = allocator<U>;
    };

    bool operator==(const allocator& other) { return true; }
    bool operator!=(const allocator& other) { return !operator==(other); }
};