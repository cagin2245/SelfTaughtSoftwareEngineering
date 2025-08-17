#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

// HashMap implementasyonu (iterator + const_iterator destekli)
template <typename Key, typename Value>
class HashMap
{
private:
    static const size_t DEFAULT_CAPACITY = 16;
    double loadFactor = 0.75;
    size_t currentSize = 0;
    std::vector<std::list<std::pair<Key, Value>>> table;

    size_t hash(const Key &key) const
    {
        return std::hash<Key>()(key) % table.size();
    }

    using Bucket = std::list<std::pair<Key, Value>>;
    using Table = std::vector<Bucket>;

public:
    // --- Iterator ---
    class iterator
    {
        Table *table;
        size_t bucketIndex;
        typename Bucket::iterator bucketIt;

        void skipEmpty()
        {
            while (bucketIndex < table->size() && bucketIt == (*table)[bucketIndex].end())
            {
                ++bucketIndex;
                if (bucketIndex < table->size())
                {
                    bucketIt = (*table)[bucketIndex].begin();
                }
                else
                {
                    // end() iteratörü -> bucketIt geçersiz olmalı
                    bucketIt = typename Bucket::iterator();
                }
            }
        }

    public:
        iterator(Table *t, size_t idx)
            : table(t), bucketIndex(idx), bucketIt(idx >= t->size() ? typename Bucket::iterator() : (*t)[idx].begin())
        {
            skipEmpty();
        }

        std::pair<Key, Value> &operator*()
        {
            if (bucketIndex >= table->size() || bucketIt == (*table)[bucketIndex].end())
                throw std::out_of_range("Iterator out of range");
            return *bucketIt;
        }
        std::pair<Key, Value> *operator->() { return &(*bucketIt); }

        iterator &operator++()
        {
            ++bucketIt;
            skipEmpty();
            return *this;
        }
        bool operator==(const iterator &other) const
        {
            return table == other.table && bucketIndex == other.bucketIndex && bucketIt == other.bucketIt;
        }
        bool operator!=(const iterator &other) const { return !(*this == other); }
    };

    // --- Const Iterator ---
    class const_iterator
    {
        const Table *table;
        size_t bucketIndex;
        typename Bucket::const_iterator bucketIt;

        void skipEmpty()
        {
            while (bucketIndex < table->size() && bucketIt == (*table)[bucketIndex].end())
            {
                ++bucketIndex;
                if (bucketIndex < table->size())
                {
                    bucketIt = (*table)[bucketIndex].begin();
                }
                else
                {
                    // end() iteratörü -> bucketIt geçersiz olmalı
                    bucketIt = typename Bucket::iterator();
                }
            }
        }

    public:
        const_iterator(const Table *t, size_t idx)
            : table(t), bucketIndex(idx)
        {
            if (idx >= t->size())
            {
                bucketIndex = t->size();
                bucketIt = typename Bucket::const_iterator();
            }
            else
            {
                bucketIt = (*t)[idx].begin();
                skipEmpty();
            }
        }

        const std::pair<Key, Value> &operator*() const
        {
            if (bucketIndex >= table->size() || bucketIt == (*table)[bucketIndex].end())
                throw std::out_of_range("Iterator out of range");
            return *bucketIt;
        }
        const std::pair<Key, Value> *operator->() const { return &(*bucketIt); }

        const_iterator &operator++()
        {
            ++bucketIt;
            skipEmpty();
            return *this;
        }

        bool operator==(const const_iterator &other) const
        {
            return table == other.table && bucketIndex == other.bucketIndex && bucketIt == other.bucketIt;
        }
        bool operator!=(const const_iterator &other) const { return !(*this == other); }
    };

    // API: begin/end
    iterator begin() { return iterator(&table, 0); }
    iterator end() { return iterator(&table, table.size()); }

    const_iterator begin() const { return const_iterator(&table, 0); }
    const_iterator end() const { return const_iterator(&table, table.size()); }

    // ---- Normal Fonksiyonlar ----
    HashMap() : table(DEFAULT_CAPACITY) {}
    HashMap(const HashMap &other) : table(other.table), currentSize(other.currentSize), loadFactor(other.loadFactor) {}
    HashMap(HashMap &&other) noexcept : table(std::move(other.table)), currentSize(other.currentSize), loadFactor(other.loadFactor)
    {
        other.currentSize = 0;
    }

    void insert(const Key &key, const Value &value)
    {
        size_t index = hash(key);
        for (auto &pair : table[index])
        {
            if (pair.first == key)
            {
                pair.second = value;
                return;
            }
        }
        table[index].emplace_back(key, value);
        currentSize++;
        if ((double)currentSize / table.size() > loadFactor)
            rehash();
    }

    Value searchTable(const Key &key) const
    {
        size_t index = hash(key);
        for (const auto &pair : table[index])
        {
            if (pair.first == key)
                return pair.second;
        }
        return Value();
    }

    bool isValid(const Key &key, Value &value) const
    {
        size_t index = hash(key);
        for (const auto &pair : table[index])
        {
            if (pair.first == key)
            {
                value = pair.second;
                return true;
            }
        }
        return false;
    }

    void remove(const Key &key)
    {
        size_t index = hash(key);
        auto &bucket = table[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it)
        {
            if (it->first == key)
            {
                bucket.erase(it);
                currentSize--;
                return;
            }
        }
    }

    void print() const
    {
        for (const auto &bucket : table)
        {
            for (const auto &pair : bucket)
                std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }

    void printSorted() const
    {
        std::vector<std::pair<Key, Value>> allPairs;
        for (const auto &bucket : table)
            for (const auto &pair : bucket)
                allPairs.push_back(pair);

        std::sort(allPairs.begin(), allPairs.end(), [](const auto &a, const auto &b)
                  {
            if constexpr (std::is_same<Key, std::string>::value)
                return std::stoi(a.first) < std::stoi(b.first);
            else
                return a.first < b.first; });

        for (const auto &pair : allPairs)
            std::cout << pair.first << ": " << pair.second << std::endl;
    }

    bool isEmpty() const
    {
        return currentSize == 0;
    }

    size_t size() const { return currentSize; }

    void rehash()
    {
        size_t newCapacity = table.size() * 2;
        std::vector<std::list<std::pair<Key, Value>>> newTable(newCapacity);
        for (const auto &bucket : table)
        {
            for (const auto &pair : bucket)
            {
                size_t newIndex = std::hash<Key>()(pair.first) % newCapacity;
                newTable[newIndex].emplace_back(pair.first, pair.second);
            }
        }
        table = std::move(newTable);
        std::cout << "Rehashed to new capacity: " << newCapacity << std::endl;
    }
};
