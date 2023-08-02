#pragma once

#include <memory>
#include <cassert>

#include "./vector.hpp"

template<typename T>
class stack final
{
public:
    using value_type = typename vector<T>::value_type;
    using size_type = typename vector<T>::size_type;
    using difference_type = typename vector<T>::difference_type;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    stack() = default;
    stack(const stack& other) = default;
    stack& operator=(const stack& other) = default;
    stack(stack&& other) = default;
    stack& operator=(stack&& other) = default;
    ~stack() = default;

    constexpr reference operator[](size_t index)
    {
        assert(index >= 0 && index < m_elements.size());
        return m_elements[index];
    }

    constexpr const_reference operator[](size_t index) const
    {
        assert(index >= 0 && index < m_elements.size());
        return m_elements[index];
    }

public:

    template<typename... Args>
    constexpr void push(Args&&... args)
    {
        m_elements.emplace_back(std::forward<Args>(args)...);
    }

    constexpr void pop()
    {
        if (m_elements.empty()) return;

        m_elements.pop_back();
    }

    constexpr reference front() { return m_elements.front(); }
    constexpr const_reference front() const { return m_elements.front(); }

    constexpr reference back() { return m_elements.back(); }
    constexpr const_reference back() const { return m_elements.back(); }

    constexpr bool full() const { return m_elements.full(); }
    constexpr bool empty() const { return m_elements.empty(); }
    constexpr size_t size() const { return m_elements.size(); }

    constexpr pointer begin() { return m_elements.begin(); }
    constexpr const_pointer begin() const { return m_elements.begin(); }

    constexpr pointer end() { return m_elements.end(); }
    constexpr const_pointer end() const { return m_elements.end(); }

    constexpr pointer rbegin() { return m_elements.rbegin(); }
    constexpr const_pointer rbegin() const { return m_elements.rebgin(); }

    constexpr pointer rend() { return m_elements.rend(); }
    constexpr const_pointer rend() const { return m_elements.rend(); }

private:
    vector<T> m_elements{};
};