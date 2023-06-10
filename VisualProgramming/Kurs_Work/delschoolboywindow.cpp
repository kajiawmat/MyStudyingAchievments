#include "delschoolboywindow.h"
#include "ui_delschoolboywindow.h"

delSchoolBoyWindow::delSchoolBoyWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delSchoolBoyWindow)
{
    ui->setupUi(this);
}

delSchoolBoyWindow::~delSchoolBoyWindow()
{
    delete ui;
}
