#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm> // En üste ekleyin


template <typename Key, typename Value>
class HashMap {
    private:
        static const size_t DEFAULT_CAPACITY = 16;
        double loadFactor = 0.75;//Load factor for resizing
        size_t currentSize = 0; // Current number of elements in the map        
        std::vector<std::list<std::pair<Key, Value>>> table;
        size_t hash (const Key& key) const {
            return std::hash<Key>()(key) % table.size();
        }
        // Removed unused tables, size, numTables, and DEFAULT_LOAD_FACTOR.
        
    public:

        class HashNode {
            public:
                Key key;
                Value value;
                HashNode * next;

                HashNode(const Key& k, const Value& v) : key(k), value(v), next(nullptr) {}
        };
        
        HashMap() : table(DEFAULT_CAPACITY) {} // tabloyu başlatır
        HashMap(const HashMap& other) : table(other.table), currentSize(other.currentSize), loadFactor(other.loadFactor) 
        {
            // Copy constructor
            // No need to copy the individual elements since we are copying the entire table
        }
        HashMap(HashMap&& other) noexcept : table(std::move(other.table)), currentSize(other.currentSize), loadFactor(other.loadFactor) {
            // Move constructor
            other.currentSize = 0; // Clear the moved-from object
        }
       
        
        std::vector<std::list<std::pair<Key, Value>>> getTable() const {
            return table; // Return the current table
        }
        void insert(const Key& key, const Value& value) {
            size_t index = hash(key);
        
            for (auto& pair : table[index]) {
                if (pair.first == key) {
                    pair.second = value; // Update existing key
                    return;
                }
            }
            table[index].emplace_back(key, value); // Insert new key-value pair
        
            
            
            currentSize++;
            double loadFactor = static_cast<double>(currentSize) / table.size();
        
            if (loadFactor > this->loadFactor) {               
                rehash(); // Resize if load factor exceeds threshold                
            }
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
        void printSorted() const;
        bool isEmpty() const;
        void remove(const Key& key);
        void rehash();
        size_t size() const;

    };




template <typename Key, typename Value>
size_t HashMap<Key, Value>::size() const {
    return currentSize; // Return the current size of the map
}

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
void HashMap<Key, Value>::printSorted() const {
    std::vector<std::pair<Key, Value>> allPairs;
    for (const auto& bucket : table) {
        for (const auto& pair : bucket) {
            allPairs.push_back(pair);
        }
    }
    std::sort(allPairs.begin(), allPairs.end(),
        [](const auto& a, const auto& b) {
            
            if constexpr (std::is_same<Key, std::string>::value) {
                return std::stoi(a.first) < std::stoi(b.first);
            } else {
                return a.first < b.first;
            }
        });

    for (const auto& pair : allPairs) {
        std::cout << pair.first << ": " << pair.second << std::endl;
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

template <typename Key, typename Value>
void HashMap<Key, Value>::rehash() {
    size_t newCapacity = table.size() * 2;
    std::vector<std::list<std::pair<Key, Value>>> newTable(newCapacity);
    size_t newSize = 0;
    for (const auto& bucket : table) {
        for (const auto& pair : bucket) {
            size_t newIndex = std::hash<Key>()(pair.first) % newCapacity;
            newTable[newIndex].emplace_back(pair.first, pair.second);
            ++newSize;
        }
    }
    table = std::move(newTable);
    std::cout << "Rehashed to new capacity: " << newCapacity << std::endl;
    currentSize = newSize; // Eleman sayısını koru
}

