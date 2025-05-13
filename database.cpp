#include "database.h"

dataBase::dataBase() {}

// Конструктор
dataBase::dataBase(QString name, QString type, QString comment, int n)
    : name(name), type(type), n_arguments(n), comment(comment) {
    if (n_arguments > 0) {
        arguments = new QString[static_cast<unsigned>(n_arguments)];
    }
}
// Конструктор копирования
dataBase::dataBase(const dataBase &da) : dataBase(da.name, da.type,
               da.comment, da.n_arguments) {
    if (n_arguments > 0) {
        std::copy(da.arguments, da.arguments + da.n_arguments, arguments);
    }
}
// Оператор копирования
dataBase & dataBase::operator=(const dataBase &da) {
    dataBase temp(da);
    swap(*this, temp);
    return *this;
}
// Конструктор перемещения
dataBase::dataBase(dataBase &&da) noexcept {
    name = std::move(da.name);
    type = std::move(da.type);
    n_arguments = da.n_arguments;
    arguments = da.arguments;
    comment = std::move(da.comment);
    da.n_arguments = 0;
    da.name = da.type = da.comment = "";
    da.arguments = nullptr;
}
// Оператор перемещения
dataBase & dataBase::operator=(dataBase &&da) noexcept {
    if (this != &da) {
        swap(*this, da);
        da.n_arguments = 0;
        da.name = da.type = da.comment = "";
        delete[] da.arguments;
        da.arguments = nullptr;
    }
    return *this;
}
// Деструктор
dataBase::~dataBase() {
    delete[] arguments;
}
// Оператор получения элемента по индексу I
QString & dataBase::operator[](int i) {
    return arguments[i];
}
// Очистка массива
void dataBase::clear() {
    n_arguments = 0;
    name = type = comment = "";
    delete[] arguments;
    arguments = nullptr;
}
// Оператор приведения к типу bool
dataBase::operator bool() {
    return !name.isEmpty() || !type.isEmpty() || !comment.isEmpty() ||
           n_arguments != 0 || arguments != nullptr;
}
// Установка имени
void dataBase::setName(QString arg) {
    name = arg;
}
// Получение имени
const QString & dataBase::getName() {
    return name;
}
// Установка типа
void dataBase::setType(QString arg) {
    type = arg;
}
    // Получение имени
    const QString & dataBase::getType() {
    return type;
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
const int & dataBase::getNArguments() {
    return n_arguments;
}
// Установка числа аргументов
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
void swap(dataBase &first, dataBase &second) noexcept {
    std::swap(first.name, second.name);
    std::swap(first.type, second.type);
    std::swap(first.n_arguments, second.n_arguments);
    std::swap(first.arguments, second.arguments);
    std::swap(first.comment, second.comment);
}
