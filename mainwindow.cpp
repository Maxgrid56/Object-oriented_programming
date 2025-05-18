#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QFileInfo"
#include "QFileDialog"
#include "QTextStream"
#include "vector.h"
#include "add_dialog.h"
#include "show_data.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(920, 480);

    this->setWindowTitle("Характеристики фильмов");


    mainFont = new QFont;
    mainFont->setPointSize(12);

    mainWidget = new QWidget(this);
    mainWidgetLayout = new QVBoxLayout;
    mainWidget->setLayout(mainWidgetLayout);

    tableWidget = new QTableWidget;
    tableWidget->setColumnCount(4);
    tableWidget->setFont(*mainFont);
    tableWidget->setContextMenuPolicy(Qt::DefaultContextMenu);
    tableWidget->setFrameShape(QFrame::Box);
    tableWidget->setFrameShadow(QFrame::Raised);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setTextElideMode(Qt::ElideMiddle);
    tableWidget->setHorizontalHeaderLabels(headers);
    tableWidget->setColumnWidth(0, 220);
    tableWidget->setColumnWidth(1, 220);
    tableWidget->setColumnWidth(2, 110);
    tableWidget->setColumnWidth(3, 350);

    connect(tableWidget, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(tableWidget_cellDoubleClicked(int,int)));


    menuBar = new QMenuBar;
    menuBar->setGeometry(0, 0, 920, 31);

    menu = new QMenu;
    menu->setTitle("Файл");

    action_New = new QAction;
    action_Open = new QAction;
    action_Save = new QAction;
    action_SaveAs = new QAction;
    action_Merge = new QAction;
    action_Exit = new QAction;

    action_New->setText("Создать...");
    action_Open->setText("Открыть...");
    action_Save->setText("Сохранить");
    action_SaveAs->setText("Сохранить как...");
    action_Merge->setText("Соеденить...");
    action_Exit->setText("Выход");

    menu->addAction(action_New);
    menu->addAction(action_Open);
    menu->addAction(action_Save);
    menu->addAction(action_SaveAs);
    menu->addAction(action_Merge);
    menu->addAction(action_Exit);

    connect(action_New, SIGNAL(triggered(bool)), this, SLOT(action_New_triggered()));
    connect(action_Open, SIGNAL(triggered(bool)), this, SLOT(action_Open_triggered(bool)));
    connect(action_Save, SIGNAL(triggered(bool)), this, SLOT(action_Save_triggered()));
    connect(action_SaveAs, SIGNAL(triggered(bool)), this, SLOT(action_SaveAs_triggered()));
    connect(action_Merge, SIGNAL(triggered(bool)), this, SLOT(action_Merge_triggered()));
    connect(action_Exit, SIGNAL(triggered(bool)), this, SLOT(action_Exit_triggered()));

    menuBar->addMenu(menu);

    menu_2 = new QMenu;
    menu_2->setTitle("Запись");

    action_Add = new QAction;
    action_Delete = new QAction;
    action_Edit = new QAction;
    action_Clear = new QAction;
    action_ShowData = new QAction;

    action_Add->setText("Добавить...");
    action_Delete->setText("Удалить");
    action_Edit->setText("Редактировать");
    action_Clear->setText("Очистить");
    action_ShowData->setText("Вывести");

    menu_2->addAction(action_Add);
    menu_2->addAction(action_Delete);
    menu_2->addAction(action_Edit);
    menu_2->addAction(action_Clear);
    menu_2->addAction(action_ShowData);

    connect(action_Add, SIGNAL(triggered(bool)), this, SLOT(action_Add_triggered()));
    connect(action_Delete, SIGNAL(triggered(bool)), this, SLOT(action_Delete_triggered()));
    connect(action_Edit, SIGNAL(triggered(bool)), this, SLOT(action_Edit_triggered()));
    connect(action_Clear, SIGNAL(triggered(bool)), this, SLOT(action_Clear_triggered()));
    connect(action_ShowData, SIGNAL(triggered(bool)), this, SLOT(action_ShowData_triggered()));

    menuBar->addMenu(menu_2);

    menu_3 = new QMenu;
    menu_3->setTitle("Помощь");

    action_about = new QAction;

    action_about->setText("О программе");

    menu_3->addAction(action_about);

    connect(action_about, SIGNAL(triggered(bool)), this, SLOT(action_About_triggered()));

    menuBar->addMenu(menu_3);

    mainWidgetLayout->addWidget(menuBar);
    mainWidgetLayout->addWidget(tableWidget);

    this->setCentralWidget(mainWidget);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::action_New_triggered()
{
 if (tableWidget->rowCount() > 0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("Вы уверены, что хотите создать новый файл?\nВсе проделанные изменения не будут сохранены.");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);

        if (msgBox.exec() == QMessageBox::No) {
            return;
        }
    }

    tableWidget->setRowCount(0);

    main_vector.clear();
    file_ = "";
    setWindowTitle("*" + file_ + " – Характеристика фильмов");
}


