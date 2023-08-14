#pragma once

#include <memory>

template<typename T>
struct Object final
{
    T value{};
    int32_t priority{};
};

template<typename T, size_t N>
class priority_queue final
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    priority_queue() = default;
    priority_queue(const priority_queue& other) = default;
    priority_queue& operator=(const priority_queue& other) = default;
    priority_queue(priority_queue&& other) = default;
    priority_queue& operator=(priority_queue&& other) = default;
    ~priority_queue() = default;

    Object<T>& operator[](size_t index)
    {
        return arr[index];
    }

public:
    void enqueue(const_reference object, int priority)
    {
        size++; 
        
        arr[size].value = object;
        arr[size].priority = priority;
    }

    Object<T> dequeue()
    {
        // Find the position of the element
        // with highest priority
        int index = GetHighestPriority();

        Object<T> object = arr[index];
    
        // Shift the element one index before
        // from the position of the element
        // with highest priority is found
        for (int i = index; i < size; i++) {
            arr[i] = arr[i + 1];
        }
    
        // Decrease the size of the
        // priority queue by one
        size--;
        
        return object;
    }

    int GetHighestPriority()
    {
        if (size == 1)
        {
            return arr[0].priority;
        }

        int highestPriority = INT_MIN;
        int index = -1;
    
        // Check for the element with
        // highest priority
        for (int i = 0; i <= size; i++) 
        {
            if (arr[i].priority > highestPriority) 
            {
                highestPriority = arr[i].priority;
                index = i;
            }
            else if (arr[i].priority == highestPriority 
                    && arr[i].value > arr[i - 1].value) // if priority is same we choose the element with the highest value
            {
                highestPriority = arr[i].priority;
                index = i;
            }
        }
    
        // Return position of the element
        return index;
    }

    bool isfull() const { return size == N; }

    bool isempty() const { return size == 0; }

private:
    Object<T> arr[N];
    int32_t size{};
};