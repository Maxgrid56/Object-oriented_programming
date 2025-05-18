#include "database.h"

dataBase::dataBase() {}

// Конструктор
dataBase::dataBase(QString movie, QString director, int year, QString comment)
    : movie(movie), director(director), year(year), comment(comment) {
}
// Конструктор копирования
dataBase::dataBase(const dataBase &da) : dataBase(da.movie, da.director,
               da.year, da.comment) {
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
    comment = std::move(da.comment);
    da.year = 0;
    da.movie = da.director = da.comment = "";

}
// Оператор перемещения
dataBase & dataBase::operator=(dataBase &&da) noexcept {
    if (this != &da) {
        swap(*this, da);
        da.year = 0;
        da.movie = da.director = da.comment = "";
    }
    return *this;
}

// Очистка массива
void dataBase::clear() {
    year = 0;
    movie = director = comment = "";
}
// Оператор приведения к типу bool
dataBase::operator bool() {
    return !movie.isEmpty() || !director.isEmpty() || !comment.isEmpty() ||
           year != 0;
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

void dataBase::setYear(int n)
{
    year = n;
}

void swap(dataBase &first, dataBase &second) noexcept {
    std::swap(first.movie, second.movie);
    std::swap(first.director, second.director);
    std::swap(first.year, second.year);
    std::swap(first.comment, second.comment);
}
