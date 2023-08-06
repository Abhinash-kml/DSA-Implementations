#pragma once

#include <memory>

// Default deleter;
template<typename T>
struct DefaultDeleter
{
    void operator()(T* ptr)
    {
        delete ptr;
    }
};

template<typename T>
struct DefaultDeleter<T[]>
{
    void operator()(T* ptr)
    {
        delete[] ptr;
    }
};

// Main smart pointer class

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
    
    explicit unique_ptr(pointer ptr)
        : m_internal(ptr)
    {}

    unique_ptr(const unique_ptr& other) = delete;
    unique_ptr& operator=(const unique_ptr& other) = delete;

    unique_ptr(unique_ptr&& other)
        : m_internal(other.m_internal)
        , m_deleter(std::move(other.m_deleter))
    {
        other.m_internal = nullptr;
    }

    unique_ptr& operator=(unique_ptr&& other)
    {
        m_internal = other.m_internal;
        m_deleter = std::move(other.m_deleter);
        other.m_internal = nullptr;
    }

    ~unique_ptr()
    {
        m_deleter(m_internal);
    }

public:
    pointer get() { return m_internal; }
    const_pointer get() const { return m_internal; }

    pointer operator->() { return m_internal; }
    const_pointer operator->() const { return m_internal; }

    reference operator*() { return *m_internal; }
    const_reference operator*() const { return *m_internal; }

    pointer release()
    {
        pointer temp{m_internal};
        m_internal = nullptr;
        return temp;
    }

    void reset(pointer ptr = nullptr)
    {
        if (m_internal)
            m_deleter(m_internal);
        
        m_internal = ptr;
    }

    void swap(unique_ptr& other)
    {
        using std::swap;
        swap(m_internal, other.m_internal);
        swap(m_deleter, other.m_deleter);
    }

    operator bool() const { return m_internal; }
private:
    pointer m_internal{nullptr};
    Deleter m_deleter{};
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

    unique_ptr() = default;

    unique_ptr(pointer ptr)
        :   m_ptr(ptr)
    {}

    unique_ptr(const unique_ptr& other) = delete;
    unique_ptr& operator=(const unique_ptr& other) = delete;

    unique_ptr(unique_ptr&& other)
        : m_ptr(other.m_ptr)
        , m_deleter(other.m_deleter)
    {
        other.m_ptr = nullptr;
    }

    unique_ptr& operator=(unique_ptr&& other)
    {
        m_ptr = other.m_ptr;
        m_deleter = other.m_deleter;

        other.m_ptr = nullptr;
    }

    ~unique_ptr()
    {
        if (m_ptr)
        m_deleter(m_ptr);
    }

public:
    pointer get() { return m_ptr; }
    const_pointer get() const { return m_ptr; }

    pointer operator->() { return m_ptr; }
    const_pointer operator->() const { return m_ptr; }

    reference operator*() { return *m_ptr; }
    const_reference operator*() const { return *m_ptr; }

    pointer release()
    {
        pointer temp{m_ptr};
        m_ptr = nullptr;
        return temp;
    }

    void reset(pointer ptr = nullptr)
    {
        if (m_ptr)
        m_deleter(m_ptr);

        m_ptr = ptr;
    }

    void swap(unique_ptr& other)
    {
        using std::swap;
        swap(m_ptr, other.m_ptr);
        swap(m_deleter, other.m_deleter);
    }

    void swap(unique_ptr&& other)
    {
        using std::swap;
        swap(m_ptr, other.m_ptr);
        swap(m_deleter, other.m_deleter);
    }

    reference operator[](size_t index)
    {
        return m_ptr[index];
    }

    operator bool() const { return m_ptr; }
private:
    pointer m_ptr{};
    Deleter m_deleter{};
};

// Helper functions
template<typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args)
{
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

