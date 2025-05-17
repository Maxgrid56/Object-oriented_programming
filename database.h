#ifndef DATABASE_H
#define DATABASE_H

#include "database.h"
#include <QString>
#include <QtAlgorithms>

class dataBase
{
private:
    // Имя
    QString movie = "";
    // Тип
    QString director = "";
    // Количество аргументов
    int year = 0;
    // Аргументы
    //QString *arguments = nullptr;
    // Комментарий к функции
    QString comment = "";

public:
    // Конструктор по умолчанию
    dataBase();

    // Конструктор
    explicit dataBase(QString movie, QString director, int year, QString comment);  // name заменил на movie, type заменил на director, comment и int n заменил местами, переименовав int n в int year;

    // Конструктор копирования
    dataBase(const dataBase &da);
    // Оператор копирования
    dataBase &operator=(const dataBase &da);
    // Конструктор перемещения
    dataBase(dataBase &&da) noexcept;
    // Оператор перемещения
    dataBase &operator=(dataBase &&da) noexcept;
    // Деструктор
    //virtual ~dataBase();
    // Оператор получения элемента по индексу I
    //QString &operator[](int i);
    // Очистка массива
    void clear();
    // Оператор приведения к типу bool
    explicit operator bool();
    // Установка имени
    void setName(QString arg);
        // Получение имени
        const QString &getName();
    // Установка типа
    void setType(QString arg);
    // Получение имени
    const QString &getType();
    // Установка комментария
    void setComment(QString arg);
    // Получение комментария
    const QString &getComment();
    // Получение количества аргументов
    const int &getNArguments();
    // Установка числа аргументов
    void setNArguments(int n);
    friend void swap(dataBase &first, dataBase &second) noexcept;
    // Класс итератора по аргументам
    class iterator {
    public:
        QString *i;
        typedef std::random_access_iterator_tag iterator_category;
        typedef ptrdiff_t difference_type;
        typedef QString value_type;
        typedef QString *pointer;
        typedef QString &reference;
        inline iterator() : i(nullptr) {}
        inline explicit iterator(QString *n) : i(n) {}
        inline iterator(const iterator &o): i(o.i){}
        inline QString &operator*() const { return *i; }
        inline QString *operator->() const { return i; }
        inline QString &operator[](int j) const { return i[j]; }
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
        inline const iterator operator++(int) { QString *n = i; ++i;
            return iterator(n); }
        inline iterator &operator--() { i--; return *this; }
            inline const iterator operator--(int) { QString *n = i; i--;
            return iterator(n); }
        inline iterator &operator+=(int j) { i+=j; return *this; }
        inline iterator &operator-=(int j) { i-=j; return *this; }
        inline iterator operator+(int j) const { return iterator(i+j); }
        inline iterator operator-(int j) const { return iterator(i-j); }
        inline int operator-(iterator j) const { return int(i - j.i); }
    };
    /*
    inline typename dataBase::iterator begin() { return
                                                 iterator(&arguments[0]); }
    inline typename dataBase::iterator end() { return
                                               iterator(&arguments[n_arguments]); }
    */
};

#endif // DATABASE_H
