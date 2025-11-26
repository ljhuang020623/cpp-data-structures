#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <cassert>


template<typename T>
class StackArray{

public:
    static const int SPARE_CAPACITY = 16;



    // ========== Rule of 5 ========= 
    // Constructor
    explicit StackArray(int initCapacity = SPARE_CAPACITY)
    : m_size{0}, 
      m_capacity{initCapacity}, 
      m_data {new T[m_capacity]}{}

    // Destructor
    ~StackArray(){
        delete[] m_data;
    }

    // Copy ctor
    StackArray(const StackArray& other)
    : m_size{other.m_size},
      m_capacity(other.m_capacity),
      m_data(new T[m_capacity])
    {
        for (int i = 0; i != m_size; ++i) {
            m_data[i] = other.m_data[i];
        }
    }

    // Copy assignment
    StackArray& operator=(const StackArray& other){
        StackArray copy{other};
        std::swap(*this, copy);
        return *this;
    }

    // Move ctor
    StackArray(StackArray&& other) noexcept
    : m_size{other.m_size},
      m_capacity{other.m_capacity},
      m_data{other.m_data}
      {
        // move semantics is like steal resource from other and make other give up,
        // if we dont reset other's member then *this.m_data and other.m_data both pointing to the same memory,
        // both dtor will run delete[] to the same pointer -> double delete(UB)
        other.m_size = 0;
        other.m_capacity = 0;
        other.m_data = nullptr;
      }
    
    // Move assignment
    StackArray& operator=(StackArray&& other) noexcept{
        std::swap(m_size, other.m_size);
        std::swap(m_capacity, other.m_capacity);
        std::swap(m_data, other.m_data);
        return *this; 
    }
    void push(const T& value){
        ensure_capacity();
        m_data[m_size++] = value;
    }

    void pop() {
        assert(!empty());  
        --m_size;
    }



    // assert(expr) will abort when expr is false, continue when expr is true
    T& top(){
        assert(!empty());
        return m_data[m_size - 1];
    }

    const T& top() const{
        assert(!empty());
        return m_data[m_size - 1];
    }


    int size() const noexcept{
        return m_size;
    }
    int capacity() const noexcept{
        return m_capacity;
    }
    bool empty() const noexcept{
        return m_size == 0;
    }




private:
    // the amount of item the stack holds
    int m_size;
    int m_capacity; 
    // the pointer to the first element of that stack
    T* m_data;

    void ensure_capacity(){
        if(m_size < m_capacity){
            return;
        }

        int new_capacity = m_capacity * 2 + 1;
        T* newStack = new T[new_capacity];
        for(int i = 0; i != m_size; ++i){
            newStack[i] = m_data[i];
        }
        delete[] m_data;

        m_data = newStack;
        m_capacity = new_capacity;
    }
};
