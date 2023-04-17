#pragma once

#include <iostream>
#include <cassert>
#include <memory>

template<typename T>
class allocator;

template<typename T, typename A = allocator<T>>
class vector final
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    vector() = default;

    template<typename Type = T>
    vector(size_t size, Type&& object = Type{})
        : m_size{ size }
        , m_capacity{ size }
        , m_elements{ m_allocator.allocate(size) }
    {
        for (size_t i = 0; i < m_size; ++i)
            new (m_elements + i) T(std::forward<Type>(object));
    }

    template<typename Iter>
    vector(Iter begin, Iter end)
        : m_size{ (size_t)std::distance(begin, end) }
        , m_capacity{ m_size }
        , m_elements{ m_allocator.allocate(m_size) }
    {
        for (auto it = begin, i = 0; it != end; ++it, ++i)
            new (m_elements + i) T(*it);
    }

    vector(std::initializer_list<T> list)
        : m_size{ list.size() }
        , m_capacity{ list.size() }
        , m_elements{ m_allocator.allocate(m_size) }
    {
        for (auto it = list.begin(), i = 0; it != list.end(); ++it, ++i)
            new (m_elements + i) T(*it);
    }

    vector(const vector& other)
        : m_size{ other.m_size }
        , m_capacity{ other.m_capacity }
        , m_elements{ m_allocator.allocate(m_capacity) }
    {
        for (size_t i = 0; i < m_size; ++i)
            new (m_elements + i) T(other.m_elements[i]);
    }

    vector& operator=(const vector& other)
    {
        if (&other == this) return *this;

        vector<T> temp{other};
        temp.swap(this);

        return *this;
    }

    vector(vector&& other)
        : m_size{ 0 }
        , m_capacity{ 0 }
        , m_elements{ nullptr }
    { 
        other.swap(*this);
    }

    vector& operator=(vector&& other)
    { 
        if (&other == this) return *this;

        other.swap(*this);

        return *this;
    }

    ~vector()
    {
        if (!isEmpty())
            clear();

        m_allocator.deallocate(m_elements, m_capacity);
        m_capacity = 0;
    }

public:
    void push_back(const T& element)
    {
        emplace_back(element);
    }

    void push_back(T&& element)
    {
        emplace_back(std::move(element));
    }

    template<typename... Args>
    reference emplace_back(Args&&... args)
    {
        size_t required_capacity = m_size + 1;

        if (required_capacity > m_capacity)
            relocate(required_capacity * 1.5);

        pointer newElement = new (m_elements + m_size) T(std::forward<Args>(args)...);
        return *newElement;
    }

    void pop_back()
    {
        if (isEmpty()) return; 

        m_elements[m_size--].~T();
    }

    void clear()
    {
        if (isEmpty()) return;

        for (size_t i = 0; i < m_size; ++i)
            m_elements[i].~T();
        
        m_size = 0;
    }

    void resize(size_t amount)
    {
        if (amount > m_size)
        {
            reserve(amount);

            for (size_t i = m_size; i < amount; ++i)
                new (m_elements + i) T();
            
            m_size = amount;
            return;
        }

        while (m_size > amount)
            pop_back();
    }

    void reserve(size_t amount)
    {
        if (amount < m_capacity) return;

        relocate(amount);
    }

    void shrink_to_fit()
    {
        relocate(m_size);
    }

    void swap(vector& other)
    {
        using std::swap;
        swap(m_size, other.size);
        swap(m_capacity, other.capacity);
        swap(m_elements, other.m_elements);
        swap(m_allocator, other.m_allocator);
    }

    bool isEmpty() const { return m_size == 0; }

    size_t size() const { return m_size; }
    size_t capacity() const { return m_capacity; }

    pointer begin() { return &m_elements[0]; }
    const_pointer begin() const { return &m_elements[0]; }

    pointer end() { return &m_elements[m_size]; }
    const_pointer end() const { return &m_elements[m_size]; }

    pointer rbegin() { return &m_elements[m_size - 1]; }
    const_pointer rbegin() const { return &m_elements[m_size - 1]; }

    pointer rend() { return &m_elements[-1]; }
    const_pointer rend() const { return &m_elements[-1]; }

    reference operator[](size_t index)
    {
        assert(index >= 0 && index < m_size);
        return m_elements[index];
    }

    const_reference operator[](size_t index) const
    {
        assert(index >= 0 && index < m_size);
        return m_elements[index];
    }

private:
    void relocate(size_t amount)
    {
        if (amount < m_size) return;    // We are comparing against m_size and not m_capacity because, if we compared against m_capacity then shrink() function will not work

        pointer temp = m_allocator.allocate(amount);
        for (size_t i = 0; i < m_size; ++i)
            new (temp + i) T(std::move(m_elements[i]));

        m_allocator.deallocate(m_elements, m_capacity);
        m_elements = temp;
        m_capacity = amount;
    }

private:
    size_t m_size{ 0 };
    size_t m_capacity{ 1 };
    pointer m_elements{ m_allocator.allocate(1) };
    A m_allocator{ };
};

// Explicit deduction guides
template<typename Iter>
vector(Iter begin, Iter end) -> vector<typename std::iterator_traits<Iter>::value_type>;