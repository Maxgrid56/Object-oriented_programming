#include "add_dialog.h"
#include "ui_add_dialog.h"


Add_Dialog::Add_Dialog(QWidget *parent) :
    QDialog(parent)//,
    //ui(new Ui::Add_Dialog)
{
    //ui->setupUi(this);

    this->setGeometry(0, 0, 400, 280);
    this->show();
    this->setFixedSize(size());
    this->setWindowTitle(" ");

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setGeometry(10, 240, 361, 32);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

    lineEdit= new QLineEdit(this);
    lineEdit->setGeometry(200, 20, 191, 31);

    lineEdit_2 = new QLineEdit(this);
    lineEdit_2->setGeometry(200, 60, 191, 31);

    lineEdit_3 = new QLineEdit(this);
    lineEdit_3->setGeometry(10, 130, 381, 31);

    lineEdit_4 = new QLineEdit(this);
    lineEdit_4->setGeometry(10, 190, 381, 31);

    label = new QLabel(this);
    label->setGeometry(10, 60, 191, 31);
    label->setText("Название фильма:");
    label->setAlignment(Qt::AlignCenter);

    label_2 = new QLabel(this);
    label_2->setGeometry(10, 20, 191, 31);
    label_2->setText("Второй столбик:");
    label_2->setAlignment(Qt::AlignCenter);

    label_3 = new QLabel(this);
    label_3->setGeometry(10, 100, 381, 31);
    label_3->setText("Третий Столбик:");
    label_3->setAlignment(Qt::AlignCenter);

    label_4 = new QLabel(this);
    label_4->setGeometry(10, 100, 381, 31);
    label_4->setText("Комментарий:");
    label_4->setAlignment(Qt::AlignCenter);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

/*
Add_Dialog::~Add_Dialog()
{
    delete ui;
}
*/

void Add_Dialog::setType(QString arg)
{
    lineEdit->setText(arg);
}


void Add_Dialog::setName(QString arg)
{
    lineEdit_2->setText(arg);
}


void Add_Dialog::setArgs(QString arg)
{
    lineEdit_3->setText(arg);
}


void Add_Dialog::setComment(QString arg)
{
    lineEdit_4->setText(arg);
}


dataBase Add_Dialog::getData()
{
    dataBase result;
    QString edit3 = lineEdit_3->text().simplified().replace(";", ",");

    if (edit3.size() > 0)
    {
        QStringList temp = edit3.replace(";", ",").split(",");
        int len = temp.size();
        result.setNArguments(len);
        std::copy(temp.begin(), temp.end(), result.begin());
    }

    result.setType(lineEdit->text().simplified().replace(";", ","));
    result.setName(lineEdit_2->text().simplified().replace(";", ","));
    result.setComment(lineEdit_4->text().simplified().replace(";",
                                                                  ","));
    return result;
}
