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

    //this->resize(920, 480);
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

    connect(tableWidget, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(on_tableWidget_cellDoubleClicked(int,int)));

    lineEdit = new QLineEdit;
    lineEdit->setPlaceholderText("Поиск");

    connect(lineEdit, SIGNAL(textChanged(QString)), this, SLOT(on_lineEdit_textChanged(QString)));

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

    //action_New->setShortcut("Ctrl+N");
    //action_Open->setShortcut("Ctrl+O");
    //action_Save->setShortcut("Ctrl+S");
    //action_SaveAs->setShortcut("Ctrl+Alt+S");

    menu->addAction(action_New);
    menu->addAction(action_Open);
    menu->addAction(action_Save);
    menu->addAction(action_SaveAs);
    menu->addAction(action_Merge);
    menu->addAction(action_Exit);

    connect(action_New, SIGNAL(triggered(bool)), this, SLOT(on_action_New_triggered()));
    connect(action_Open, SIGNAL(triggered(bool)), this, SLOT(on_action_Open_triggered(bool)));
    connect(action_Save, SIGNAL(triggered(bool)), this, SLOT(on_action_Save_triggered()));
    connect(action_SaveAs, SIGNAL(triggered(bool)), this, SLOT(on_action_SaveAs_triggered()));
    connect(action_Merge, SIGNAL(triggered(bool)), this, SLOT(on_action_Merge_triggered()));
    connect(action_Exit, SIGNAL(triggered(bool)), this, SLOT(on_action_Exit_triggered()));

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

    //action_Add->setShortcut("Ctrl+A");
    //action_Delete->setShortcut("Ctrl+D");
    //action_Clear->setShortcut("Ctrl+P");

    menu_2->addAction(action_Add);
    menu_2->addAction(action_Delete);
    menu_2->addAction(action_Edit);
    menu_2->addAction(action_Clear);
    menu_2->addAction(action_ShowData);

    connect(action_Add, SIGNAL(triggered(bool)), this, SLOT(on_action_Add_triggered()));
    connect(action_Delete, SIGNAL(triggered(bool)), this, SLOT(on_action_Delete_triggered()));
    connect(action_Edit, SIGNAL(triggered(bool)), this, SLOT(on_action_Edit_triggered()));
    connect(action_Clear, SIGNAL(triggered(bool)), this, SLOT(on_action_Clear_triggered()));
    connect(action_ShowData, SIGNAL(triggered(bool)), this, SLOT(on_action_ShowData_triggered()));

    menuBar->addMenu(menu_2);

    menu_3 = new QMenu;
    menu_3->setTitle("Помощь");

    action_about = new QAction;

    action_about->setText("О программе");

    menu_3->addAction(action_about);

    connect(action_about, SIGNAL(triggered(bool)), this, SLOT(on_action_About_triggered()));

    menuBar->addMenu(menu_3);

    mainWidgetLayout->addWidget(menuBar);
    mainWidgetLayout->addWidget(lineEdit);
    mainWidgetLayout->addWidget(tableWidget);

    this->setCentralWidget(mainWidget);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_New_triggered()
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


void MainWindow::on_action_Exit_triggered()
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
void MainWindow::on_action_About_triggered()
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


void MainWindow::on_action_Add_triggered()
{
    Add_Dialog myDialog;

    if (myDialog.exec() == QDialog::Accepted)
    {
        dataBase t = myDialog.getData();
        //auto len = t.getNArguments();

        tableWidget->setRowCount(tableWidget->rowCount() + 1);
        tableWidget->setItem(tableWidget->rowCount() - 1, 0, new QTableWidgetItem(t.getDirector()));
        //tableWidget->item(tableWidget->rowCount() - 1, 0)->setTextColor(typeColor);
        tableWidget->setItem(tableWidget->rowCount() - 1, 1, new QTableWidgetItem(t.getMovie()));
        tableWidget->setItem(tableWidget->rowCount() - 1, 2, new QTableWidgetItem(/*QString::number(len)*/ QString::number(t.getYear())));
        /*
        QString arg = "";

        if (len > 0)
        {
            arg = t[0];
            for (int i = 1; i < len; ++i)
            {
                arg += ", " + t[i];
            }
        }
        */
        //tableWidget->setItem(tableWidget->rowCount() - 1, 3, new QTableWidgetItem(arg));
        tableWidget->setItem(tableWidget->rowCount() - 1, 3, new QTableWidgetItem(t.getComment()));         //изменил позицию с 1,4 на 1,3
        //tableWidget->item(tableWidget->rowCount() - 1, 4)->setTextColor(commentColor);
        main_vector.push_back(t);
        //statusBar->showMessage("Запись добавлена");
        setWindowTitle("*" + file_ + " – Характеристика фильмов");
    }
}


void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    tableWidget->setCurrentCell(-1, -1);

    if (arg1 == "")
    {
        return;
    }

    tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::MultiSelection);
    auto find_items = tableWidget->findItems(arg1, Qt::MatchContains);
    int len = find_items.size();

    for (int i = 0; i < len; ++i)
    {
        auto item = find_items.at(i);
        //tableWidget->setItemSelect(item, true);
    }
    tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    //statusBar->showMessage("Найдено " + QString::number(len) + "ячеек");
}


