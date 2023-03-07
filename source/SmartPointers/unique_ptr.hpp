#pragma once

#include <memory>
#include <algorithm>

template<typename T>
class unique_ptr final
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;

    unique_ptr() = delete;

    unique_ptr(pointer ptr) 
        : _ptr{ ptr }
    { }
    
    template<typename... Args>
    unique_ptr(Args&&... args)
        : _ptr{ new T(std::forward<Args>(args)...) }
    { }

    unique_ptr(const unique_ptr& other) = delete;
    unique_ptr& operator=(const unique_ptr& other) = delete;
    
    unique_ptr(unique_ptr&& other)
        : _ptr{ other._ptr }
    {
        other._ptr = nullptr;
    }

    unique_ptr& operator=(unique_ptr&& other)
    {
        _ptr = other._ptr;
        other._ptr = nullptr;
    }

    ~unique_ptr()
    {
        if (_ptr) delete _ptr;
    }

public:
    pointer get() { return _ptr; }
    const_pointer get() const { return _ptr; }

    pointer operator->() { return _ptr; }
    const_pointer operator->() const { return _ptr; }

    reference operator*() { return *_ptr; }
    const_reference operator*() { return *_ptr; }

    void reset()
    {
        
    }

    pointer release()
    {
        pointer temp = _ptr;
        _ptr = nullptr;
        return temp;
    }

    void swap(unique_ptr& other)
    {
        using std::swap;

        swap(_ptr, other._ptr);
    }

private:
    pointer _ptr{ nullptr };
};