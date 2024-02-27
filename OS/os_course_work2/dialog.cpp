#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

//запуск сервера
void Dialog::on_start_clicked()
{
    server.setMessage("Welcome to chat! \r\n");
    if(!server.listen(QHostAddress::Any,5353)){
        QMessageBox::critical(this,"Error", server.errorString());
        return;
    }
}
void Dialog::on_stop_clicked()
{
    server.close();
    enableButton();
}

void Dialog::enableButton(){
    ui->start->setEnabled(!server.isListening());
    ui->stop->setEnabled(!server.isListening());
}
