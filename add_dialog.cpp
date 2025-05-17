#include "add_dialog.h"
//#include "ui_add_dialog.h"


Add_Dialog::Add_Dialog(QWidget *parent) :
    QDialog(parent)//,
    //ui(new Ui::Add_Dialog)
{
    //ui->setupUi(this);

    this->setGeometry(0, 0, 400, 280);
    this->show();
    this->setFixedSize(size());
    this->setWindowTitle(" ");

    buttonBox = new QDialogButtonBox;
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setGeometry(10, 240, 361, 32);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

    addDialogMainLayout = new QVBoxLayout(this);

    lineEdit= new QLineEdit();
    lineEdit->setGeometry(200, 20, 191, 31);

    lineEdit_2 = new QLineEdit();
    lineEdit_2->setGeometry(200, 60, 191, 31);

    lineEdit_3 = new QLineEdit();
    lineEdit_3->setGeometry(10, 130, 381, 31);

    lineEdit_4 = new QLineEdit();
    lineEdit_4->setGeometry(10, 190, 381, 31);

    label = new QLabel();
    label->setGeometry(10, 60, 191, 31);
    label->setText("Название фильма:");
    label->setAlignment(Qt::AlignCenter);

    label_2 = new QLabel();
    label_2->setGeometry(10, 20, 191, 31);
    label_2->setText("Второй столбик:");
    label_2->setAlignment(Qt::AlignCenter);

    label_3 = new QLabel();
    label_3->setGeometry(10, 100, 381, 31);
    label_3->setText("Третий Столбик:");
    label_3->setAlignment(Qt::AlignCenter);

    label_4 = new QLabel();
    label_4->setGeometry(10, 100, 381, 31);
    label_4->setText("Комментарий:");
    label_4->setAlignment(Qt::AlignCenter);

    row1 = new QWidget;
    row1Layout = new QHBoxLayout;
    row1Layout->addWidget(label);
    row1Layout->addWidget(lineEdit);
    row1->setLayout(row1Layout);
    addDialogMainLayout->addWidget(row1);

    row2 = new QWidget;
    row2Layout = new QHBoxLayout;
    row2Layout->addWidget(label_2);
    row2Layout->addWidget(lineEdit_2);
    row2->setLayout(row2Layout);
    addDialogMainLayout->addWidget(row2);

    row3 = new QWidget;
    row3Layout = new QHBoxLayout;
    row3Layout->addWidget(label_3);
    row3Layout->addWidget(lineEdit_3);
    row3->setLayout(row3Layout);
    addDialogMainLayout->addWidget(row3);

    row4 = new QWidget;
    row4Layout = new QHBoxLayout;
    row4Layout->addWidget(label_4);
    row4Layout->addWidget(lineEdit_4);
    row4->setLayout(row4Layout);
    addDialogMainLayout->addWidget(row4);

    addDialogMainLayout->addWidget(buttonBox);

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

    //QString edit3 = lineEdit_3->text().simplified().replace(";", ",");
    /*
    if (edit3.size() > 0)
    {
        QStringList temp = edit3.replace(";", ",").split(",");
        int len = temp.size();
        result.setNArguments(len);
        std::copy(temp.begin(), temp.end(), result.begin());          //эта строка должна отвечать за перенос информации из arguments
    }
    */

    result.setType(lineEdit->text().simplified().replace(";", ","));
    result.setName(lineEdit_2->text().simplified().replace(";", ","));
    result.setNArguments(lineEdit_3->text().toInt()/*.simplified().replace(";", ",")*/);      //по идее, данная строка полностью покрывает исполнение закоменченной части
    result.setComment(lineEdit_4->text().simplified().replace(";", ","));
    return result;
}
