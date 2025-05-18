#include "show_data.h"


Show_Data::Show_Data(QWidget *parent) :
    QDialog(parent)
{
    this->setGeometry(0, 0, 570, 480);
    this->show();
    this->setWindowTitle("CSV-отображение");

    showDataMainLayout = new QVBoxLayout;
    textEdit = new QTextEdit;
    pushButton = new QPushButton;
    pushButton->setText("OK");
    showDataMainLayout->addWidget(textEdit);
    showDataMainLayout->addWidget(pushButton);

    connect(pushButton, SIGNAL(clicked(bool)), this, SLOT(pushButton_clicked()));

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

void Show_Data::pushButton_clicked()
{
    this->close();
}
