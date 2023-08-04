#pragma once

#include <memory>

#define NL '\n'

template<typename T, size_t N>
class fqueue final
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    fqueue() = default;
    fqueue(const fqueue& other) = default;
    fqueue& operator=(const fqueue& other) = default;
    fqueue(fqueue&& other) = default;
    fqueue& operator=(fqueue&& other) = default;
    ~fqueue() = default;

public:
    void enqueue(const_reference object)
    {
        if (empty())
        {
            m_front = 0;
            m_back = -1;

            std::cout << "Queue empty, variables reset" << NL;
        }

        if (full())
        {
            std::cout << "Queue overflow / full" << NL;
            return;
        }

        m_back++;
        m_count++;
        new (m_elements + m_back) T(object);
    }

    void dequeue()
    {
        if (empty())
        {
            m_front = 0;
            m_back = -1;

            std::cout << "Queue empty, variables reset" << NL;

            return;
        }

        m_elements[m_front].~T();

        m_front++;
        m_count--;
    }

    reference peek() 
    { 
        return m_elements[m_front];
    }
    pointer front() 
    {
        if (!empty())
        return &m_elements[m_front];

        return nullptr;
    }
    pointer back() 
    {
        if (!empty())
        return &m_elements[m_back];

        return nullptr;
    }

    pointer begin() { return &m_elements[m_front]; }
    const_pointer begin() const { return &m_elements[m_front]; }

    pointer end() { return &m_elements[m_back + 1]; }
    const_pointer end() const { return &m_elements[m_back + 1]; }

    size_t count() const { return m_count; }

    bool empty() const { return (m_front == -1) || (m_front > m_back); }
    bool full() const { return m_back == (N - 1); }

private:
    T m_elements[N]{};
    int32_t m_front{ -1 };
    int32_t m_back{ -1 };
    int32_t m_count{ 0 };
};