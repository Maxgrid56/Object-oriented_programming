#ifndef SHOW_DATA_H
#define SHOW_DATA_H

#include <QDialog>
#include <QtWidgets>

class Show_Data : public QDialog
{
    Q_OBJECT

public:
    /*explicit*/ Show_Data(QWidget *parent = nullptr);
    void setText(const QString &str);
    QString getText();
    //~Show_Data();

private slots:
    void pushButton_clicked();

private:


    QTextEdit* textEdit;
    QPushButton* pushButton;
    QVBoxLayout* showDataMainLayout;
};

#endif // SHOW_DATA_H
