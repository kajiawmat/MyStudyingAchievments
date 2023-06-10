#include "delsubjectwindow.h"
#include "ui_delsubjectwindow.h"

delSubjectWindow::delSubjectWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delSubjectWindow)
{
    ui->setupUi(this);
}

delSubjectWindow::~delSubjectWindow()
{
    delete ui;
}
