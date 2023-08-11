#pragma once

template<typename T>
class ICallable;

template<typename Ret, typename... Args>
class ICallable<Ret(Args...)>
{
public:
    virtual Ret invoke(Args&&...) = 0;
    virtual ~ICallable() = default;
};

template<typename T>
class FunctionObjCallable;

template<typename Ret, typename... Args>
class FunctionObjCallable<Ret(Args...)> : public ICallable<Ret(Args...)>
{
public:
    using FunctionSignature = Ret(*)(Args...);

    FunctionObjCallable(FunctionSignature func) : m_function(func) {}

    virtual Ret invoke(Args&&... args) override
    {
        return (*m_function)(std::forward<Args>(args)...);
    }

    ~FunctionObjCallable() = default;
private:
    FunctionSignature m_function{};
};

template<typename T, typename Signature>
class MemberFunctionCallable;

template<typename T, typename Ret, typename... Args>
class MemberFunctionCallable<T, Ret(Args...)> : public ICallable<Ret(Args...)>
{
public:
    using PtrToMemFun = Ret(T::*)(Args...);

    MemberFunctionCallable(T& instance, PtrToMemFun func)
        : m_instance(instance)
        , m_function(func)
    {}

    virtual Ret invoke(Args&&... args) override
    {
        return (m_instance.*m_function)(std::forward<Args>(args)...);
    }

    ~MemberFunctionCallable() = default;
private:
    T& m_instance;
    PtrToMemFun m_function{};
};

template<typename T, typename Signature>
class ConstMemberFunctionCallable;

template<typename T, typename Ret, typename... Args>
class ConstMemberFunctionCallable<T, Ret(Args...)> : public ICallable<Ret(Args...)>
{
public:
    using PtrToConstMemFun = Ret(T::*)(Args...) const;

    ConstMemberFunctionCallable(T& instance, PtrToConstMemFun func)
        : m_instance(instance)
        , m_function(func)
    {}

    virtual Ret invoke(Args&&... args) override
    {
        return (m_instance.*m_function)(std::forward<Args>(args)...);
    }

    ~ConstMemberFunctionCallable() = default;
private:
    T& m_instance;
    PtrToConstMemFun m_function{};
};

