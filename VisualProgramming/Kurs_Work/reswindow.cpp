#include "reswindow.h"
#include "ui_reswindow.h"

resWindow::resWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::resWindow)
{
    ui->setupUi(this);
}

resWindow::~resWindow()
{
    delete ui;
}
