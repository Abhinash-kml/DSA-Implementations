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