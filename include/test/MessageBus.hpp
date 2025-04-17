#pragma once
#include <string>
#include <functional>
#include <map>
#include <utility>
#include <vector>
#include "../Utils/Any.hpp"
#include "../Utils/function_traits.hpp"
#include "../Utils/NonCopyable.hpp"

class MessageBus : NonCopyable {
public:
    MessageBus() = default;
    MessageBus(const MessageBus&) = delete;
    MessageBus& operator=(const MessageBus&) = delete;

    // 注册消息处理函数
    template<typename F>
    void Attach(F&& f, const std::string& topic = "") {
        using func_type = typename function_traits<F>::stl_function_type;
        std::string msg_type = topic + typeid(func_type).name();
        m_map.emplace(std::move(msg_type), to_function(std::forward<F>(f)));
    }

    // 发送消息
    template<typename R, typename... Args>
    void SendReq(Args&&... args, const std::string& topic = "") {
        using func_type = std::function<R(Args...)>;
        std::string msg_type = topic + typeid(func_type).name();
        auto range = m_map.equal_range(msg_type);
        for (auto it = range.first; it != range.second; ++it) {
            auto& any_func = it->second;
            auto func = any_func.AnyCast<func_type>();
            func(std::forward<Args>(args)...);
        }
    }

    // 移除消息
    template<typename R, typename... Args>
    void Remove(const std::string& topic = "") {
        using func_type = std::function<R(Args...)>;
        std::string msg_type = topic + typeid(func_type).name();
        auto range = m_map.equal_range(msg_type);
        m_map.erase(range.first, range.second);
    }

private:
    std::multimap<std::string, Any> m_map;
};
