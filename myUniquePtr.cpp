//
// Created by 宋健星 on 2024/7/8.
//
#include "iostream"

using namespace std;

template <typename T, typename deleter = default_delete<T>>
class MyUniquePtr{
public:
    MyUniquePtr(T* ptr): m_ptr(ptr){}

    ~MyUniquePtr(){
        if(m_ptr != nullptr){
            m_deleter(m_ptr);
            cout << "destroy" << endl;
        }
    }

    //unique_ptr无法拷贝构造和拷贝赋值，因为一块内存只能被一个unique_ptr指向
    MyUniquePtr(MyUniquePtr<T, deleter>& uniqPtr) = delete;
    MyUniquePtr<T, deleter>& operator=(MyUniquePtr<T, deleter>& uniqPtr) = delete;

    //只能有移动构造函数和移动赋值运算符
    MyUniquePtr(MyUniquePtr<T, deleter>&& uniqPtr){
        m_ptr = uniqPtr.m_ptr;
        uniqPtr.m_ptr = nullptr;
    }
    MyUniquePtr<T, deleter>& operator=(MyUniquePtr<T, deleter>&& uniqPtr){
        if(&uniqPtr != this){
            m_ptr = uniqPtr.m_ptr;
            uniqPtr.m_ptr = nullptr;
        }

        return *this;
    }

    void reset(T* ptr){
        m_deleter(m_ptr);
        m_ptr = ptr;
    }

    T& operator*(){
        return *m_ptr;
    }

    T* operator->(){
        return m_ptr;
    }

private:
    deleter m_deleter;
    T* m_ptr;
};

class deleter{
public:
    void operator()(int* p){
        delete p;
        cout << "customize deleter be called" << endl;
    }
};

int main(){
//    MyUniquePtr<int> up1(new int (10));
//    cout << *up1 << endl;
//    *up1 = 100;
//    cout << *up1 << endl;
//
//    MyUniquePtr<int> up2(move(up1));
//    cout << *up2 << endl;

    MyUniquePtr<int, deleter> up3(new int(10));
    MyUniquePtr<int, deleter> up4 = move(up3);
    cout << *up4 << endl;

    return 0;
}
