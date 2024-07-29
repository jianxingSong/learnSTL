//
// Created by 宋健星 on 2024/7/8.
//
#include "iostream"

using namespace std;

template <typename T>
struct Node{
    T value;
    Node* next;
    Node(): value(0), next(nullptr){}
    Node(int v): value(v), next(nullptr){}
    Node(int v, Node<T>* p): value(v), next(p){}
};


//就是一个封装好的指针
template <typename T>
class Iterator{
public:
    using link_type = Node<T>;

    Iterator(link_type* p = nullptr):ptr(p){}

    Iterator& operator++(){
        ptr = ptr->next;
        return *this;
    }

    Iterator operator++(int){
        Iterator<T> temp = *this;
        ptr = ptr->next;
        return temp;
    }

    bool operator==(const Iterator& it){
        return ptr == it.ptr;
    }

    bool operator!=(const Iterator& it){
        return ptr != it.ptr;
    }

    link_type* operator->(){
        return ptr;
    }

    link_type& operator*(){
        return ptr->value;
    }

private:
    Node<T>* ptr;
};

template <typename T>
class MyList{
public:
    MyList(): dummyHead(Node<T>()), m_size(0){}

    void push_front(const T& t){
        dummyHead.next = new Node<T>(t, dummyHead.next);
        m_size++;
    }

    void pop_front(){
        Node<T>* front = dummyHead.next;
        dummyHead.next = dummyHead.next->next;
        delete front;
        m_size--;
    }

    T& front(){
        return dummyHead.next->value;
    }

    Iterator<T> begin(){
        return Iterator<T>(dummyHead.next);
    }

    Iterator<T> end(){
        return Iterator<T>(nullptr);
    }

    ~MyList(){
        Node<T>* node = dummyHead.next;
        while(node != nullptr){
            Node<T>* temp = node;
            node = node->next;
            delete temp;
        }
        m_size = 0;
    }


private:
    Node<T> dummyHead;
    size_t m_size;
};




int main(){
    MyList<int> myList;
    myList.push_front(1);
    myList.push_front(2);
    myList.push_front(3);
    myList.push_front(4);
    myList.push_front(5);
    myList.pop_front();
    for(auto it = myList.begin();it != myList.end();it++){
        cout << it->value << endl;
    }


    return 0;
}
