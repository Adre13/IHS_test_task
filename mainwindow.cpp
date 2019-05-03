#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    data = new data_base();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_folder_pushButton_clicked()
{
    QString folder_path = QFileDialog::getExistingDirectory(nullptr, "Select a Directory", QDir::homePath());
    data->read_folder(folder_path);
}

void MainWindow::on_query_pushButton_clicked()
{
    request = ui->query_lineEdit->text();
    if(!request.isEmpty())
    {
        ui->textEdit->append(data->get_data(request));
    }
}

void MainWindow::on_save_pushButton_clicked()
{
    QString initial_path = QDir::currentPath() + "/untitled.txt";
    QString file_name = QFileDialog::getSaveFileName(this, tr("Save As"), initial_path);
    if(data->save_to_file(file_name))
    {
        QMessageBox::information(this, "Information", "All data saved to - " + file_name);
    }else
    {
        QMessageBox::warning(this, "warning", "Something wrong! I could not save data!");
    }
}

void MainWindow::on_actionclear_triggered()
{
    ui->textEdit->clear();
}

void MainWindow::on_load_pushButton_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open file"), QDir::currentPath());
    if(data->load_from_file(file))
    {
        QMessageBox::information(this, "Information", "All data loaded from - " + file);
    }else
    {
        QMessageBox::warning(this, "warning", "Something wrong! I could not load data!");
    }
}
