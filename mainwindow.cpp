#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
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

    if (!isSizeOk)
    {
        QMessageBox::warning(this, "Invalid Input", "The size of square should be an integer, but the input is: \"" + ui->txtSize->text() + "\"");
        return;
    }

    if (size < 3)
    {
        QMessageBox::warning(this, "Invalid Input", "The size of square should be >= 3, but the input is: " + ui->txtSize->text());
        return;
    }

    Square::Direction direction = Square::Direction::Default;
    if (ui->radioTopLeft->isChecked()) direction = Square::Direction::TopLeft;
    if (ui->radioTopRight->isChecked()) direction = Square::Direction::TopRight;
    if (ui->radioBottomLeft->isChecked()) direction = Square::Direction::BottomLeft;
    if (ui->radioBottomRight->isChecked()) direction = Square::Direction::BottomRight;

    square.resize(size, direction);
}