void MainWindow::action_Exit_triggered()
{
    if (tableWidget->rowCount() > 0 || file_ != "")
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("Вы уверены, что хотите выйти?\nВсе проделанные изменения не будут сохранены.");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        if (msgBox.exec() == QMessageBox::No)
        {
            return;
        }
    }
    exit(0);
}
void MainWindow::action_About_triggered()
{
    QMessageBox::about(this,
    "О программе",
    "Курсовая работа по дисциплине ООП\n"
    "Тема: Создание базы данных на основе кастомного контейнера, характеризующую фильмы\n"
    "Вариант 7\n"
    "Выполнил студент группы ПИБ-31з\n"
    "Гриб Максим Романович\n"
    "Санкт-Петербург\n"
    "2025 год");
}


void MainWindow::action_Add_triggered()
{
    Add_Dialog myDialog;

    if (myDialog.exec() == QDialog::Accepted)
    {
        dataBase t = myDialog.getData();

        tableWidget->setRowCount(tableWidget->rowCount() + 1);
        tableWidget->setItem(tableWidget->rowCount() - 1, 0, new QTableWidgetItem(t.getDirector()));
        tableWidget->setItem(tableWidget->rowCount() - 1, 1, new QTableWidgetItem(t.getMovie()));
        tableWidget->setItem(tableWidget->rowCount() - 1, 2, new QTableWidgetItem(QString::number(t.getYear())));
        tableWidget->setItem(tableWidget->rowCount() - 1, 3, new QTableWidgetItem(t.getComment()));

        main_vector.push_back(t);
        setWindowTitle("*" + file_ + " – Характеристика фильмов");
    }
}


void MainWindow::action_Edit_triggered()
{
    auto list = tableWidget->selectedItems();
    if (list.size() > 0)
    {
        Add_Dialog myDialog;
        myDialog.setDirector(list.at(0)->text());
        myDialog.setMovie(list.at(1)->text());
        myDialog.setYear(list.at(2)->text());
        myDialog.setComment(list.at(3)->text());

        if (myDialog.exec() == QDialog::Accepted)
        {
            dataBase t = myDialog.getData();
            list.at(0)->setText(t.getDirector());
            list.at(1)->setText(t.getMovie());
            list.at(2)->setText(QString::number(t.getYear()));

            list.at(3)->setText(t.getComment());
            main_vector[list.at(0)->row()].setDirector(t.getDirector());
            main_vector[list.at(1)->row()].setMovie(t.getMovie());
            main_vector[list.at(2)->row()].setYear(t.getYear());
            main_vector[list.at(3)->row()].setComment(t.getComment());

            setWindowTitle("*" + file_ + " – Характеристика фильмов");
        }
    }
}


void MainWindow::action_Delete_triggered()
{
    auto list = tableWidget->selectionModel()->selectedRows();

    if (list.size() > 0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("Вы уверены, что хотите удалить строки с выбранными элементами?");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);

        if (msgBox.exec() == QMessageBox::Yes)
        {
            for (auto k = list.rbegin(); k != list.rend(); ++k)
            {
                auto idx = (*k).row();
                main_vector.erase(idx);
                tableWidget->removeRow(idx);
            }
            setWindowTitle("*" + file_ + " – Характеристика фильмов");
        }
    }

}


