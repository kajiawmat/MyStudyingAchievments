#include "schoolboyswindow.h"
#include "ui_schoolboyswindow.h"
#include<QMessageBox>
#include<QIcon>

schoolBoysWindow::schoolBoysWindow(QTableView *Schoolers, QSqlTableModel *model,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::schoolBoysWindow)
{
    ui->setupUi(this);
    this->setLayout(ui->verticalLayout);
    ui->tableView=Schoolers;
    ui->tableView->setParent(this);
    ui->verticalLayout->addWidget(ui->tableView);
    ui->verticalLayout->addWidget(ui->buttonBox);
    Model=model;
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(SaveChanges()));
    Model->setHeaderData(0,Qt::Horizontal,"Имя ученика");
    Model->setHeaderData(1,Qt::Horizontal,"Дата рождения");
    Model->setHeaderData(2,Qt::Horizontal,"Адрес проживания");
    Model->setHeaderData(3,Qt::Horizontal,"Телефон ученика");
    Model->setHeaderData(4,Qt::Horizontal,"Имя матери");
    Model->setHeaderData(5,Qt::Horizontal,"Телефон матери");
    Model->setHeaderData(6,Qt::Horizontal,"Имя отца");
    Model->setHeaderData(7,Qt::Horizontal,"Телефон отца");
}

schoolBoysWindow::~schoolBoysWindow()
{
    delete ui;
}

void schoolBoysWindow::SaveChanges()
{
    int n=QMessageBox::question(this,"Сохранение","Вы уверены, что хотите сохранить изменения?",QMessageBox::Yes | QMessageBox::No);
    if(n==QMessageBox::Yes)
    {
        Model->submitAll();
    }
    else
    {
        Model->revertAll();
    }
}
