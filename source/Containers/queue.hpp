#pragma once

#include <vector>
#include <memory>
#include <cassert>

template<typename T>
class queue final
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    queue() = default;
    queue(const queue& other) = default;
    queue& operator=(const queue& other) = default;
    queue(queue&& other) = default;
    queue& operator=(queue&& other) = default;
    ~queue() = default;

    reference operator[](size_t index)
    {
        return m_array[index];
    }

    const_reference operator[](size_t index) const 
    {
        return m_array[index];
    }

    pointer begin() { return &m_array[0]; }
    const_pointer begin() const { return &m_array[0]; }

    pointer end() { return &m_array[m_array.size()]; }
    const_pointer end() const { return &m_array[m_array.size()]; }
    
public:
    void enqueue(const value_type& object)
    {
        m_array.push_back(object);
    }

    void dequeue()
    {
        m_array.erase(m_array.cbegin());
    }

    reference peek() { return m_array.begin(); }
    const_reference peek() const { return m_array.cbegin(); }

    void print()
    {
        for (auto& element : m_array)
            std::cout << element << " ";

        std::cout << '\n';
    }

private:
    std::vector<T> m_array{};
    int32_t m_front{0};
    int32_t m_back{-1};
};