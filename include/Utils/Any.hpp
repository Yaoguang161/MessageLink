#include <memory>
#include <type_traits>
#include <typeindex>
#include <iostream>
#include <typeinfo>
#include <utility>

//不能 直接存储 std::unique_ptr<T>，因为 std::unique_ptr 不能被拷贝，但可以通过 std::move() 存储并转移所有权。
struct Any
{
    Any(void)            : m_tpIndex(std::type_index(typeid(void)))          {}
    Any(const Any& that) : m_ptr(that.Clone()), m_tpIndex(that.m_tpIndex)         {}
    Any(Any && that)     : m_ptr(std::move(that.m_ptr)), m_tpIndex(that.m_tpIndex){}

    //创建智能指针时， 对于一般的类型，通过std::decay来移除引用和cv符，从而获取原始类型
    template<typename U, class = 
    typename std::enable_if<!std::is_same<typename std::decay<U>::type,Any>::value,U>::type> Any(U && value)
        : m_ptr(new Derived<typename std::decay<U>::type>(std::forward<U>(value)))
        , m_tpIndex(std::type_index(typeid(typename std::decay<U>::type)))
        {}

    bool IsNull() const {return !bool(m_ptr);}

    template<class U> bool Is() const
    {
        return m_tpIndex == std::type_index(typeid(U));
    }

    //将Any转换成实际的类型
    template<class U>
    U& AnyCast()
    {
        if(!Is<U>())
        {
            std::cout << "can not cast" << typeid(U).name() << " to " << m_tpIndex.name() << std::endl;
            throw std::bad_cast();
        }
        auto derived = dynamic_cast<Derived<U>*>(m_ptr.get());
        return derived->m_value;
    }

    Any& operator=(const Any& a)
    {
        if(m_ptr == a.m_ptr)
        {
            return *this;
        }
        m_ptr     = a.Clone();
        m_tpIndex = a.m_tpIndex;
        return *this;
    }

private:
    struct Base;
    using BasePtr = std::unique_ptr<Base>;

    struct Base
    {
        virtual ~Base(){}
        virtual BasePtr Clone() const = 0;
    };

    template<typename T>
    struct Derived : Base
    {
        template<typename U>
        Derived(U && value) : m_value(std::forward<U>(value)){}    // T&& 既可以绑定左值，也可以绑定右值。 通用引用（Universal Reference），它可以匹配左值和右值。

        BasePtr Clone() const
        {
            return BasePtr(new Derived<T>(m_value));  // 返回子类对象指针
        }
        T m_value;
    };

    BasePtr Clone() const
    {
        if (m_ptr != nullptr)
        {
            return m_ptr->Clone();
        }
        return nullptr;
    }

    BasePtr m_ptr;
    std::type_index m_tpIndex;
};



