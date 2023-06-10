#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "nikolaev.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Nikolaev *myform;

signals:
    void sendData(QString str);

private slots:
    void on_LoadButton_clicked();
    void on_ReadyButton_clicked();
};

#endif // MAINWINDOW_H
