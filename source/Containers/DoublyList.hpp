#pragma once

#include <iosfwd>
#include <cstdint>
#include <functional>

namespace neo
{
    auto println = [](const char* str) { std::cout << str << '\n'; };
}

enum class EPrintMode : std::uint8_t
{
    FOWARD = 0,
    BACKWARD
};

template<typename T>
struct Node final
{
    Node() = default;

    Node(const T& value, Node<T>* prev = nullptr, Node<T>* next = nullptr)
        : value{ value }
        , prev{ prev }
        , next{ next }
    { }

    T value{};
    Node<T>* prev{ nullptr };
    Node<T>* next{ nullptr };
};

template<typename T>
class DoublyList final
{
public:
    DoublyList() = default;

    DoublyList(const T& value)
        : head{ new Node<T>(value) }
    { }

    DoublyList(const DoublyList& other) = default;
    DoublyList& operator=(const DoublyList& other) = default;
    DoublyList(DoublyList&& other) = default;
    DoublyList& operator=(DoublyList&& other) = default;

    ~DoublyList() = default;

public:
    DoublyList& PushBack(const T& value)
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
        newNode->prev = current;
        m_size++;

        return *this;
    }

    DoublyList& PushFront(const T& value)
    {
        Node<T> *newNode, *current;

        if (!head)
        {
            newNode = new Node<T>(value);
            head = newNode;
        }

        newNode = new Node<T>(value);
        current = head;

        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        m_size++;

        return *this;
    }

    DoublyList& PushAfter(Node<T>* previousNode, const T& value)
    {
        Node<T>* newNode;

        if (!head)
        {
            newNode = new Node<T>(value);
            head = newNode;
            m_size++;

            return *this;
        }

        newNode = new Node<T>(value);

        newNode->next = previousNode->next;
        newNode->prev = previousNode;
        previousNode->next = newNode;
        newNode->next->prev = newNode;
    }

    Node<T>* Find(const T& value)
    {
        if (!head)
        {
            neo::println("List is empty, nothing to find here!");
            return nullptr;
        }

        Node<T>* current = head;
        
        while (current)
        {
            if (current->value == value)
                return current;

            current = current->next;
        }

        return nullptr;
    }

    DoublyList& Erase(const T& value)
    {
        if (!head)
        {
            neo::println("List is empty, nothing to erase here!");
            return *this;
        }

        Node<T>* current = head;

        if (current->value == value)
        {
            Node<T>* temp{ current->next };
            delete current;

            head = temp;
            head->prev = nullptr;

            return *this;
        }

        current = head;

        while (current->next)
        {
            if (current->next->value == value)
            {
                Node<T>* temp{ current->next };
                current->next->next->prev = current;
                current->next = current->next->next;
                delete temp;
            }
            else
            {
                current = current->next;
            }
        }

        return *this;
    }

    DoublyList& Print(EPrintMode mode = EPrintMode::FOWARD)
    {
        if (!head)
        {
            neo::println("List is empty, nothing to print here!");
            return *this;
        }

        Node<T>* current = std::invoke([this, &mode]() -> Node<T>* {
            switch (mode)
            {
                case EPrintMode::FOWARD: return head; break;
                case EPrintMode::BACKWARD: {
                    Node<T>* ptr{ head };
                    while (ptr->next)
                        ptr = ptr->next;

                    return ptr;
                }; break;
                default: return nullptr; break;
            }
        });

        switch (mode)
        {
            case EPrintMode::FOWARD: {
                while (current) {
                    std::cout << current->value << " ";
                    current = current->next;
                }

                std::cout << '\n';
            }; break;

            case EPrintMode::BACKWARD: {
                while (current) {
                    std::cout << current->value << " ";
                    current = current->prev;
                }

                std::cout << '\n';
            }; break;
        }

        return *this;
    }

private:
    Node<T>* head{ nullptr };
    size_t m_size{ 0 };
};