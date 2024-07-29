//
// Created by 宋健星 on 2024/7/7.
//
#include "iostream"
#include "atomic"

using namespace std;

//! shared_ptr需要注意的是要单独定义一个控制块，用于存储引用计数
//! 并且定义增加 减少和获取这种接口
class shared_count{
public:
    shared_count(): count(1){

    }

    void addCount(){
        count++;
    }

    void reduceCount(){
        count--;
    }

    long long getCount(){
        return count;
    }

private:
    long long count;
};


//! shared_ptr维护两个成员两个成员变量：指向计数器的指针以及指向真正对象的指针
//! 然后定义构造函数以及拷贝赋值运算符就可以了
//! 还有一下向useCount的接口以及一些解引用的操作符重载等等
template <typename T>
class MySharedPtr{
public:
    MySharedPtr():ptr(nullptr), sh_cnt_ptr(nullptr){}

    MySharedPtr(T* p):ptr(p){
        if(p != nullptr){
            sh_cnt_ptr = new shared_count;
        }
    }

    MySharedPtr(MySharedPtr<T>& shPtr){
        if(shPtr.ptr != nullptr){
            ptr = shPtr.ptr;
            sh_cnt_ptr = shPtr.sh_cnt_ptr;
            sh_cnt_ptr->addCount();
        }
    }

    MySharedPtr(MySharedPtr<T>&& shPtr){
        if(shPtr.ptr != nullptr){
            ptr = shPtr.ptr;
            sh_cnt_ptr = shPtr.sh_cnt_ptr;
            shPtr.ptr = nullptr;
            shPtr.sh_cnt_ptr = nullptr;
        }
    }

    MySharedPtr<T>& operator=(MySharedPtr<T>& shPtr){
        if(&shPtr == this){
            return *this;
        }

        if(ptr != nullptr && sh_cnt_ptr->getCount() == 1){
            delete ptr;
            delete sh_cnt_ptr;
        }
        if(shPtr.ptr != nullptr){
            ptr = shPtr;
            sh_cnt_ptr = shPtr.sh_cnt_ptr;
            sh_cnt_ptr->addCount();
        }
        return *this;
    }

    MySharedPtr<T>& operator=(MySharedPtr<T>&& shPtr){
        if(&shPtr == this){
            return *this;
        }

        if(ptr != nullptr && sh_cnt_ptr->getCount() == 1){
            delete ptr;
            delete sh_cnt_ptr;
        }
        if(shPtr.ptr != nullptr){
            ptr = shPtr;
            sh_cnt_ptr = shPtr.sh_cnt_ptr;
            shPtr.ptr = nullptr;
            sh_cnt_ptr = nullptr;
        }
        return *this;
    }

    T* operator->(){
        return ptr;
    }

    T& operator*(){
        return *ptr;
    }

    T* get(){
        return ptr;
    }

    bool unique(){
        return ptr != nullptr && sh_cnt_ptr->getCount() == 1;
    }

    int useCount(){
        if(ptr != nullptr)
            return  sh_cnt_ptr->getCount();
        return 0;
    }


    virtual ~MySharedPtr(){
        if(sh_cnt_ptr != nullptr && sh_cnt_ptr->getCount() == 0){
            delete ptr;
            delete sh_cnt_ptr;
        }
    }


private:
    T* ptr;
    shared_count* sh_cnt_ptr;
};

class Test{
public:
    void print(){
        cout << 11111 << endl;
    }
};

int main(){
//    MySharedPtr<int> shPtr1 = new int(10);
//    MySharedPtr<int> shPtr2 = shPtr1;
//    MySharedPtr<int> shPtr3 = move(shPtr2);
//    cout << shPtr1.useCount() << ", " << shPtr2.useCount() << endl;
    MySharedPtr<Test> shP1 = new Test();
    shP1->print();

}

