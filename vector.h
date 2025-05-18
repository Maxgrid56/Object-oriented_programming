#ifndef VECTOR_H
#define VECTOR_H

// C++ program to implement a custom container class template with basic operations.
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <memory>
#include <QString>
using namespace std;


template <class T>
class Vector {
private:
    // Начальный размер массива
    int n_ = 0;
    // Зарезервированный размер массива (m_ >= n_)
    int m_ = 10;
    // Указатель на массив из m_ элементов
    T *values_ = nullptr;

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
        std::copy(da.values_, da.values_ + n_, values_);
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
