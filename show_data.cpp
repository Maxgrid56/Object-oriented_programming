#include "show_data.h"
#include "ui_show_data.h"


Show_Data::Show_Data(QWidget *parent) :
    QDialog(parent)//,
    //ui(new Ui::Show_Data)
{
    //ui->setupUi(this);            //попробуй не использовать закомменченые части кода.

    this->setGeometry(0, 0, 570, 480);
    this->show();
    this->setWindowTitle("CSV-отображение");

    showDataMainLayout = new QVBoxLayout;
    textEdit = new QTextEdit;
    pushButton = new QPushButton;
    pushButton->setText("OK");
    showDataMainLayout->addWidget(textEdit);
    showDataMainLayout->addWidget(pushButton);

    this->setLayout(showDataMainLayout);
}

void Show_Data::setText(const QString &str)
{
    textEdit->setText(str);
}

QString Show_Data::getText()
{
    return textEdit->toPlainText();
}
/*
Show_Data::~Show_Data()
{
    delete ui;
}
*/
void Show_Data::on_pushButton_clicked()
{
    this->close();
}
