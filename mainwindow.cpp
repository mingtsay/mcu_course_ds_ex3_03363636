#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->setModel(&square);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    app->quit();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, "About", "This application is written by Ming Tsay with Qt Creator under macOS, and has been compiled with MXE for Windows platforms.");
}

void MainWindow::on_btnExecute_clicked()
{
    bool isSizeOk = false;
    int size = ui->txtSize->text().toInt(&isSizeOk);
    if (!isSizeOk || size < 3) return;
    square.resize(size);
    ui->tableView->model()->dataChanged(QModelIndex(), QModelIndex());
}
