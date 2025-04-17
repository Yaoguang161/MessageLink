#include "../include/test/MessageBus.hpp"
#include <iostream>
#include <string>
#include <vector>

MessageBus g_bus;
const std::string Topic = "Compute";

struct Adder {
    Adder() {
        g_bus.Attach([](int x) {
            return x + 10;
        }, Topic);
    }
};

struct Multiplier {
    Multiplier() {
        g_bus.Attach([](int x) {
            return x * 2;
        }, Topic);
    }
};

struct Subtractor {
    Subtractor() {
        g_bus.Attach([](int x) {
            return x - 5;
        }, Topic);
    }
};

void TestSendReqWithResults() {
    Adder a;
    Multiplier m;
    Subtractor s;

    // 广播请求并收集所有返回值
    std::vector<int> results = g_bus.SendReqWithResults<int, int>(20, Topic);

    std::cout << "结果列表: ";
    for (int v : results) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    // 输出应为：30 40 15
}