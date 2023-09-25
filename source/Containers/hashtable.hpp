#pragma once

#include <memory>

template<typename Key, typename Value>
struct HashNode final 
{
    Key key{};
    Value value{};
};

template<typename Key, typename Value>
class HashTable final
{
public:
    HashTable() = default;

    HashTable(size_t capacity)
        : table(new HashNode<Key, Value>[capacity])
        , m_size(0)
        , m_capacity(capacity)
    {}

    ~HashTable()
    {
        if (table)
            delete[] table;
    }

public:
    void insert(const Key& key, const Value& value)
    {
        if (!table)
        {
            std::cout << "The HashTable is not constructed" << '\n';
            return;
        }

        size_t index = hashcode(key);

        while (true)
        {
            if (table[index].key != key)
            {
                new (table + index) HashNode<Key, Value>(key, value);
                m_size++;
                return;
            }
            else
            {
                index = (index + 1) % m_capacity;
            }
        }
    }
    
    Value* get(const Key& key)
    {
        if (!table)
        {
            std::cout << "The HashTable is not constructed, returning " << '\n';
            return nullptr;
        }

        size_t index = hashcode(key);
        size_t counter = 0;

        while (true)
        {
            if (counter++ > m_capacity) break;

            if (table[index].key == key)
                return &table[index].value;
            else
                index = (index + 1) % m_capacity;
        }

        return nullptr;
    }

private:
    int hashcode(const Key& key) const
    {
        return key & m_capacity;
    }

private:
    HashNode<Key, Value>* table{nullptr};
    size_t m_size{};
    size_t m_capacity{};
};