void MainWindow::on_action_Edit_triggered()
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
            //auto len = t.getNArguments();
            //QString arg = "";
            /*
            if (len > 0)
            {
                arg = t[0];

                for (int i = 1; i < len; ++i)
                {
                    arg += ", " + t[i];
                }
            }
            */
            //list.at(3)->setText(arg);
            list.at(3)->setText(t.getComment());
            main_vector[list.at(0)->row()].setDirector(t.getDirector());
            main_vector[list.at(1)->row()].setMovie(t.getMovie());
            main_vector[list.at(2)->row()].setYear(t.getYear());
            //int k = list.at(3)->row();
            //std::copy(t.begin(), t.end(), main_vector[k].begin());
            main_vector[list.at(3)->row()].setComment(t.getComment());
            //statusBar->showMessage("Запись отредактирована");
            setWindowTitle("*" + file_ + " – Характеристика фильмов");
        }
    }
}


void MainWindow::on_action_Delete_triggered()
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
            //statusBar->showMessage("Запись удалена");
            setWindowTitle("*" + file_ + " – Характеристика фильмов");
        }
    }
    else ;//statusBar->showMessage("Таблица пуста");
}


void MainWindow::on_action_Clear_triggered()
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
            //statusBar->showMessage("Таблица очищена");
            setWindowTitle("*" + file_ + " – Характеристика фильмов");
        }
    }
    else ;//statusBar->showMessage("Таблица пуста");
}


void MainWindow::on_action_Open_triggered(bool isClean)             //нужно разобраться с тем, чтобы таблица очищалась и убирала лишние строки перед открытием нового файла
{
    QString file_name = QFileDialog::getOpenFileName(this, "Открыть файл...", ".", "CSV files (*.csv);;All files (*.*);;");
    QFileInfo check_file(file_name);
    if (check_file.exists() && check_file.isFile())
    {
        if (isClean)
        {
            MainWindow::on_action_New_triggered();
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
                    //QString s_args = "";
                    //QStringList args = fields[2].split(",");
                    //auto len = args.size();
                    //t.setNArguments(len);
                    /*
                    if (len > 0)
                    {
                        t[0] = args[0].simplified();
                        s_args = t[0];
                        for (int i = 1; i < len; ++i)
                        {
                            t[i] = args[i].simplified();
                            s_args += ", " + t[i];
                        }
                    }
                    */
                    t.setYear(fields[2].toInt());
                    t.setComment(fields[3].simplified());
                    tableWidget->setRowCount(tableWidget->rowCount() + 1);
                    tableWidget->setItem(tableWidget->rowCount() -1, 0, new QTableWidgetItem(t.getDirector()));
                    //tableWidget->item(tableWidget->rowCount() - 1,0)->setTextColor(typeColor);
                    tableWidget->setItem(tableWidget->rowCount() -1, 1, new QTableWidgetItem(t.getMovie()));
                    tableWidget->setItem(tableWidget->rowCount() -1, 2, new QTableWidgetItem(QString::number(t.getYear())));
                    //tableWidget->setItem(tableWidget->rowCount() -1, 3, new QTableWidgetItem(s_args));
                    tableWidget->setItem(tableWidget->rowCount() -1, 3, new QTableWidgetItem(t.getComment()));
                    //tableWidget->item(tableWidget->rowCount() - 1,4)->setTextColor(commentColor);
                    main_vector.push_back(t);
                }
            }

            file.close();
            //statusBar->showMessage("Записи из файла добавлены");
            file_ = file_name;
            setWindowTitle(file_ + " – Характеристика фильмов");
        }
        else ;//statusBar->showMessage("Файл '" + file_name + "' не удалось открыть на чтение (" + file.errorString() + ")");
    }
    else ;//statusBar->showMessage("Файл '" + file_name + "' не существует");
}


void MainWindow::on_action_Save_triggered()
{
    if (file_ == "")
    {
        MainWindow::on_action_SaveAs_triggered();
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
        //statusBar->showMessage("Файл записан");
        setWindowTitle(file_ + " – Характеристика фильмов");
    }
}


void MainWindow::on_action_SaveAs_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Сохранить файл...", ".", "CSV files (*.csv);;All files (*.*);;");

    if (file_name != "")
    {
        file_ = file_name;
        MainWindow::on_action_Save_triggered();
    }
}


void MainWindow::on_action_Merge_triggered()
{
    QString old_file = file_;
    MainWindow::on_action_Open_triggered(false);
    file_ = old_file;
    //statusBar->showMessage("Данные объединены");
    setWindowTitle("*" + file_ + " – Характеристика фильмов");
}


void MainWindow::on_tableWidget_cellDoubleClicked(int, int)
{
    MainWindow::on_action_Edit_triggered();
}


void MainWindow::on_action_ShowData_triggered()
{
    Show_Data myDialog;
    QString s;
    for (auto &k : main_vector)
    {
        QString arg = QString::number(k.getYear());
        //int len = k.getNArguments();
        /*
        if (len > 0)
        {
            arg = k[0];
            for (int i = 1; i < len; ++i)
            {
                arg += ", " + k[i];
            }
        }
        */
        s += k.getDirector() + ";" + k.getMovie() + ";" + arg + ";" +
        k.getComment() + "\n";
    }

    myDialog.setText(s);
    myDialog.exec();
}


/*
//функции и слоты из show_data
void MainWindow::setText(const QString &str)
{
    textEdit->setText(str);
}

QString MainWindow::getText()
{
    return textEdit->toPlainText();
}

void MainWindow::on_pushButton_clicked()
{
    this->close();              //замени this на виджет, котрый будет вызываться
}



//функции и слоты из add_dialog
void MainWindow::setType(QString arg)
{
    lineEdit->setText(arg);
}


void MainWindow::setName(QString arg)
{
    lineEdit_2->setText(arg);
}


void MainWindow::setArgs(QString arg)
{
    lineEdit_3->setText(arg);
}


void MainWindow::setComment(QString arg)
{
    lineEdit_4->setText(arg);
}


dataBase MainWindow::getData()
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
*/
