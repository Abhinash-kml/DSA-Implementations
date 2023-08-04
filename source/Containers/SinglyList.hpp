#pragma once

#include <memory>

template<typename T>
struct Node final
{
    T data{};
    Node<T>* next{nullptr};
};

template<typename T>
class SinglyList final
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    SinglyList() = default;

    SinglyList(const SinglyList& other)
        : m_head(other.m_head)
        , m_count(other.m_count)
    {}

    SinglyList& operator=(const SinglyList& other)
    {
        m_head = other.m_head;
        m_count = other.m_count;
    }

    SinglyList(SinglyList&& other)
        : m_head(other.m_head)
        , m_count(other.m_count)
    {
        other.m_head = nullptr;
        other.m_count = nullptr;
    }

    SinglyList& operator=(SinglyList&& other)
    {
        m_head = other.m_headl;
        m_count = other.m_count;

        other.m_head = nullptr;
        other.m_count = nullptr;
    }

    ~SinglyList()
    {
        while (m_head != nullptr)
        {
            Node<T>* temp{m_head->next};
            delete m_head;
            m_head = temp;
        }
    }

public:
    void insert(const_reference object)
    {
        Node<T>* newNode = new Node<T>(object, nullptr);
        if (m_head == nullptr)
        {
            m_head = newNode;
            m_count++;
            return;
        }

        Node<T>* temp = m_head;
        while (temp->next != nullptr)
            temp = temp->next;

        temp->next = newNode;
        m_count++;
    }

    void insertAtHead(const_reference object)
    {
        Node<T>* newNode = new Node<T>(object, m_head);
        m_head = newNode;
        m_count++;
    }

    void deleteNode(const_reference object)
    {
        if (!m_head) return;

        // If the Node to be deleted is head node
        if (m_head->data == object)
        {
            Node<T>* temp = m_head;
            m_head = m_head->next;
            delete temp;
            m_count--;
            return;
        }

        // If the node to be deleted is not head node
        Node<T>* current = m_head;
        while (current->next != nullptr)
        {
            if (current->next->data == object)
            {
                Node<T>* temp{current->next};
                current->next = current->next->next;
                delete temp;
                m_count--;
            }
            else
                current = current->next;
        }
    }
    void removeAtHead()
    {
        if (m_head == nullptr)
        return;

        Node<T>* temp{m_head};
        m_head = m_head->next;
        delete temp;
        m_count--;
    }

    void removeAtIndex(size_t index)
    {
        if (!m_head) return;

        Node<T>* temp = m_head;

        if (index == 1)
        {
            m_head = m_head->next;
            delete temp;
            m_count--;
            return;
        }

        int count = index - 1;
        
        while (--count)
            temp = temp->next;

        Node<T>* temp2 = temp->next;
        temp->next = temp2->next;
        delete temp2;
        m_count--;
    }

    void remove()
    {
        removeAtIndex(m_count);
    }

    Node<T>* reverseRecursively(Node<T>* current)
    {
        if (current->next == nullptr || current == nullptr)
        {
            m_head = current;
            return current;
        }

        Node<T>* lastNode = reverseRecursively(current->next);
        lastNode->next = current;
        current->next = nullptr;
        return current;
    }

    void reverseIteratively()
    {
        Node<T>* current, *previous, *oldnext;
        current = m_head;
        previous = oldnext = nullptr;

        while (current != nullptr)
        {
            oldnext = current->next;
            current->next = previous;
            previous = current;
            current = oldnext;
        }

        m_head = previous;
    }

    void print()
    {
        Node<T>* temp = m_head;
        while (temp != nullptr)
        {
            std::cout << temp->data << " ";
            temp = temp->next;
        }

        std::cout << '\n';
    }

    Node<T>* get() { return m_head; }
private:
    Node<T>* m_head{nullptr};
    size_t m_count{};
};