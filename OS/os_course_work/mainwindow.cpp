#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    socket1 = new QTcpSocket();
    connect(socket1,SIGNAL(connected()),this,SLOT(connected()));
    connect(socket1,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(socket1,SIGNAL(readyRead()),this,SLOT(sockReady()));

    ui->pushButtonConnect->setEnabled(true);
    ui->disconnectButton->setEnabled(false);
    ui->sendButton->setEnabled(false);

    model1.setStringList(list1);
    ui->listView->setModel(&model1);

    ui->lineEditSend->setPlaceholderText("Введите сообщение..");
    ui->nameLineEdit->setPlaceholderText("Введите имя..");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonConnect_clicked()
{
    name1 = ui->nameLineEdit->text();
    if(name1 == nullptr){
        QMessageBox::critical(this,"Error", "Please enter a valid name!");
        return;
    }

    socket1->connectToHost("127.0.0.1",5353);//соединяемся с хостом
    ui->pushButtonConnect->setEnabled(false);
    ui->disconnectButton->setEnabled(false);
    ui->sendButton->setEnabled(false);

    if(!socket1->waitForConnected(500)){
        on_disconnectButton_clicked();
        QMessageBox::critical(this,"Error", "Server connection problems!");
        return;
    }
    ui->nameLineEdit->clear();
}

void MainWindow::on_disconnectButton_clicked()
{
    socket1->deleteLater();

    ui->pushButtonConnect->setEnabled(true);
    ui->disconnectButton->setEnabled(false);
    ui->sendButton->setEnabled(false);

}

void MainWindow::on_sendButton_clicked()
{
    QByteArray data;
    data.append(name1);
    data.append(QString(": "));
    data.append((ui->lineEditSend->text()));

    ui->lineEditSend->setText(QString());
    socket1->write(data);
}

void MainWindow::connected(){
    ui->pushButtonConnect->setEnabled(false);
    ui->disconnectButton->setEnabled(true);
    ui->sendButton->setEnabled(true);
}

void MainWindow::disconnected(){
    ui->pushButtonConnect->setEnabled(true);
    ui->disconnectButton->setEnabled(false);
    ui->sendButton->setEnabled(false);
}

void MainWindow::sockReady(){
  QByteArray data = socket1->readAll();
  QString message(data);
  list1.append(message);

  model1.setStringList(list1);
  ui->listView->scrollToTop();
}

void MainWindow::on_lineEditSend_returnPressed()
{
    on_sendButton_clicked();
}
