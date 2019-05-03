#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "data_base.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_folder_pushButton_clicked();

    void on_query_pushButton_clicked();

    void on_save_pushButton_clicked();

    void on_actionclear_triggered();

    void on_load_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    data_base* data;
    QString request;
};

#endif // MAINWINDOW_H
