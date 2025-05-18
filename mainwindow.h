#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QDialog>
#include "database.h"
#include "vector.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  //QTableWidget* tableWidget;

private:
    Ui::MainWindow *ui;

    QString file_ = "";
    QColor typeColor = QColor(0, 0, 127);
    QColor commentColor = QColor(0, 85, 0);
    Vector<dataBase> main_vector;


    QFont* mainFont;                            //основной шрифт

    QWidget* mainWidget;                        //структурные виджеты

    QVBoxLayout* mainWidgetLayout;              //лейауты


    QTableWidget* tableWidget;
    QStringList headers ={"Название", "Режиссёр", "Год выхода", "Комментарий"};     //все строки с названиями столбцов

    //QLineEdit* lineEdit;

    QMenuBar* menuBar;                          //строка с меню

    QMenu* menu;                                //меню "файл"
    QMenu* menu_2;                              //меню "запись"
    QMenu* menu_3;                              //меню "запись"

    QAction* action_New;                        //акшены menu
    QAction* action_Open;
    QAction* action_Save;
    QAction* action_SaveAs;
    QAction* action_Merge;
    QAction* action_Exit;

    QAction* action_Add;                        //акшены menu_2
    QAction* action_Delete;
    QAction* action_Edit;
    QAction* action_Clear;
    QAction* action_ShowData;

    QAction* action_about;                      //акшены menu_3

private slots:
    void action_New_triggered();
    void action_About_triggered();
    void action_Exit_triggered();
    void action_Add_triggered();
    //void on_lineEdit_textChanged(const QString &arg1);
    void action_Edit_triggered();
    void action_Delete_triggered();
    void action_Clear_triggered();
    void action_Open_triggered(bool isClean = true);
    void action_Save_triggered();
    void action_SaveAs_triggered();
    void action_Merge_triggered();
    void tableWidget_cellDoubleClicked(int, int);
    void action_ShowData_triggered();


};
#endif // MAINWINDOW_H
