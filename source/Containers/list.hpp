#pragma once

#include <iosfwd>

namespace neo {
static auto println = [](const char* str) { 
    std::cout << str << '\n';
};
}

template<typename T>
struct Node final
{
    T value{};
    Node<T>* next{ nullptr };
};


template<typename T>
class List final
{
public:
    List() = default;

    List(const T& val)
        : List(val, nullptr)
    { }

    List(const T& val, Node<T>* next)
        : head{ new Node<T>(val, next) }
        , m_size{ 1 }
    { }

public:
    List& insert(const T& val)
    {
        Node<T>* newNode = new Node<T>(val);

        if (head == nullptr)
        {
            head = newNode;
            m_size = 1;
            return *this;
        }
        
        Node<T>* temp = head;

        while (temp->next)
            temp = temp->next;

        temp->next = newNode;
        m_size++;
        return *this;
    }

    List& erase(const T& val, bool bEraseAll = 0)
    {
        if (!head) 
        {
            neo::println("List is empty, nothing to erase!");
            return *this;
        }

        if (head && head->value == val)
        {
            Node<T>* temp{ head };
            head = head->next;
            delete temp;

            neo::println("Found element at head and deleted it");
            return *this;
        }

        Node<T>* current = head;
        while (current && current->next)
        {
            if (current->next->value == val)
            {
                Node<T>* temp{ current->next };
                current->next = current->next->next;
                delete temp;

                neo::println("Found and deleted");
                if (!bEraseAll) return *this;
            }
            else 
            {
                current = current->next;
            }
        }

        return *this;
    }

    void print()
    {
        if (!head) 
        {
            neo::println("The list is empty, nothing to print here!");
            return;
        }

        Node<T>* temp = head;

        while (temp)
        {
            std::cout << temp->value << " ";
            std::cout << '\n';
            temp = temp->next;
            if (!temp) neo::println("Null - Reached end");
        }
    }

    void search(const T& val)
    {
        if (!head) neo::println("The list is empty, nothing to search here!");

        Node<T>* temp{ head };
        while (temp)
        {
            if (temp->value == val)
            {
                neo::println("Element was found!");
                return;
            }
        }
    }

private:
    Node<T>* head{ nullptr };
    size_t m_size{ 0 };
};