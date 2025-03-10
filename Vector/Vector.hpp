#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <initializer_list>
#include <utility>
#include <stdexcept>

template <typename T>
class KVector
{
public:
    // 初始化与析构
    KVector();
    KVector(std::initializer_list<T> init);
    KVector(const KVector& other);
    KVector(KVector&& other) noexcept;
    KVector& operator=(const KVector& other);
    KVector& operator=(KVector&& other) noexcept;
    ~KVector();

    void push_back(const T& value);
    void push_back(T&& value);
    void pop_back();

    T& at(size_t index);
    const T& at(size_t index) const;

    T& front();
    const T& front() const;

    T& back();
    const T& back() const;

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    size_t getSize() const;
    size_t getCapacity() const;
    void clear();
    void erase(size_t index);
    void insert(size_t index, const T& value);
    void assign(std::initializer_list<T> init);

    bool empty() const;

    // 迭代器
    class Iterator {
    private:
        T* ptr;

    public:
        explicit Iterator(T* p = nullptr) : ptr(p) {}

        T& operator*() { return *ptr; }
        const T& operator*() const { return *ptr; }
        T* operator->() { return ptr; }
        const T* operator->() const { return ptr; }

        Iterator& operator++() { ++ptr; return *this; }

        Iterator operator++(int) { Iterator temp = *this; ++(*this); return temp; }

        Iterator& operator--() { --ptr; return *this; }

        Iterator operator--(int) { Iterator temp = *this; --(*this); return temp; }

        bool operator==(const Iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
    };

    Iterator begin() { return Iterator(m_data); }
    const Iterator begin() const { return Iterator(m_data); }
    Iterator end() { return Iterator(m_data + m_size); }
    const Iterator end() const { return Iterator(m_data + m_size); }

private:
    T* m_data;
    size_t m_size;
    size_t m_capacity;

    void resize(size_t capacity);
};

template <typename T>
KVector<T>::KVector() : m_data(nullptr), m_size(0), m_capacity(0) {}

template <typename T>
KVector<T>::KVector(std::initializer_list<T> init) : m_data(0), m_size(0), m_capacity(0) {
    for (const auto& value : init) {
        push_back(value);
    }
}

template <typename T>
KVector<T>::KVector(const KVector& other) : m_data(nullptr), m_size(0), m_capacity(0) {
    for (const auto& value : other) {
        push_back(value);
    }
}

template <typename T>
KVector<T>::KVector(KVector&& other) noexcept : m_data(other.m_data), m_size(other.m_size), m_capacity(other.m_capacity) {
    other.m_data = nullptr;
    other.m_size = 0;
    other.m_capacity = 0;
}

template <typename T>
KVector<T>& KVector<T>::operator=(const KVector& other) {
    if (this != &other) {
        delete[] m_data;
        m_size = 0;
        m_capacity = 0;
        for (const auto& value : other) {
            push_back(value);
        }
    }
    return *this;
}

template <typename T>
KVector<T>& KVector<T>::operator=(KVector&& other) noexcept {
    if (this != &other) {
        delete[] m_data;
        m_data = other.m_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }
    return *this;
}

template <typename T>
KVector<T>::~KVector() {
    delete[] m_data;
}

template <typename T>
void KVector<T>::push_back(const T& value) {
    if (m_size == m_capacity) resize(2 * m_capacity + 1);
    m_data[m_size++] = value;
}

template <typename T>
void KVector<T>::push_back(T&& value) {
    if (m_size == m_capacity) resize(2 * m_capacity + 1);
    m_data[m_size++] = std::move(value);
}

template <typename T>
void KVector<T>::pop_back() {
    if (m_size == 0) throw std::underflow_error("队列为空，无法执行pop_back");
    --m_size;
}

template <typename T>
T& KVector<T>::at(size_t index) {
    if (index >= m_size) throw std::out_of_range("索引超出范围");
    return m_data[index];
}

template <typename T>
const T& KVector<T>::at(size_t index) const {
    if (index >= m_size) throw std::out_of_range("索引超出范围");
    return m_data[index];
}

template <typename T>
T& KVector<T>::front() {
    if (m_size == 0) throw std::underflow_error("队列为空,无法访问前端元素");
    return m_data[0];
}

template <typename T>
const T& KVector<T>::front() const {
    if (m_size == 0) throw std::underflow_error("队列为空,无法访问前端元素");
    return m_data[0];
}

template <typename T>
T& KVector<T>::back() {
    if (m_size == 0) throw std::underflow_error("队列为空,无法访问尾部元素");
    return m_data[m_size - 1];
}

template <typename T>
const T& KVector<T>::back() const {
    if (m_size == 0) throw std::underflow_error("队列为空,无法访问尾部元素");
    return m_data[m_size - 1];
}

template <typename T>
T& KVector<T>::operator[](size_t index) {
    if (index >= m_size) throw std::out_of_range("索引超出范围");
    return m_data[index];
}

template <typename T>
const T& KVector<T>::operator[](size_t index) const {
    if (index >= m_size) throw std::out_of_range("索引超出范围");
    return m_data[index];
}

template <typename T>
size_t KVector<T>::getSize() const {
    return m_size;
}

template <typename T>
size_t KVector<T>::getCapacity() const {
    return m_capacity;
}

template <typename T>
void KVector<T>::clear(){
    m_size = 0;
}

template <typename T>
void KVector<T>::erase(size_t index) {
    if (index >= m_size) throw std::out_of_range("索引超出范围");

    for (size_t i = index; i < m_size - 1; ++i) {
        m_data[i] = std::move(m_data[i + 1]);
    }
    --m_size;
}

template <typename T>
void KVector<T>::insert(size_t index, const T& value) {
    if (index > m_size) throw std::out_of_range("插入索引超出范围");

    if (m_size == m_capacity) resize(2 * m_capacity + 1);

    for (size_t i = m_size; i > index; --i) {
        m_data[i] = std::move(m_data[i - 1]);
    }

    m_data[index] = value;
    ++m_size;
}

template <typename T>
void KVector<T>::assign(std::initializer_list<T> init) {
    clear();
    for (const auto& value : init) {
        push_back(value);
    }
}

template <typename T>
bool KVector<T>::empty() const {
    return m_size == 0;
}

template <typename T>
void KVector<T>::resize(const size_t capacity) {
    T* newData = new T[capacity];
    for (size_t i = 0; i < m_size; i++) {
        newData[i] = std::move(m_data[i]);
    }
    delete[] m_data;
    m_data = newData;
    m_capacity = capacity;
}

#endif // VECTOR_HPP