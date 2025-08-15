#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>


template <typename Key, typename Value>
class HashMap {
    private:
        static const size_t DEFAULT_CAPACITY = 16;
        std::vector<std::list<std::pair<Key, Value>>> table;
        size_t hash (const Key& key) const {
            return std::hash<Key>()(key) % table.size();
        }
        
    public:
        HashMap() : table(DEFAULT_CAPACITY) {}

        void insert(const Key& key, const Value& value) {
            size_t index = hash(key);
            for (auto& pair : table[index]) {
                if (pair.first == key) {
                    pair.second = value; // Update existing key
                    return;
                }
            }
            table[index].emplace_back(key, value); // Insert new key-value pair
        }

        Value searchTable(const Key& key) const {
            size_t index = hash(key);
            for (const auto& pair : table[index]) {
                if (pair.first == key) {
                    return pair.second; // Return the value if key is found
                }
            }
            return Value(); // Return default value if key is not found
        }


        bool isValid(const Key& key, Value& value) const;
        void print() const;
        bool isEmpty() const;
        void remove(const Key& key);
    };


template <typename Key, typename Value>
bool HashMap<Key, Value>::isValid(const Key& key, Value& value) const {
    size_t index = hash(key);
    for (const auto& pair : table[index]) {
        if (pair.first == key) {
            value = pair.second;
            return true; // Key found
        }
    }
    return false; // Key not found
}
template <typename Key, typename Value>
void HashMap<Key, Value>::print() const {
    for (const auto& bucket : table) {
        for (const auto& pair : bucket) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }
}

template <typename Key, typename Value>
bool HashMap<Key, Value>::isEmpty() const {
    for (const auto& bucket : table) {
        if (!bucket.empty()) {
            return false; // At least one bucket is not empty
        }
    }
    return true; // All buckets are empty
}

template <typename Key, typename Value>
void HashMap<Key, Value>::remove(const Key& key) {
    size_t index = hash(key);
    auto& bucket = table[index];
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->first == key) {
            bucket.erase(it); // Remove the key-value pair
            return;
        }
    }

}
