#pragma once

#include <memory>

#include "./SinglyList.hpp"

// Stack using singly link list

template<typename T>
class llstack final
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    llstack() = default;
    llstack(const llstack& other) = default;
    llstack& operator=(const llstack& other) = default;
    llstack(llstack&& other) = default;
    llstack& operator=(llstack&& other) = default;
    ~llstack() = default;

public:
    void push(const_reference object)
    {
        list.insert(object);
        m_size++;
    }

    void pop()
    {
        list.removeAtIndex(m_size--);
    }

    size_t size() { return m_size; }

    void print() { list.print(); }

private:
    SinglyList<T> list{};
    size_t m_size{};
};