#include <memory>
#include <typeindex>
#include <iostream>

struct Any
{
    // Any(void) : m_tpIndex(std::type_index(typeid(void))){}




private:
    struct Base;
    using BasePtr = std::unique_ptr<Base>;

    struct Base
    {
        virtual ~Base(){}
        
    }
};



