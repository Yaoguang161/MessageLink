#pragma once
#include <functional>
#include <tuple>
#include <type_traits>

// 主模板
template <typename T>
struct function_traits;

// 普通函数
template <typename Ret, typename... Args>
struct function_traits<Ret(Args...)> {
    using return_type = Ret;
    using stl_function_type = std::function<Ret(Args...)>;
    using pointer = Ret(*)(Args...);
    static constexpr std::size_t arity = sizeof...(Args);

    template <std::size_t N>
    struct args {
        static_assert(N < arity, "function_traits: invalid parameter index.");
        using type = typename std::tuple_element<N, std::tuple<Args...>>::type;
    };
};

// 函数指针
template <typename Ret, typename... Args>
struct function_traits<Ret(*)(Args...)> : function_traits<Ret(Args...)> {};

// std::function
template <typename Ret, typename... Args>
struct function_traits<std::function<Ret(Args...)>> : function_traits<Ret(Args...)> {};

// 成员函数指针（const、volatile 都覆盖）
#define FUNCTION_TRAITS_CV(...) \
template <typename Ret, typename ClassType, typename... Args> \
struct function_traits<Ret(ClassType::*)(Args...) __VA_ARGS__> : function_traits<Ret(Args...)> {};

FUNCTION_TRAITS_CV()
FUNCTION_TRAITS_CV(const)
FUNCTION_TRAITS_CV(volatile)
FUNCTION_TRAITS_CV(const volatile)
#undef FUNCTION_TRAITS_CV

// lambda 或仿函数对象（推导 operator()）
template <typename Callable>
struct function_traits : function_traits<decltype(&Callable::operator())> {};

// to_function：统一转换为 std::function 类型
template <typename Function>
typename function_traits<Function>::stl_function_type to_function(Function&& f) {
    return static_cast<typename function_traits<Function>::stl_function_type>(std::forward<Function>(f));
}
