#include "Message.h"
#include <utility>
#include <unordered_map>
#include <functional> // 添加此行以使用std::function

std::unordered_multimap<std::string, std::function<void()>> m_map; // 将Any替换为std::function<void()>

//注册可调用对象
template<typename F>
void Attach(const std::string& strTopic, const F& f)
{
    auto func = to_function(f);
    Add(strTopic, std::move(func));
}

//注册成员函数
template <class C, class ... Args, class P>
void Attach(const std::string& strTopic, void(C::*f)(Args...) const, const P& p)
{
    std::function<void(Args...)> func = [&p, f](Args... args)
    {
        return (*p.*f) (std::forward<Args>(args) ...);
    };
    Add(strTopic, std::move(func));
}

template <typename F>
void Add(const std::string& strTopic, F&& f)
{
    std::string strKey = strTopic + typeid(F).name();
    m_map.emplace(std::move(strKey), f);
}