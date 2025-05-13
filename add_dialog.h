#ifndef ADD_DIALOG_H
#define ADD_DIALOG_H

#include <QDialog>
#include <QtWidgets>
#include "database.h"

class Add_Dialog : public QDialog
{
    Q_OBJECT

public:
    /*explicit*/ Add_Dialog(QWidget *parent = nullptr);
    //~Add_Dialog();
    dataBase getData();
    void setType(QString arg);
    void setName(QString arg);
    void setArgs(QString arg);
    void setComment(QString arg);
private:

    QDialogButtonBox* buttonBox;
    QLineEdit* lineEdit;
    QLineEdit* lineEdit_2;
    QLineEdit* lineEdit_3;
    QLineEdit* lineEdit_4;
    QLabel* label;
    QLabel* label_2;
    QLabel* label_3;
    QLabel* label_4;
};
#endif // ADD_DIALOG_H
