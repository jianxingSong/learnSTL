//
// Created by 宋健星 on 2024/8/17.
//
#include <iostream>
#include "vector"
#include "list"
#include "functional"
#include "utility"

using namespace std;

template <typename Key, typename Value>
class MyHashMap{
private:
    vector<list<pair<Key, Value>>> table;
    size_t bucket_count;

    size_t hashFunction(const Key& key) const {
        return hash<Key>()(key) % bucket_count;
    }

public:
    MyHashMap(size_t buckets = 53): bucket_count(buckets) {
        table.resize(bucket_count);
    }

    void insert(const Key& key, const Value& value){
        size_t index = hashFunction(key);
        for(auto& pair : table[index]){
            if(pair.first == key){
                pair.second = value;
                return;
            }
        }

        table[index].emplace_back(key, value);
    }

    void remove(const Key& key){
        size_t index = hashFunction(key);
        auto& cell = table[index];
        for(auto it = cell.begin();it != cell.end();++it){
            if(it->first == key){
                cell.erase(it);
                return;
            }
        }
    }

    Value* find(const Key& key){
        size_t index = hashFunction(key);
        for(auto& pair : table[index]){
            if(pair.first == key){
                return &pair.second;
            }
        }
        return nullptr;
    }

    void print() const{
        for(size_t i = 0;i < bucket_count;i++){
            cout << "Bucket " << i << ": ";
            for(const auto& pair : table[i]){
                cout << "(" << pair.first << ", " << pair.second << ") ";
            }
            cout << endl;
        }
    }
};


int main() {
    MyHashMap<string, int> myMap;
    myMap.insert("Alice", 23);
    myMap.insert("Bob", 34);
    myMap.insert("Charlie", 25);
    myMap.insert("Dave", 30);

    myMap.print();

    int* age = myMap.find("Bob");
    if(age){
        cout << "Bob's age is " << *age << endl;
    }

    myMap.remove("Charlie");
    myMap.print();

    return 0;
}