void MainWindow::action_Clear_triggered()
{
    if (tableWidget->rowCount() > 0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("Вы уверены, что хотите очистить таблицу?");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);

        if (msgBox.exec() == QMessageBox::Yes)
        {
            tableWidget->setRowCount(0);
            main_vector.clear();
            setWindowTitle("*" + file_ + " – Характеристика фильмов");
        }
    }
}


void MainWindow::action_Open_triggered(bool isClean)
{
    QString file_name = QFileDialog::getOpenFileName(this, "Открыть файл...", ".", "CSV files (*.csv);;All files (*.*);;");
    QFileInfo check_file(file_name);
    if (check_file.exists() && check_file.isFile())
    {
        if (isClean)
        {
            MainWindow::action_New_triggered();
        }
        QFile file(file_name);

        if (file.open(QIODevice::ReadOnly))
        {
            QTextStream in(&file);

            tableWidget->clear();
            tableWidget->setRowCount(0);
            tableWidget->setHorizontalHeaderLabels(headers);

            while (!in.atEnd())
            {
                dataBase t;
                QString line = in.readLine();
                QStringList fields = line.split(";");

                if (fields.size() == 4)
                {
                    t.setDirector(fields[0].simplified());
                    t.setMovie(fields[1].simplified());
                    t.setYear(fields[2].toInt());
                    t.setComment(fields[3].simplified());
                    tableWidget->setRowCount(tableWidget->rowCount() + 1);
                    tableWidget->setItem(tableWidget->rowCount() -1, 0, new QTableWidgetItem(t.getDirector()));
                    tableWidget->setItem(tableWidget->rowCount() -1, 1, new QTableWidgetItem(t.getMovie()));
                    tableWidget->setItem(tableWidget->rowCount() -1, 2, new QTableWidgetItem(QString::number(t.getYear())));
                    tableWidget->setItem(tableWidget->rowCount() -1, 3, new QTableWidgetItem(t.getComment()));
                    main_vector.push_back(t);
                }
            }

            file.close();
            file_ = file_name;
            setWindowTitle(file_ + " – Характеристика фильмов");
        }

    }
}


void MainWindow::action_Save_triggered()
{
    if (file_ == "")
    {
        MainWindow::action_SaveAs_triggered();
        return;
    }

    QFile file(file_);

    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);
        int len = tableWidget->rowCount();

        for (int i = 0; i < len; ++i)
        {
            QString type = tableWidget->item(i, 0)->text();
            QString name = tableWidget->item(i, 1)->text();
            QString args = tableWidget->item(i, 2)->text();
            QString comment = tableWidget->item(i, 3)->text();

            out << type << ";" << name << ";" << args << ";" << comment << "\n";
        }

        file.close();
        setWindowTitle(file_ + " – Характеристика фильмов");
    }
}


void MainWindow::action_SaveAs_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Сохранить файл...", ".", "CSV files (*.csv);;All files (*.*);;");

    if (file_name != "")
    {
        file_ = file_name;
        MainWindow::action_Save_triggered();
    }
}


void MainWindow::action_Merge_triggered()
{
    QString old_file = file_;
    MainWindow::action_Open_triggered(false);
    file_ = old_file;

    setWindowTitle("*" + file_ + " – Характеристика фильмов");
}


void MainWindow::tableWidget_cellDoubleClicked(int, int)
{
    MainWindow::action_Edit_triggered();
}


void MainWindow::action_ShowData_triggered()
{
    Show_Data myDialog;
    QString s;
    for (auto &k : main_vector)
    {
        QString arg = QString::number(k.getYear());
        s += k.getDirector() + ";" + k.getMovie() + ";" + arg + ";" +
        k.getComment() + "\n";
    }

    myDialog.setText(s);
    myDialog.exec();
}
