#pragma once

#include "callables.hpp"

template<typename T>
class delegate;

template<typename Ret, typename... Args>
class delegate<Ret(Args...)>
{
public:
    delegate() = default;

    delegate(const delegate& other) = delete;
    delegate& operator=(const delegate& other) = delete;

    delegate(delegate&& other)
        : m_callable(other.m_callable)
    {
        other.m_callable = nullptr;
    }

    delegate& operator=(delegate&& other)
    {
        m_callable = other.m_callable;
        other.m_callable = nullptr;
    }

    ~delegate()
    {
        if (m_callable) delete m_callable;
    }

public:
    template<typename T>
    void Bind(T& object, Ret(T::*func)(Args...))
    {
        m_callable = new MemberFunctionCallable<T, Ret(Args...)>(object, func);    
    }

    template<typename T>
    void Bind(T& object, Ret(T::*func)(Args...) const)
    {
        m_callable = new ConstMemberFunctionCallable<T, Ret(Args...)>(object, func);
    }

    void Bind(Ret(*func)(Args...))
    {
        m_callable = new FunctionObjCallable<Ret(Args...)>(func);
    }

    Ret operator()(Args&&... args)
    {
        return m_callable->invoke(std::forward<Args>(args)...);
    }

private:
    ICallable<Ret(Args...)>* m_callable{nullptr};
};



