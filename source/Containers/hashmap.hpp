#pragma once

#include <memory>

// Hashmap using linear probing, inefficient because of double pointer == more time required for double indirection

template<typename Key, typename Value>
struct Hashnode final
{
    Key key{};
    Value value{};
};

template<typename Key, typename Value>
class Hashmap final
{
public:
    Hashmap() = default;

    explicit Hashmap(const size_t capacity)
    {
        m_capacity = capacity;
        arr = new Hashnode<Key, Value>*[capacity];

        for (size_t i = 0; i < m_capacity; ++i)
            arr[i] = nullptr;
    }

    int hashfunction(const Key& key)
    {
        return key % m_capacity;
    }

public:
    void insertnode(const Key& key, const Value& value)
    {
        Hashnode<Key, Value>* temp = new Hashnode<Key, Value>(key, value);

        size_t index = hashfunction(key);

        while (true)
        {
            if (arr[index] == nullptr)
            {
                arr[index] = temp;
                m_size++;
                break;
            }
            else
            {
                index = (index + 1) % m_capacity;
            }
        }

    }

    Value deletenode(const Key& key)
    {
        size_t index = hashfunction(key);

        while (true)
        {
            if (arr[index] && arr[index]->key == key)
            {
                const Value value = arr[index]->value;
                arr[index]->~Hashnode<Key, Value>();
                delete arr[index];
                m_size--;
                return value;
            }

            index++;
            index %= m_capacity;
        }

        return Value{};
    }

    Value get(const Key& key)
    {
        size_t index = hashfunction(key);
        size_t counter = 0;

        while (true)
        {
            if (counter++ > m_capacity) break;

            if (arr[index]->key == key)
                return arr[index]->value;

            index++;
            index %= m_capacity;
        }

        return Value{};
    }

    size_t size() const { return m_size; }
    bool isempty() const { return m_size == 0; }

    void display()
    {
        for (int i = 0; i < m_capacity; i++) 
        {
            if (arr[i] != nullptr)
                std::cout << "key = " << arr[i]->key
                     << "  value = "
                     << arr[i]->value << '\n';
        }
    }

private:
    Hashnode<Key, Value>** arr{};
    size_t m_size{};
    size_t m_capacity{};
};