#ifndef VECTOR_H
#define VECTOR_H

#include <cstdint>
#include <stdexcept>

namespace Containers
{

#define GROWTH_RATE 2

template <class T>
class Vector
{
public:
    Vector() = default;
    Vector(std::size_t size);
    ~Vector();

    T& operator[](std::size_t n);
    void push_back(const T& item);
    void pop_back();

    uint64_t size() const;

private:
    void grow();

    uint64_t m_size = 0;
    uint64_t m_available_space = 0;
    T* m_data = nullptr;
};

template <class T>
Vector<T>::Vector(std::size_t size)
{
    m_data = new T[size];
    m_available_space = size;
}

template <class T>
Vector<T>::~Vector()
{
    delete m_data;
}

template <class T>
T& Vector<T>::operator[](std::size_t n)
{
    if (n >= m_size)
    {
        throw std::out_of_range{"Vector index 'n' is out of range."};
    }
    return m_data[n];
}

template <class T>
void Vector<T>::push_back(const T& item)
{
    if (m_size >= m_available_space)
    {
        grow();
    }

    m_data[m_size] = item;
    m_size++;
}

template <class T>
void Vector<T>::pop_back()
{
    m_size--;
}

template <class T>
uint64_t Vector<T>::size() const
{
    return m_size;
}

template <class T>
void Vector<T>::grow()
{
    m_available_space = m_available_space * GROWTH_RATE;
    T* new_data = new T[m_available_space];

    std::copy(m_data, m_data + m_size, new_data);
    m_data = new_data;
}
}
#endif  // VECTOR_H