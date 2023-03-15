#pragma once

#include <memory>

template<typename T>
struct DefaultDeleter
{
    DefaultDeleter() = default;

    template<typename U>
    DefaultDeleter(const DefaultDeleter<U>& other) {}

    void operator()(T* ptr)
    {
        delete ptr;
    }
};

template<typename T>
struct DefaultDeleter<T[]>
{
    DefaultDeleter() = default;

    template<typename U>
    DefaultDeleter(const DefaultDeleter<U[]>& other) {}

    void operator()(T* ptr)
    {
        delete[] ptr;
    }
};

template<typename T, typename Deleter = DefaultDeleter<T>>
class unique_ptr final
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    unique_ptr() = default;

    explicit unique_ptr(pointer ptr) : internal{ ptr } {}
    
    template<typename... Types>
    unique_ptr(Types&&... args) : internal{ new T(std::forward<Types>(args)...) } {}

    unique_ptr(const unique_ptr& other) = delete;
    unique_ptr& operator=(const unique_ptr& other) = delete;

    unique_ptr(unique_ptr&& other)
        : internal{ other.internal }
    { 
        other.internal = nullptr;
    }

    unique_ptr& operator=(unique_ptr&& other)
    {
        internal = other.internal;
        other.internal = nullptr;
    }

    ~unique_ptr()
    {
        if (internal) delete internal;
    }

public:
    pointer get() { return internal; }
    const_pointer get() const { return internal; }

    pointer operator->() { return internal; }
    const_pointer operator->() const { return internal; }

    reference operator*() { return *internal; }
    const_reference operator*() const { return *internal; }

    pointer release()
    {
        pointer temp = internal;
        internal = nullptr;
        return temp;
    }

    void reset(pointer ptr)
    {
        release();
        internal = ptr;
    }

    operator bool() const { return internal; }
    operator pointer() { return internal; }

private:
    pointer internal{ nullptr };
};