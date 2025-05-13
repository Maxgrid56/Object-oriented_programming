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
    QStringList headers ={"Название", "Год выхода", "Режиссёр", "Комментарий"};     //все строки с названиями столбцов

    QLineEdit* lineEdit;

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
    /*
    void setText(const QString &str);           //функции и слоты из show_data
    QString getText();

    dataBase getData();                         //функции и слоты из add_dialog
    void setType(QString arg);
    void setName(QString arg);
    void setArgs(QString arg);
    void setComment(QString arg);
    */
private slots:
    void on_action_New_triggered();
    void on_action_About_triggered();
    void on_action_Exit_triggered();
    void on_action_Add_triggered();
    void on_lineEdit_textChanged(const QString &arg1);
    void on_action_Edit_triggered();
    void on_action_Delete_triggered();
    void on_action_Clear_triggered();
    void on_action_Open_triggered(bool isClean = true);
    void on_action_Save_triggered();
    void on_action_SaveAs_triggered();
    void on_action_Merge_triggered();
    void on_tableWidget_cellDoubleClicked(int, int);
    void on_action_ShowData_triggered();

    /*
    void on_pushButton_clicked();
    */
    /*
    QWidget* mainWidget;
    QWidget* mainWidgetTop;                            //виджеты проекта

    QVBoxLayout* mainWidgetLayout;
    QHBoxLayout* mainWidgetLayoutTop;                  //лейауты проекта

    QPushButton* fileButton;
    QPushButton* addButton;
    QPushButton* helpButton;
    */

};
#endif // MAINWINDOW_H
