#include <iostream>

using namespace std;

template <typename T>
class MyAllocator{
public:
    static T* allocate(size_t size){
        if(size <= 0 || size > maxSize())
            throw std::bad_alloc();
        void* res = malloc(size * sizeof(T));
        if(res == 0)
            throw std::bad_alloc();
        return static_cast<T*>(res);
    }

    static void deallocate(T* p){
        free((void*)p);
    }

    static size_t maxSize(){
        return static_cast<size_t>(size_t(-1) / sizeof(T));
    }

};

void testIntAllocator(size_t n){
    int* arr = MyAllocator<int>::allocate(n);
    for(int i = 0;i < n;i++){
        arr[i] = i;
    }
    for(int i = 0;i < n;i++){
        cout << arr[i] << " ";
    }
    cout << endl;
    delete[] arr;
}

class TestAllocator{
public:
    int a;
    int b;
    ~TestAllocator(){
        cout << "destroy function called " << endl;
    }
};

void testClassAllocator(size_t n){
    TestAllocator* arr = MyAllocator<TestAllocator>::allocate(n);
    for(int i = 0;i < n;i++){
        arr[i].a = i;
        arr[i].b = i * 10;
    }
    for(int i = 0;i < n;i++){
        cout << arr[i].a << " ";
    }
    cout << endl;
    for(int i = 0;i < n;i++){
        cout << arr[i].b << " ";
    }
    cout << endl;

}

int main() {
    testClassAllocator(10);

    return 0;
}
