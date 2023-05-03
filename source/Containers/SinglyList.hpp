#pragma once

#include <stack>

namespace neo
{
    auto println = [](const char* str) { std::cout << str << '\n'; };
}

template<typename T>
struct Node final
{
    Node() = default;

    Node(const T& value)
        : Node(value, nullptr)
    { }

    Node(const T& value, Node<T>* next)
        : value{ value }
        , next{ next }
    { }

    T value{};
    Node<T>* next{ nullptr };
};

template<typename T>
class SinglyList final
{
public:
    SinglyList() = default;

    SinglyList(const T& value)
        : head{ new Node<T>(value) }
    { }

    SinglyList(const T& value, Node<T>* next)
        : head{ new Node<T>(value, next) }
    { }

    SinglyList(const SinglyList& other) = default;
    SinglyList& operator=(const SinglyList& other) = default;
    SinglyList(SinglyList&& other) = default;
    SinglyList& operator=(SinglyList&& other) = default;

    ~SinglyList() = default;

public:
    SinglyList& PushFront(const T& value)
    {
        Node<T>* newNode;

        if (!head)
        {
            head = new Node<T>(value);
            return *this;
        }

        newNode = new Node<T>(value, head);
        head = newNode;
        return *this;
    }

    SinglyList& PushBack(const T& value)
    {
        Node<T> *newNode, *current;
        
        if (!head)
        {
            newNode = new Node<T>(value);
            head = newNode;

            m_size++;

            return *this;
        }

        newNode = new Node<T>(value);
        current = head;

        while (current->next)
            current = current->next;

        current->next = newNode;
        m_size++;

        return *this;
    }

    SinglyList& PushAfter(Node<T>* previous, const T& value)
    {
        Node<T>* newNode = new Node<T>(value, previous->next);
        previous->next = newNode;

        m_size++;

        return *this;
    }

    SinglyList& Erase(const T& value, bool bEarseAll = false)
    {
        if (!head)
        {
            neo::println("SinglyList is empty, nothing to erase!");
            return *this;
        }

        if (head->value == value)
        {
            Node<T>* temp{ head->next };
            delete head;
            head = temp;

            m_size--;

            return *this;
        }
        
        Node<T>* current{ head };
        while (current && current->next)
        {
            if (current->next->value == value)
            {
                Node<T>* temp{ current->next };
                current->next = current->next->next;
                delete temp;

                m_size--;
                if (!bEarseAll) return *this;
            }
            else 
            {
                current = current->next;
            }
        }

        return *this;
    }

    SinglyList& Reverse()
    {
        Node<T> *current, *prev, *next;
        current = head;
        prev = next = nullptr;

        while (current)
        {
            next = current->next;
            current->next = prev;

            prev = current;
            current = next;
        }

        head = prev;

        return *this;
    }

    SinglyList& ReverseWithStack()
    {
        Node<T>* current = head;
        std::stack<Node<T>*> m_stack;

        while (current->next)
        {
            m_stack.push(current);
            current = current->next;
        }

        head = current;

        while (!m_stack.empty())
        {
            current->next = m_stack.top();
            m_stack.pop();
            current = current->next;
        }

        current->next = nullptr;

        return *this;
    }

    SinglyList& Print()
    {
        if (!head)
        {
            neo::println("SinglyList is empty, nothing to print here!");
            return *this;
        }

        Node<T>* current{ head };

        while (current)
        {
            if (current == head) std::cout << "[";

            std::cout << current->value;
            current = current->next;
            current ? (std::cout << ", ") : (std::cout << "]" << '\n');

        }

        return *this;
    }

    Node<T>* Find(const T& value)
    {
        if (!head)
        {
            neo::println("SinglyList is empty, nothing to find here!");
            return nullptr;
        }

        Node<T>* current{ head };
        
        while (current)
        {
            if (current->value == value)
                return current;
            else
                current = current->next;
        }

        return nullptr;
    }

    size_t Size() const { return m_size; }

private:
    Node<T>* head{ nullptr };
    size_t m_size{ 0 };
};