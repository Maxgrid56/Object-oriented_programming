#ifndef VECTOR_H
#define VECTOR_H

// C++ program to implement a custom container class template with basic operations.
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <memory>
#include <QString>
using namespace std;

/*
// Custom container class template
template <class T, class Allocator = allocator<T>> class Array{         //название каждого элемента темплейта прописывается с заглавной буквы
public:
    // Type definitions for easier access to types used in the container
    // Type of elements stored in the container
    using value_type = T;

    // Allocator type used for memory management
    using allocator_type = Allocator;

    // Reference type to the container's elements
    using reference = value_type &;

    // Constant reference type to the container's elements
    using const_reference = const value_type &;

    // Type for size and capacity of the container
    using size_type = size_t;

    // Type for difference between iterator positions
    using difference_type = ptrdiff_t;

    using alloc_traits = std::allocator_traits<Allocator>;

    // Iterator class for the custom container
    class iterator{
    public:
        // Type definitions for the iterator

        // Category tag for random access iterators
        using iterator_category = random_access_iterator_tag;

        // Type of elements the iterator points to
        using value_type = T;

        // Type for difference between iterators
        using difference_type = ptrdiff_t;

        // Pointer type to the element
        using pointer = T *;
        // Reference type to the element
        using reference = T &;

        // Constructor to initialize the iterator with a pointer to an element
        iterator(pointer ptr) : ptr_(ptr) {
        }

        // Dereference operator to access the element pointed to by the iterator
        reference operator*() const{
            return *ptr_;
        }

        // Arrow operator to access the element's members
        pointer operator->() const{
            return ptr_;
        }

        T &operator[] (size_type index) {
            if (index >= size_){

                // Throw an exception if the index is invalid
                throw out_of_range("Index out of range");
            }
            return data_[index];
        }

        // Prefix increment operator to move the iterator to the next element
        iterator &operator++(){
            ++ptr_;
            return *this;
        }

        // Postfix increment operator to move the iterator to the next element and return the previous
        // position
        iterator operator++(int) {
            iterator temp = *this;
            ++ptr_;
            return temp;
        }

        // Equality operator to compare if two iterators are equal (point to the same element)
        bool operator==(const iterator &other) const{
            return ptr_ == other.ptr_;
        }

        // Inequality operator to compare if two iterators are not equal (point to different elements)
        bool operator!=(const iterator &other) const{
            return ptr_ != other.ptr_;
        }

    private:
        pointer ptr_; // Pointer to the element the iterator currently points to
    };

    // Default constructor to create an empty container
    Array() : data_(nullptr), size_(0), capacity_(0){
    }

    // Copy constructor to create a container as a copy of another container
    Array(const Array &other) : size_(other.size_), capacity_(other.capacity_) {
        data_ = alloc_traits::allocate(alloc_, capacity_);
        for (size_type i = 0; i < size_; ++i) {
            alloc_traits::construct(alloc_, data_ + i, other.data_[i]);
        }
    }

    // Destructor to clean up the allocated memory when the container is destroyed
    ~Array(){
        // Deallocate the allocated memory
        clear();
        alloc_.deallocate(data_, capacity_);
    }

    // Member function to add a new element at the end of the container
    void push_back(const T &value) {
        if (size_ == capacity_) {
            reserve(capacity_ ? 2 * capacity_ : 1);
        }
        alloc_traits::construct(alloc_, data_ + size_, value);
        ++size_;
    }

    // Member function to remove the last element from the container
    void pop_back() {
        if (size_ > 0) {
            --size_;
            alloc_traits::destroy(alloc_, data_ + size_);
        }
    }

    // Уничтожаем все объекты
    void clear() {
        for (size_type i = 0; i < size_; ++i) {
            alloc_traits::destroy(alloc_, data_ + i);
        }
        size_ = 0;
    }

    // Перемещаем или копируем
    void reserve(size_type new_capacity) {
        if (new_capacity <= capacity_) return;

        T *new_data = alloc_traits::allocate(alloc_, new_capacity);
        for (size_type i = 0; i < size_; ++i) {
            alloc_traits::construct(alloc_, new_data + i, std::move_if_noexcept(data_[i]));
            alloc_traits::destroy(alloc_, data_ + i);
        }

        alloc_traits::deallocate(alloc_, data_, capacity_);
        data_ = new_data;
        capacity_ = new_capacity;
    }

    // Member function to access an element at a given index with bounds checking
    reference at(size_type index){
        if (index >= size_){

            // Throw an exception if the index is invalid
            throw out_of_range("Index out of range");
        }
        return data_[index];
    }

    // Const version of the 'at' function to access elements in a read-only context
    const_reference at(size_type index) const{
        if (index >= size_){

            // Throw an exception if the index is invalid
            throw out_of_range("Index out of range");
        }
        return data_[index];
    }

    // Member function to get the number of elements currently in the container
    size_type size() const{
        return size_;
    }

    // Member function to check if the container is empty
    bool empty() const{
        return size_ == 0;
    }

    // Member function to get an iterator pointing to the first element of the container
    iterator begin(){
        return iterator(data_);
    }

    // Member function to get an iterator pointing to the end (one past the last element) of the container
    iterator end(){
        return iterator(data_ + size_);
    }

private:
    // Pointer to the container's elements
    T *data_;

    // Number of elements in the container
    size_type size_;

    // Allocated capacity of the container
    size_type capacity_;

    // Экземпляр аллокатора
    Allocator alloc_;
};
*/


