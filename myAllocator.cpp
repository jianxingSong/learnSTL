#include <iostream>

using namespace std;


//! allocator类是没有成员对象的 所有的操作都是封装的new 和 free
//! 需要实现以下成员函数
//! allocate: 分配的固定大小个T类型的内存空间
//! deallocate: 释放分配的内存
//! construct: 对申请的内存进行构造
//! destroy: 对申请的对象进行析构
template <typename T>
class MyAllocator{
public:
    T* allocate(size_t size){
        if(size <= 0 || size > maxSize())
            throw std::bad_alloc();
        void* res = malloc(size * sizeof(T));
        if(res == 0)
            throw std::bad_alloc();
        return static_cast<T*>(res); //malloc出来之后要记得强转
    }

    void deallocate(T* p){
        free((void*)p);
    }
    /* 为什么free知道要释放多大的内存？
     * free 函数能够知道要释放多少内存的原因是内存分配函数（如 malloc、calloc 和 realloc）在分配内存时，
     * 通常会在分配的内存块之前存储一些额外的信息，这些信息记录了内存块的大小。
     */

    static size_t maxSize(){
        return static_cast<size_t>(size_t(-1) / sizeof(T));
    }

    template<typename U, typename...Args>
    void construct(U* p,Args&&...args){
        new(p) U(forward<Args>(args)...);
    }

    void destroy(T* p){
        p->~T();
    }

};

//void testIntAllocator(size_t n){
//    int* arr = MyAllocator<int>::allocate(n);
//    for(int i = 0;i < n;i++){
//        arr[i] = i;
//    }
//    for(int i = 0;i < n;i++){
//        cout << arr[i] << " ";
//    }
//    cout << endl;
//    delete[] arr;
//}

class TestAllocator{
public:
    TestAllocator(int i, int j):a(i), b(j){
        cout << "calling TestAllocator's constructor" << endl;
    }
    int a;
    int b;
    ~TestAllocator(){
        cout << "destroy function called " << endl;
    }
};

void testClassAllocator(size_t n){
    MyAllocator<TestAllocator> myAllocator;
    TestAllocator* arr = myAllocator.allocate(n);
//    for(int i = 0;i < n;i++){
//        arr[i].a = i;
//        arr[i].b = i * 10;
//    }
    for(int i = 0;i < n;i++)
        myAllocator.construct(&arr[i], i, i * 10);
    for(int i = 0;i < n;i++){
        cout << arr[i].a << " ";
    }
    cout << endl;
    for(int i = 0;i < n;i++){
        cout << arr[i].b << " ";
    }
    cout << endl;
    for(int i = 0;i < n;i++)
        myAllocator.destroy(&arr[i]);
    myAllocator.deallocate(arr);
}

int main() {
    testClassAllocator(10);

    return 0;
}
