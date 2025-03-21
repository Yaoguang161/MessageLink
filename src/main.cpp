#include "../include/test/Message.h"

using namespace std;

int main()
{
    auto f = to_function([](int i){
        return i;
        });
    std::function<int(int)> f1 = [] (int i) {return i;};
    if(std::is_same<decltype(f), decltype(f1)>::value)
    {
        cout << "same" << endl;
    }

    return 0;
}