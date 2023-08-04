#pragma once

#include <memory>

#include "./SinglyList.hpp"

// A queue data structure implemented using Singly link list\

template<typename T>
class llqueue final
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    llqueue() = default;
    llqueue(const llqueue& other) = default;
    llqueue& operator=(const llqueue& other) = default;
    llqueue(llqueue&& other) = default;
    llqueue& operator=(llqueue&& other) = default;
    ~llqueue() = default;

public:
    void enqueue(const_reference object)
    {
        list.insert(object);
        m_count++;
    }

    void dequeue()
    {
        list.removeAtHead();
        m_count--;
    }

    void print() { list.print(); }

    size_t size() const { return m_count; }

private:
    SinglyList<T> list{};
    size_t m_count{};
};