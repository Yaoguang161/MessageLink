#include "../include/test/MessageBus.hpp"

MessageBus g_bus;

const std::string Topic = "Drive";
const std::string CallBackTopic = "DriveOK";

struct Subject
{
    Subject()
    {
        g_bus.Attach([this]{DirveOK();}, CallBackTopic);
    }

    void SendReq(const std::string& topic)
    {
        g_bus.SendReq<void, int>(50, topic);
    }

    void DirveOK()
    {
        std::cout << "drive ok" << std::endl;
    }
};

struct Car
{
    Car()
    {
        g_bus.Attach([this](int speed){Drive(speed);},Topic);  //注册到 "Drive" + typeid(std::function<void(int)>).name()
    }

    void Drive(int speed)
    {
        std::cout << "Car drive " << speed << std::endl;
        g_bus.SendReq<void>(CallBackTopic);
    }
};

struct Bus
{
    Bus()
    {
        g_bus.Attach([this](int speed){Drive(speed);});  //注册到空  "" + typeid(std::function<void(int)>).name()
    }

    void Drive(int speed)
    {
        std::cout << "Bus drive " << speed << std::endl;
        g_bus.SendReq<void>(CallBackTopic);
    }
};

struct Truck
{
    Truck()
    {
        g_bus.Attach([this](int speed){Drive(speed);});  //注册到空 "" + typeid(std::function<void(int)>).name()
    }

    void Drive(int speed)
    {
        std::cout << "Truck drive " << speed << std::endl;
        g_bus.SendReq<void>(CallBackTopic);
    }
};

struct Plane
{
    Plane()
    {
        g_bus.Attach([this](int speed, double height) {
            Fly(speed, height);
        }, Topic);
    }

    void Fly(int speed, double height)
    {
        std::cout << "Plane fly at speed " << speed << " and height " << height << std::endl;
        g_bus.SendReq<void>(CallBackTopic);
    }
};

void TestBus()
{
    Subject subject;
    Car car;
    Bus bus;
    Truck truck;
    Plane plane;

    g_bus.SendReq<void, int, double>(300, 10000.0, Topic);
    subject.SendReq(Topic);  //取  Car
    subject.SendReq("");     //取  Bus Truck
}