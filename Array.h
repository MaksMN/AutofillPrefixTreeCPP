#pragma once
#include "ArrayExceptions.h"
#include <string>
#include <iostream>
/// @brief Создает массив
template <typename T>
class Array
{
private:
    int m_length{};
    T *m_data{};
    int null_ptr = 0;

public:
    Array() = default;

    /// @brief Создает массив указанной длинны
    /// @param <int>length Длина массива
    Array(int length) : m_length{length}
    {
        if (length < 0)
        {
            throw ArrayBadLength();
        }
        if (length > 0)
        {
            m_data = new T[length]{};
        }
    }

    /// @brief Конструктор копирования
    /// @param <Array>a
    Array(const Array &a)
    {
        reallocate(a.getLength());
        for (int index{0}; index < m_length; ++index)
        {
            m_data[index] = a.m_data[index];
        }
    }

    ~Array()
    {
        delete[] m_data;
    }

    /// @brief Удаляет все элементы массива
    void erase()
    {
        delete[] m_data;
        m_data = nullptr;
        m_length = 0;
    }

    T &operator[](int index)
    {
        if (index < 0 || index > m_length || m_length == 0)
        {
            throw ArrayBadRange();
        }
        return m_data[index];
    }

    /// @brief Меняет размер массива с удалением существующих элементов.
    /// @exception ArrayBadLength
    /// @param <int>newLength Новая длинна массива.
    void reallocate(int newLength)
    {
        if (newLength <= 0 || newLength == m_length)
        {
            throw ArrayBadLength();
        }
        erase();
        if (newLength <= 0)
            return;
        m_data = new T[newLength];
        m_length = newLength;
    }

    /// @brief Меняет размер массива. Существующие элементы сохранены.
    /// @exception ArrayBadLength
    /// @param <int>newLength Новая длинна массива.
    void resize(int newLength)
    {
        if (newLength <= 0 || newLength == m_length)
        {
            throw ArrayBadLength();
        }
        T *data{new T[newLength]};
        if (m_length > 0)
        {
            int elementsToCopy{(newLength > m_length) ? m_length : newLength};

            for (int index{0}; index < elementsToCopy; ++index)
            {
                data[index] = m_data[index];
            }
        }
        delete[] m_data;
        m_data = data;
        m_length = newLength;
    }

    Array &operator=(const Array &a)
    {
        if (&a == this)
        {
            return *this;
        }
        reallocate(a.getLength());
        for (int index{0}; index < m_length; ++index)
        {
            m_data[index] = a.m_data[index];
        }
        return *this;
    }

    /// @brief Добавляет в массив элемент перед указанным индексом
    /// @exception ArrayBadRange
    /// @param value Значение нового элемента
    /// @param index Индекс перед которым будет создан новый элемент
    void insertBefore(T value, int index)
    {
        if (index < 0 || index > m_length)
        {
            throw ArrayBadRange();
        }
        T *data{new T[m_length + 1]};
        for (int before{0}; before < index; ++before)
        {
            data[before] = m_data[before];
        }
        data[index] = value;
        for (int after{index}; after < m_length; ++after)
        {
            data[after + 1] = m_data[after];
        }
        delete[] m_data;
        m_data = data;
        ++m_length;
    }

    /// @brief Удаляет из массива элемент с указанным индексом
    /// @exception ArrayBadRange
    /// @param index Индекс перед которым будет создан новый элемент
    void remove(int index)
    {
        if (index < 0 || index > m_length)
        {
            throw ArrayBadRange();
        }
        if (m_length == 1)
        {
            erase();
            return;
        }
        T *data{new T[m_length - 1]};
        for (int before{0}; before < index; ++before)
        {
            data[before] = m_data[before];
        }
        for (int after{index + 1}; after < m_length; ++after)
        {
            data[after - 1] = m_data[after];
        }
        delete[] m_data;
        m_data = data;
        --m_length;
    }

    /// @brief Добавляет элемент в начало массива
    /// @param value Значение нового элемента
    void insertAtBeginning(T value) { insertBefore(value, 0); }

    /// @brief Добавляет элемент в конец массива
    /// @param value Значение нового элемента
    void insertAtEnd(T value) { insertBefore(value, m_length); }

    /// @brief Возвращает длину массива
    /// @return int
    int getLength() const { return m_length; }

    /// @brief Поиск элемента по значению
    /// @exception ArrayNoFoundException
    /// @param value
    /// @return Индекс первого найденного элемента в массиве
    int search(T value)
    {
        for (int i = 0; i < getLength(); i++)
        {
            if (m_data[i] == value)
            {
                return i;
            }
        }
        throw ArrayNotFound();
    }

    /// @brief Поиск всех элементов по значению
    /// @exception ArrayNoFoundException
    /// @param value
    /// @return Массив Array с найденными элементами.
    Array<int> searchAll(T value)
    {
        Array<int> results;
        for (int i = 0; i < getLength(); i++)
        {
            if (m_data[i] == value)
            {
                results.insertAtEnd(i);
            }
        }
        if (results.getLength() > 0)
        {
            return results;
        }
        else
        {
            throw ArrayNotFound();
        }
    }

    /// @brief Выводит на экран список всех элементов массива
    /// @param message Сообщение перед выводом списка
    void listValues(std::string message, bool showIndexes = true)
    {
        std::cout << message;
        for (int i = 0; i < getLength(); i++)
        {
            if (showIndexes)
            {
                std::cout << "[" << i << "]=>";
            }
            std::cout << m_data[i] << " ";
        }
        std::cout << std::endl;
    }
};