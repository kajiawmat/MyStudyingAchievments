#include "auth.h"
#include "ui_auth.h"

Auth::Auth(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Auth)
{
    ui->setupUi(this);
}

Auth::~Auth()
{
    delete ui;
}