template <class T>
class Vector {
private:
    // Начальный размер массива
    int n_ = 0;
    // Зарезервированный размер массива (m_ >= n_)
    int m_ = 10;
    // Указатель на массив из m_ элементов
    T *values_ = nullptr;

    // da в дальнейшем воспринимается как "different array" (other)
protected:
    // Стандартное количество резервируемых элементов в массиве
    int standart = 10;
public:
    // Конструктор
    explicit Vector(int n = 0) : n_(n) {
        if (n >= m_) {
            m_ = n * 2;
        }
        values_ = new T[m_] {};
    }
    // Конструктор копирования
    Vector(const Vector &da) : Vector(da.n_) {
        n_ = da.n_;
        std::copy(da.values_, da.values_ + n_, values_);        // копировать с da.values по da.values + n из массива values
    }
    // Оператор копирования
    Vector &operator=(const Vector &da){
        Vector temp(da);
        swap(*this, temp);
        return *this;
    }
    // Конструктор перемещения
    Vector(Vector &&da) noexcept {
        n_ = da.n_, m_ = da.m_, values_ = da.values_, standart =
                                                      da.standart;
        da.n_ = 0, da.m_ = 0, da.values_ = nullptr;
    }
    // Оператор перемещения
    Vector &operator=(Vector &&da) noexcept {
        if (this != &da) {
            swap(*this, da);
            delete[] da.values_, da.values_ = nullptr;
            da.n_ = 0, da.m_ = 0;
        }
        return *this;
    }
    // Деструктор
    virtual ~Vector() {
        delete[] values_;
    }
    // Оператор получения элемента по индексу I
    T &operator[](int i) {
        return values_[i];
    }
    // [static] Получение размера массива
    static int size(const Vector &da) {
        return da.n_;
    }
    // Добавление K элементов из массива DA в конец
    void add(const Vector &da, const int &k) {
        int mn = std::min(Vector::size(da), k);
        for (int i = 0; i < mn; ++i) {
            push_back(da.values_[i]);
        }
    }
    // Вставка элемента D в позицию K
    void insert(const T &d, const int &k) noexcept(false) {
        if (k == 0) {
            push_front(d);
            return;
        } else if (k == n_) {
            push_back(d);
            return;
        } else if (k > 0 && k < n_) {
            push_back(d);
            T t = values_[k], p;
            for (int i = k; i < n_; ++i) {
                p = values_[i], values_[i] = t, t = p;
            }
            values_[k] = d;
            return;
        }
        throw std::out_of_range("Vector. Method insert. Out of range");
    }
    // Добавление элемента D в конец
    void push_back(const T &d) {
        if (n_ < m_) {
            values_[n_] = d, ++n_;
            return;
        }
        T *b = values_;
        values_ = new T[m_ * 2] {};
        std::copy(b, b + n_, values_);
        delete[] b;
        m_ *= 2;
    }
    // Добавление элемента D в начало
    void push_front(const T &d) {
        push_back(d);
        T t = values_[0], p;
        for (int i = 1; i < n_; ++i) {
            p = values_[i], values_[i] = t, t = p;
        }
        values_[0] = d;
    }
    // Очистка массива
    void clear() {
        delete[] values_;
        values_ = new T[standart] {};
        n_ = 0, m_ = standart;
    }
    // Получение размера массива
    int size() const noexcept { return n_; }
    // Пустой ли массив
    bool empty() const noexcept { return n_ == 0; }
    // Удаление элемента с индексом I
    T erase(int i) noexcept(false) {
        if (n_ > 0 && i < n_) {
            T d = values_[i];
            std::copy(values_ + i + 1, values_ + n_, values_ + i);
            --n_;
            return d;
        }
        throw std::out_of_range("Vector. Method erase. Out of range");
    }
    // Удаление первого (нулевого) элемента
    T pop_front() {
        return erase(0);
    }
    // Удаление последнего элемента
    T pop_back() {
        T d = T();
        if (n_ > 0) {
            d = values_[n_ - 1], --n_;
        }
        return d;
    }
    // Оператор приведения к типу bool
    explicit operator bool() {
        return n_ != 0;
    }
    friend void swap(Vector &first, Vector &second) noexcept {
        std::swap(first.standart, second.standart);
        std::swap(first.values_, second.values_);
        std::swap(first.m_, second.m_);
        std::swap(first.n_, second.n_);
    }
    // Класс итератора по элементам
    class iterator {
    public:
        T *i;
            typedef std::random_access_iterator_tag iterator_category;
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
        inline iterator() : i(0) {}
        inline explicit iterator(T *n) : i(n) {}
        inline iterator(const iterator &o): i(o.i){}
        inline T &operator*() const { return *i; }
        inline T *operator->() const { return i; }
        inline T &operator[](int j) const { return i[j]; }
        inline bool operator==(const iterator &o) const { return i == o.i;
        }
        inline bool operator!=(const iterator &o) const { return i != o.i;
        }
        inline bool operator<(const iterator& other) const { return i <
                                                                    other.i; }
        inline bool operator<=(const iterator& other) const { return i <=
                                                                     other.i; }
        inline bool operator>(const iterator& other) const { return i >
                                                                    other.i; }
        inline bool operator>=(const iterator& other) const { return i >=
                                                                     other.i; }
        inline iterator &operator++() { ++i; return *this; }
        inline const iterator operator++(int) { T *n = i; ++i; return
                iterator(n); }
        inline iterator &operator--() { i--; return *this; }
        inline const iterator operator--(int) { T *n = i; i--; return
                iterator(n); }
        inline iterator &operator+=(int j) { i+=j; return *this; }
        inline iterator &operator-=(int j) { i-=j; return *this; }
        inline iterator operator+(int j) const { return iterator(i+j); }
        inline iterator operator-(int j) const { return iterator(i-j); }
        inline int operator-(iterator j) const { return int(i - j.i); }
    };
    inline typename Vector<T>::iterator begin() { return
                                                  iterator(&values_[0]); }
    inline typename Vector<T>::iterator end() { return
                                                iterator(&values_[n_]); }
};

#endif // VECTOR_H
