#pragma once

#include <iostream>
#include <memory>

#define NL "\n"

template<typename T>
class shared_ptr final
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    shared_ptr() = default;

    shared_ptr(pointer ptr) 
        : internal{ ptr }
        , counter{ new int(1) }
    { }

    shared_ptr(const shared_ptr& other)
        : internal{ other.internal }
        , counter{ other.counter }
    { 
        ++(*counter);
    }

    shared_ptr& operator=(const shared_ptr& other)
    {
        if (&other == this) return *this;

        internal = other.internal;
        counter = other.counter;
        ++(*counter);

        return *this;
    }

    shared_ptr(shared_ptr&& other) noexcept
        : internal{ other.internal }
        , counter{ other.counter }
    { 
        other.internal = nullptr;
        other.counter = nullptr;
    }

    shared_ptr& operator=(shared_ptr&& other) noexcept
    {
        if (&other == this) return *this;

        internal = other.internal;
        counter = other.counter;

        other.internal = nullptr;
        other.counter = nullptr;

        return *this;
    }

    ~shared_ptr()
    {
        if ((*counter) != 0)
        {
            --(*counter);
            std::cout << "Counter = " << *counter << NL;

            if ((*counter) == 0)
            {
                delete internal;
                delete counter;

                std::cout << "Object completely deleted" << NL;
            }
        }
    }

public:
    pointer operator->() { return internal; }
    const_pointer operator->() const { return internal; }

    reference operator*() { return *internal; }
    const_reference operator*() const { return *internal; }

    size_t getRefCounts() const { return *counter; }
    
    pointer get() { return internal; }
    pointer get() const { return internal; }

    void reset(pointer ptr)
    {
        if (*internal && *counter)
        {
            delete internal;
            delete counter;
        }

        internal = ptr;
        counter = new int(1);
    }

    void swap(shared_ptr& other)
    {
        using std::swap;
        
        swap(internal, other.internal);
        swap(counter, other.counter);
    }

private:
    pointer internal{ nullptr };
    int* counter{ nullptr };
};

// Make shared
template<typename T, typename... Args>
auto make_shared(Args&&... args)
{
    return shared_ptr<T>(new T(std::forward<Args>(args)...));
}