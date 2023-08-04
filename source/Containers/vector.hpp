#pragma once

#include <memory>
#include <cassert>

template<typename T, typename Allocator = std::allocator<T>>
class vector
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

    vector(std::initializer_list<T> list)
        : m_size(list.size())
        , m_capacity(list.size())
        , m_elements(m_allocator.allocate(m_size))
    {
        for (auto it = list.begin(), i = 0; it != list.end(); ++it, ++i)
            new (m_elements + i) T(*it);
    }

    template<typename Iter>
    vector(Iter begin, Iter end)
        : m_size(std::distance(begin, end))
        , m_capacity(m_size)
        , m_elements(m_allocator.allocate(m_size))
    {
        for (auto it = begin, i = 0 ; it != end; ++it, ++i)
            new (m_elements + i) T(*it);
    }

    vector(const vector& other)
        : m_size(other.m_size)
        , m_capacity(other.m_capacity)
        , m_elements(m_allocator.allocate(m_size))
    {
        for (size_t i = 0; i < m_size; ++i)
            new (m_elements + i) T(other.m_elements[i]);
    }

    vector& operator=(const vector& other)
    {   
        if (&other == this) return *this;

        vector temp{ other };
        swap(*this, temp);

        return *this;
    }

    vector(vector&& other)
        : m_size(0)
        , m_capacity(0)
        , m_elements(nullptr)
    {
        swap(*this, other);
    }

    vector& operator=(vector&& other)
    {
        if (&other == this) return *this;

        swap(*this, other);

        return *this;
    }

    ~vector()
    {
        if (!empty())
            clear();

        // Safe to deallocate the buffer
        m_allocator.deallocate(m_elements, m_capacity);
        m_capacity = 0;
    }

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

public:
    void push_back(const T& object)
    {
        emplace_back(object);
    }

    void push_back(T&& object)
    {
        emplace_back(std::move(object));
    }

    template<typename... Args>
    reference emplace_back(Args&&... args)
    {
        if (m_size + 1 > m_capacity)
        relocate(m_capacity * 1.5);

        pointer object = new (m_elements + m_size) T(std::forward<Args>(args)...);
        m_size++;
        return *object;
    }

    void pop_back()
    {
        if (empty()) return;

        m_elements[--m_size].~T();
    }

    void resize(size_t amount)
    {
        if (amount > m_size)
        {
            reserve(amount);

            for (size_t i = m_size; i < amount; ++i)
                new (m_elements + i) T();

            m_size = amount;
        }

        while (m_size > amount)
            pop_back();
        
    }

    void reserve(size_t amount)
    {
        if (amount < m_capacity) return;

        relocate(amount);
    }

    void clear()
    {
        if (empty()) return;

        for (size_t i = 0; i < m_size; ++i)
            m_elements[i].~T();

        m_size = 0;
    }

    void shrink_to_fit()
    {
        relocate(m_size);
    }

    void assign(size_t count, const_reference object)
    {
        if (m_capacity < count)
            reserve(count);

        for (size_t i = 0; i < count; ++i)
            new (m_elements + i) T(object);
    }

    void swap(vector& other)
    {
        using std::swap;
        swap(m_elements, other.m_elements);
        swap(m_allocator, other.m_allocator);
        swap(m_capacity, other.m_capacity);
        swap(m_size, other.m_size);
    }

    void swap(vector&& other)
    {
        using std::swap;
        swap(m_elements, other.m_elements);
        swap(m_allocator, other.m_allocator);
        swap(m_capacity, other.m_capacity);
        swap(m_size, other.m_size);
    }

    pointer data() { return m_elements; }
    const_pointer data() const { return m_elements; }
    
    reference front() { return m_elements[0]; }
    const_reference front() const { return m_elements[0]; }

    reference back() { return m_elements[m_size - 1]; }
    const_reference back() const { return m_elements[m_size - 1]; }

    reference at(size_t index) { return operator[](index); }
    const_reference at(size_t index) const { return operator[](index); }

    bool empty() const { return m_size == 0; }
    bool full() const { return m_size == m_capacity; }
    size_t size() const { return m_size; }
    size_t capacity() const { return m_capacity; }

    pointer begin() { return &m_elements[0]; }
    const_pointer begin() const { return &m_elements[0]; }

    pointer end() { return &m_elements[m_size]; }
    const_pointer end() const { return &m_elements[m_size]; }

    pointer rbegin() { return &m_elements[m_size - 1]; }
    const_pointer rebgin() const { return &m_elements[m_size - 1]; }

    pointer rend() { return &m_elements[-1]; }
    const_pointer rend() const { return &m_elements[-1]; }

private:
    void relocate(size_t amount)
    {
        if (amount < m_size) return; // We are comparing against m_size and not m_capacity because, if we compared against m_capacity then shrink() function will not work

        pointer newBlock = m_allocator.allocate(amount);
        for (size_t i = 0; i < m_size; ++i)
            new (newBlock + i) T(std::move(m_elements[i]));
        
        m_allocator.deallocate(m_elements, m_capacity);
        m_elements = newBlock;
        m_capacity = amount;
    }

private:
    Allocator m_allocator;
    size_t m_size{ 0 };
    size_t m_capacity{ 1 };
    pointer m_elements{ m_allocator.allocate(1) };
};

// Deduction guides
template<typename Iter>
vector(Iter begin, Iter end) -> vector<typename std::iterator_traits<Iter>::value_type>;

template<typename T, typename... U>
vector(T, U...) -> vector<T>;