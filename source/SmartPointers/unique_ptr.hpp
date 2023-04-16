#pragma once

#include <iostream>
#include <memory>

#define NL "\n"

template<typename T>
struct DefaultDeleter
{
    void operator()(T* ptr)
    {
        delete ptr;
        std::cout << "normal deleter called" << NL;
    }
};

template<typename T>
struct DefaultDeleter<T[]>
{
    void operator()(T* ptr)
    {
        delete[] ptr;
        std::cout << "array deleter called" << NL;
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

    unique_ptr(pointer ptr) 
        : internal{ ptr } 
    { }
    
    template<typename... Args>
    unique_ptr(Args&&... args) 
        : internal{ new T(std::forward<Args>(args)...) } 
    { }

    unique_ptr(const unique_ptr& other) = delete;
    unique_ptr& operator=(const unique_ptr& other) = delete;

    unique_ptr(unique_ptr&& other) noexcept
        : internal{ other.internal }
    { 
        other.internal = nullptr; 
    }

    unique_ptr& operator=(unique_ptr&& other) noexcept
    {
        if (&other == this) return *this;

        internal = other.internal;
        other.internal = nullptr;

        return *this;
    }

    ~unique_ptr()
    {
        if (internal)
            deleter(internal);

        std::cout << "Unique Pointer deleted properly" << NL;
    }

public:
    pointer get() { return internal; }
    const_pointer get() const { return internal; }

    reference operator*() { return *internal; }
    const_reference operator*() const { return *internal; }

    pointer operator->() { return internal; }
    const_pointer operator->() const { return internal; }

    pointer release()
    {
        pointer temp{ internal };
        internal = nullptr;
        return temp;
    }

    void reset(pointer ptr)
    {
        if (internal)
            deleter(internal);
        internal = ptr;
    }

    void swap(unique_ptr& other)
    {
        using std::swap;
        swap(internal, other.internal);
    }

    operator bool() const { return internal; }
    operator pointer() const { return internal; }
private:
    [[no_unique_address]] pointer internal{ nullptr };
    [[no_unique_address]] Deleter deleter{ };
};

// Unique_ptr for array types
template<typename T, typename Deleter>
class unique_ptr<T[], Deleter>
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    unique_ptr(pointer ptr)
        : internal{ ptr }
    { }

    unique_ptr(const unique_ptr& other) = delete;
    unique_ptr& operator=(const unique_ptr& other) = delete;

    unique_ptr(unique_ptr&& other)
        : internal{ other.internal }
    {
        other.internal = nullptr; 
    }

    unique_ptr& operator=(unique_ptr&& other)
    {
        if (&other == this) return *this;

        internal = other.internal;
        other.internal = nullptr;

        return *this;
    }

    ~unique_ptr()
    {
        if (internal)
            deleter(internal);
    }

public:
    reference operator[](size_t index) { return internal[index]; }
    const_reference operator[](size_t index) const { return internal[index]; }

    pointer release()
    {
        pointer temp{internal};
        internal = nullptr;
        return temp;
    }

    void reset(pointer ptr)
    {
        if (internal)
            deleter(internal);

        internal = ptr;
    }

    void swap(unique_ptr& other)
    {
        using std::swap;
        swap(internal, other.internal);
    }

    pointer get() { return internal; }
    const_pointer get() const { return internal; }

    operator bool() const { return internal; }
    operator pointer() const { return internal; }

private:
    pointer internal{ nullptr };
    Deleter deleter{};
};

template<typename T, typename... Args>
auto make_unique(Args&&... args)
{
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}