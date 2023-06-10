#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myform=new Nikolaev();
    connect(ui->ReadyButton,SIGNAL(clicked()),myform,SLOT(show()));
    connect(this,SIGNAL(sendData(QString)),myform,SLOT(receiveData(QString)));
}


void MainWindow::on_LoadButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(0,"Выберите изображение",QDir::currentPath(),"*.jpg *.jpeg");
    ui->URLEdit->setText(filename);
    QImage image1(filename);
    ui->Photolabel->setPixmap(QPixmap::fromImage(image1));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ReadyButton_clicked()
{
    QString st=ui->URLEdit->text()+"*"+
            ui->NameEdit->text()+"\n"+
            ui->WorkEdit->text()+"\n"+
            ui->DateEdit->text()+"\n"+
            ui->AddressEdit->text()+"\n";
    if(ui->radioMale->isChecked()==true) st+="пол: мужской";
        else st+="пол: женский";
    emit sendData(st);
}
