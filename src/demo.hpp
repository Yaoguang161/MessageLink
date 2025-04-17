#include "../include/test/MessageBus.hpp"

MessageBus g_bus;
const std::string Topic = "Drive";

struct Subject
{
    void SendReq(const std::string& topic)
    {
        g_bus.SendReq<void, int>(50, topic);
    }
};

struct Car
{
    Car()
    {
        g_bus.Attach([this](int speed){ Drive(speed); }, Topic);

    }

    void Drive(int speed)
    {
        std::cout << "Car drive " << speed << std::endl;
    }
};

struct Bus
{
    Bus()
    {
        g_bus.Attach([this](int speed){Drive(speed);}, Topic);
    }

    void Drive(int speed)
    {
        std::cout << "Bus drive " << speed << std::endl;
    }
};

struct Truck
{
    Truck()
    {
        g_bus.Attach([this](int speed){Drive(speed);});
    }

    void Drive(int speed)
    {
        std::cout << "Truck drive " << speed << std::endl;
    }
};

void TestBus() {
    //一般使用
    Subject subject;
    Car car;
    Bus bus;
    Truck truck;
    subject.SendReq(Topic); // ✅ 会通知 Car, Bus, Truck
    subject.SendReq("");    // ❌ 不会有任何输出（除非有默认注册）
    g_bus.Remove<void, int>(Topic);
    subject.SendReq(Topic); // ❌ 所有 listener 已被移除，不会有输出

    //简化使用
    g_bus.Attach([](int s){ std::cout << s; }, "Drive");  // 注册 handler
    g_bus.SendReq<void, int>(50, "Drive");                  // ✅ 会调用
    g_bus.Remove<void, int>("Drive");                       // ❌ 删除该 handler
    g_bus.SendReq<void, int>(50, "Drive");                  // ⛔ 不会触发，已经被删除
}

