// #include "../include/test/MessageBus.hpp"
#include "../src/democomplexity.hpp"

using namespace std;

// void TestMesBus()
// {
//     MessageBus bus;
//     //注册消息
//     bus.Attach([](int a){ cout << "no reference " << a << endl;  });
//     bus.Attach([](int& a){ cout << "lvalue reference " << a << endl;  });
//     bus.Attach([](int&& a){ cout << "rvalue reference " << a << endl;  });
//     bus.Attach([](const int& a){ cout << "const lvalue reference " << a << endl;  });
//     bus.Attach([](int a){ cout << "no reference has return value and key " << a << endl; return a;}, "a");

//     int i = 2;
//     //发送消息
//     bus.SendReq<void, int>(2);
//     bus.SendReq<int, int>(2, "a");
//     bus.SendReq<void, int &>(i);
//     bus.SendReq<void, const int &>(2);
//     bus.SendReq<void, int &&>(2);

//     //移除消息
//     bus.Remove<void,int>();
//     bus.Remove<int, int>("a");
//     bus.Remove<void, int&>();
//     bus.Remove<void, const int&>();
//     bus.Remove<void, int &&>();

//     //发送消息
//     bus.SendReq<void, int>(2);
//     bus.SendReq<int, int>(2, "a");
//     bus.SendReq<void, int&>(i);
//     bus.SendReq<void, const int&>(2);
//     bus.SendReq<void, int&&>(2);
// }

int main()
{
    TestBus();
    return 0;
}