#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "square.h"
#include <QApplication>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QApplication *app;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_actionAbout_triggered();

    void on_btnExecute_clicked();

private:
    Ui::MainWindow *ui;
    Square square;
};

#endif // MAINWINDOW_H
