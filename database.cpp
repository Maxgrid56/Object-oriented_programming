#include "database.h"

dataBase::dataBase() {}

// Конструктор
dataBase::dataBase(QString movie, QString director, int year, QString comment)
    : movie(movie), director(director), year(year), comment(comment) {
    /*
    if (n_arguments > 0) {
        arguments = new QString[static_cast<unsigned>(n_arguments)];
    }
    */
}
// Конструктор копирования
dataBase::dataBase(const dataBase &da) : dataBase(da.movie, da.director,
               da.year, da.comment) {
    /*
    if (n_arguments > 0) {
        std::copy(da.arguments, da.arguments + da.n_arguments, arguments);
    }
    */
}
// Оператор копирования
dataBase & dataBase::operator=(const dataBase &da) {
    dataBase temp(da);
    swap(*this, temp);
    return *this;
}
// Конструктор перемещения
dataBase::dataBase(dataBase &&da) noexcept {
    movie = std::move(da.movie);
    director = std::move(da.director);
    year = da.year;
    //arguments = da.arguments;
    comment = std::move(da.comment);
    da.year = 0;
    da.movie = da.director = da.comment = "";
    //da.arguments = nullptr;
}
// Оператор перемещения
dataBase & dataBase::operator=(dataBase &&da) noexcept {
    if (this != &da) {
        swap(*this, da);
        da.year = 0;
        da.movie = da.director = da.comment = "";
        //delete[] da.arguments;
        //da.arguments = nullptr;
    }
    return *this;
}
// Деструктор
/*
dataBase::~dataBase() {
    delete[] arguments;
}
*/
// Оператор получения элемента по индексу I
/*
QString & dataBase::operator[](int i) {
    return arguments[i];
}
*/
// Очистка массива
void dataBase::clear() {
    year = 0;
    movie = director = comment = "";
    //delete[] arguments;
    //arguments = nullptr;
}
// Оператор приведения к типу bool
dataBase::operator bool() {
    return !movie.isEmpty() || !director.isEmpty() || !comment.isEmpty() ||
           year != 0 /*|| arguments != nullptr*/;
}
// Установка имени
void dataBase::setMovie(QString arg) {
    movie = arg;
}
// Получение имени
const QString & dataBase::getMovie() {
    return movie;
}
// Установка типа
void dataBase::setDirector(QString arg) {
    director = arg;
}
    // Получение имени
    const QString & dataBase::getDirector() {
    return director;
}
// Установка комментария
void dataBase::setComment(QString arg) {
    comment = arg;
}
// Получение комментария
const QString & dataBase::getComment() {
    return comment;
}
// Получение количества аргументов
const int & dataBase::getYear() {
    return year;
}
// Установка числа аргументов
/*
void dataBase::setNArguments(int n) {
    if (n > 0) {
        QString *temp = new QString[static_cast<unsigned>(n)];
        std::copy(arguments, arguments + std::min(n, n_arguments), temp);
        std::swap(arguments, temp);
        n_arguments = n;
        delete[] temp;
        temp = nullptr;
        return;
    }
    // if n == 0
    delete[] arguments;
    arguments = nullptr;
    n_arguments = 0;
}
*/

void dataBase::setYear(int n)
{
    year = n;
}

void swap(dataBase &first, dataBase &second) noexcept {
    std::swap(first.movie, second.movie);
    std::swap(first.director, second.director);
    std::swap(first.year, second.year);
    //std::swap(first.arguments, second.arguments);
    std::swap(first.comment, second.comment);
}
