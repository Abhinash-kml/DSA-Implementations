#pragma once

#include <memory>

template<typename T, size_t N>
class dequeue final
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    dequeue() = default;
    dequeue(const dequeue& other) = default;
    dequeue& operator=(const dequeue& other) = default;
    dequeue(dequeue&& other) = default;
    dequeue& operator=(dequeue&& other) = default;
    ~dequeue() = default;

public:
    void push_front(const_reference object)
    {
        if (isfull()) 
        {
            std::cout << "Queue overflow, full" << '\n';
            return;
        }

        if (isempty())
        {
            m_head = 0;
            m_tail = N - 1;
        }

        new (&arr[m_head]) T(object);
        m_head++;
        m_count++;
    }

    /*void remove_front()
    {
        if (isempty())
        {
            std::cout << "Queue uderflow, empty" << '\n';
            return;
        }

        arr[m_head].~T();
        m_head--;
        m_count--;
    }*/

    void remove_front()
    {
        if (isempty())
        {
            std::cout << "Queue uderflow, empty" << '\n';
            return;
        }

        arr[m_head - m_head].~T();
        m_headstart++;
        m_head--;
        m_count--;
    }

    void push_back(const_reference object)
    {
        if (isfull())
        {
            std::cout << "Queue overflow, full" << '\n';
            return;
        }

        if (isempty())
        {
            m_head = 0;
            m_tail = N - 1;
        }

        new (&arr[m_tail]) T(object);
        m_tail--;
        m_count++;
    }

    void remove_back()
    {
        if (isempty())
        {
            std::cout << "Queue underflow, empty" << '\n';
            return;
        }

        arr[m_tail].~T();
        m_tailstart--;
        m_tail++;
        m_count--;
    }

    reference getfront()
    {
        if (!isempty()) return arr[m_head];
    }

    reference getback()
    {
        if (!isempty()) return arr[m_tail];
    }

    void print()
    {
        for (size_t i = m_headstart; (m_headstart == 0 ? i < m_head : i <= m_head); ++i)
            std::cout << arr[i] << " ";

        std::cout << "| ";

        for (size_t i = m_tail + 1; i < N; ++i)
            std::cout << arr[i] << " ";

        std::cout << '\n';
    }

    bool isfull() const { return (m_head == N - 1 || m_tail == 0) || (m_tail == m_head + 1); }
    bool isempty() const { return (m_head == -1); }

private:
    T arr[N];
    int32_t m_head{-1};
    int32_t m_headstart{0};
    int32_t m_tailstart{N -1};
    int32_t m_tail{-1};
    int32_t m_count{0};
};