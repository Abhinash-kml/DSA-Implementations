#pragma once

#include <cassert>
#include <type_traits>

template<typename T1, typename T2>
class pair final
{
public:
    pair() = default;

    pair(T1 first, T2 second)
        : m_first(first)
        , m_second(second)
    {}

    pair(const pair& other)
        : m_first(other.m_first)
        , m_second(other.m_second)
    {}

    pair& operator=(const pair& other)
    {
        if (&other == this) return *this;

        m_first = other.m_first;
        m_second = other.m_second;

        return *this;
    }

    pair(pair&& other)
        : m_first(std::move(other.m_first))
        , m_second(std::move(other.m_second))
    {}

    pair& operator=(pair&& other)
    {
        if (&other == this) return *this;

        m_first = std::move(other.m_first);
        m_second = std::move(other.m_second);

        return *this;
    }

public:
    T1& first() { return m_first; }
    const T1& first() const { return m_first; }

    T2& second() { return m_second; }
    const T2& second() const { return m_second; }

    // This only works if both T1 and T2 are same type, else it doesnt;
    // Tried one version with std::conditional but didnt that also works onlyu if both types are same.
    template<size_t N>
    std::enable_if_t<std::is_same_v<T1, T2>, T1> get()
    {
        if (!N) return m_first;
        else return m_second;
    }

    bool operator==(const pair& rhs) const
    {
        return m_first == rhs.m_first && m_second == rhs.m_second;
    }

    bool operator!=(const pair& rhs) const
    {
        return !operator==(rhs);
    }

    operator bool() const { return m_first || m_second; }

private:
    T1 m_first{};
    T2 m_second{};
};