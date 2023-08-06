#pragma once

#include <memory>
#include <utility>
#include <atomic>

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
        : m_ptr(ptr)
        , m_count(new uint32_t(0))
    {
        (*m_count)++;
    }

    shared_ptr(const shared_ptr& other)
        : m_ptr(other.m_ptr)
        , m_count(other.m_count)
    {
        (*m_count)++;
    }

    shared_ptr& operator=(const shared_ptr& other)
    {
        if (&other == this) return *this;

        m_ptr = other.m_ptr;
        m_count = other.m_count;
        (*m_count)++;

        return *this;
    }

    shared_ptr(shared_ptr&& other)
        : m_ptr(other.m_ptr)
        , m_count (other.m_count)
    {
        other.m_ptr = nullptr;
        other.m_count = nullptr;
    }

    shared_ptr& operator=(shared_ptr&& other)
    {
        if (&other == this) return *this;

        m_ptr = std::exchange(other.m_ptr, nullptr);
        m_count = std::exchange(other.m_count, nullptr);

        return *this;
    }

    ~shared_ptr()
    {
        if (m_ptr && m_count)
        {
            if (--(*m_count) == 0)
            {
                delete m_ptr;
                m_ptr = nullptr;
            }
            else
            {
                --(*m_ptr);
            }
        }
    }

public:
    pointer get() { return m_ptr; }
    const_pointer get() const { return m_ptr; }

    pointer operator->() { return m_ptr; }
    const_pointer operator->() const { return m_ptr; }

    reference operator*() { return *m_ptr; }
    const_reference operator*() const { return *m_ptr; }

    size_t refcount() const { return *m_count ? *m_count : 0; }
private:
    pointer m_ptr{nullptr};
    uint32_t* m_count{nullptr};
};