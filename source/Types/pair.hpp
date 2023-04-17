#pragma once

template<typename First, typename Second>
struct pair final
{
    First first() { return m_first; }
    Second second() { return m_second; }

    First m_first{};
    Second m_second{};
};