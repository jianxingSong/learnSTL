#include <iostream>
#include "assert.h"

using namespace std;


//! 维护的是start finish 和end三个指针
//! 最难的应该就是reserve函数了
//! 同时还要注意insert 和 erase的迭代器失效的问题
template <typename T>
class MyVector{
public:
    typedef T* iterator;
    typedef const T* const_iterator;

    //构造函数
    MyVector():_start(nullptr), _finish(nullptr), _end_of_storage(nullptr){}

    MyVector(size_t n, const T& t):_start(nullptr), _finish(nullptr), _end_of_storage(nullptr){
        reserve(n);
        for(int i = 0;i < n;i++){
             this->push_back(t);
        }
    }

    MyVector(const MyVector<T>& vec){
        reserve(vec.size());
        for(int i = 0;i < vec.size();i++){
            this->push_back(vec[i]);
        };
    }

    MyVector(const_iterator begin, const_iterator end){
        size_t sz = end - begin;
        reserve(sz);
        while(begin != end){
            this->push_back(*begin++);
        }
    }

    MyVector<T>& operator=(const MyVector<T>& vec){
        //拷贝赋值
        if(&vec == this)
            return *this;
        reserve(vec.size());
        for(int i = 0;i < vec.size();i++){
            _start[i] = vec[i];
        }
        _finish = _start + vec.size();
        return *this;
    }

    ~MyVector(){
        delete[] _start;
        _start = _finish = _end_of_storage = nullptr;
    }

    //返回自己的一些变量
    iterator begin(){
        return _start;
    }

    iterator end(){
        return _finish;
    }

    const_iterator cbegin(){
        return _start;
    }

    const_iterator cend(){
        return _finish;
    }

    //容器的操作
    void push_back(const T& t){
        if(_finish == _end_of_storage){
            reserve(capacity() == 0 ? 4 : capacity() * 2);
        }
        *_finish++ = t;
    }

    void pop_back(){
        assert(!empty());
        _finish--;
    }

    //注意这个插入函数要考虑迭代器失效的问题：
    //1.插入位置后的迭代器会全部失效，所以insert函数要返回一个迭代器，是插入位置后的迭代器
    //2.如果插入前容器的size已经等于capacity了，则需要重新开辟一个容器，则容器所有的迭代器都失效了，需要在函数内部重新指定
    iterator insert(iterator pos, T t){
        assert(pos >= _start && pos <= _finish);
        //先判断目前容器的size是否已经达到了capacity
        if(_finish == _end_of_storage){
            size_t len = pos - _start;
            reserve(capacity() == 0 ? 4 : capacity() * 2);
            pos = _start + len;
        }

        //否则需要将容器pos以后的元素全部向后移动
        iterator end = _finish;
        while(end != pos){
            *end = *(end - 1);
            end--;
        }
        *end = t;
        _finish++;
        return ++pos;
    }

    //erase同样也要考虑迭代器失效的问题
    iterator erase(iterator pos){
        assert(pos >= _start && pos < _finish);
        iterator temp = pos + 1;
        while(temp != _finish){
            *(temp - 1) = *temp;
            temp++;
        }
        _finish--;
        return pos;
    }

    //返回容器特征
    size_t size(){
        return  _finish - _start;
    }

    size_t capacity(){
        return  _end_of_storage - _start;
    }

    bool empty(){
        return _start == _finish;
    }

    //开辟内存
    void reserve(size_t n){
        if(n > capacity()){
            T* temp = new T(n);
            int sz = size();
            if(_start != nullptr){
                for(int i = 0;i < sz;i++){
                    temp[i] = _start[i];
                }
            }
            delete[] _start;
            _start = temp;
            _finish = _start + sz;
            _end_of_storage = _start + n;
        }
    }

    //操作符重载
    T& operator[](int i){
        assert(i < size());
        return _start[i];
    }


private:
    T* _start;
    T* _finish;
    T* _end_of_storage;

};

int main() {
    MyVector<int> vec(5, 1);
    for(int i = 0;i < vec.size();i++){
        vec[i] = i;
    }
    auto p = vec.insert(vec.begin() + 2, 20);
    cout << *(p++) << endl;
//    vec.push_back(6);
//    vec.pop_back();
//    vec.insert(vec.begin() + 5, 6);
//    cout << vec[5] << endl;
//    vec.erase(vec.begin() + 5);
//    cout << vec.size() << ", " << vec.capacity() << endl;
    return 0;
}
