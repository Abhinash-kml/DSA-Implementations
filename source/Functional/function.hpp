#pragma once

#include <memory>

template<typename T>
class function;

template<typename Ret, typename... ArgTypes>
class function<Ret(ArgTypes...)>
{
public:
    function(Ret(*ptr)(ArgTypes...))
        : m_callable{ std::make_unique<Callable<Ret(*)(ArgTypes...)>>(ptr) }
    { }

    Ret operator()(ArgTypes&&... args)
    {
        return m_callable->invoke(std::forward<ArgTypes>(args)...);
    }

private:
    struct ICallable
    {
        virtual Ret invoke(ArgTypes&&...) = 0;
        virtual ~ICallable() = default;
    };

    template<typename Functor>
    struct Callable : ICallable
    {
        Callable(Functor func) 
            : m_func{ func }
        { }

        Ret invoke(ArgTypes&&... args) override
        {
            return (*m_func)(std::forward<ArgTypes>(args)...);
        }

        virtual ~Callable() override = default;

        Functor m_func;
    };

private:
    std::unique_ptr<ICallable> m_callable;
};

template<typename>
class delegate;

template<typename Ret, typename... Args>
class delegate<Ret(Args...)>
{
public:
    delegate() = default;
    delegate(Ret(*ptr)(Args...))
        : m_callable{ std::make_unique<Callable<Ret(*)(Args...)>>(ptr) }
    { }

    Ret operator()(Args&&... args)
    {
        m_callable->invoke(std::forward<Args>(args)...);
    }
private:
    struct ICallable
    {
        virtual Ret invoke(Args&&...) = 0;
        virtual ~ICallable() = default;
    };

    template<typename Func>
    struct Callable : ICallable
    {
        Callable(Func pfunc) 
            : func{ pfunc }
        { }
        
        virtual Ret invoke(Args&&... args) override
        {
            return (*func)(std::forward<Args>(args)...);
        }

        ~Callable() = default;
    
    private:
        Func func;
    };

private:
    std::unique_ptr<ICallable> m_callable;
};