#include "structjournalwindow.h"
#include "ui_structjournalwindow.h"
#include <QHelpEvent>
#include "helpwindow.h"

structJournalWindow::structJournalWindow(QString Name, QString Teacher, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::structJournalWindow)
{
    ui->setupUi(this);
    mapDate=new QSignalMapper(this);
    ui->classEdit->setText(Name);
    ui->nameEdit->setText(Teacher);
    dateList[1]=ui->dateEdit;
    dateList[2]=ui->dateEdit_2;
    dateList[3]=ui->dateEdit_3;
    dateList[4]=ui->dateEdit_4;
    dateList[5]=ui->dateEdit_5;
    dateList[6]=ui->dateEdit_6;
    dateList[7]=ui->dateEdit_7;
    dateList[8]=ui->dateEdit_8;
    for(int i=1;i<=8;i++)
    {
        connect(dateList[i],SIGNAL(dateChanged(QDate)),mapDate,SLOT(map()));
        mapDate->setMapping(dateList[i],i);
    }
    connect(mapDate,SIGNAL(mapped(int)),this,SLOT(CheckNewDate(int)));
    connect(ui->buttonBox, SIGNAL(accepted()),this,SLOT(GetData()));
}


structJournalWindow::~structJournalWindow()
{
    for(int i=1;i<=8;i++) delete dateList[i];
    delete mapDate;
    delete ui;
}

void structJournalWindow::CheckNewDate(int ind)
{
    QDate NewDate=dateList[ind]->date();
    for(int i=1;i<ind;i++)
    {
        if(NewDate<=dateList[i]->date()) dateList[i]->setDate(NewDate.addDays(i-ind));
    }
    for(int i=ind+1;i<=8;i++)
    {
        if(NewDate>=dateList[i]->date()) dateList[i]->setDate(NewDate.addDays(i-ind));
    }
}

void structJournalWindow::GetData()
{
    if(ui->classEdit->text()=="")
    {
        ui->errorLabel->setText("Введите название класса");
        return;
    }
    if(ui->nameEdit->text()=="")
    {
        ui->errorLabel->setText("Введите имя учителя");
        return;
    }
    QString* data=new QString(ui->classEdit->text() + "\n" + ui->nameEdit->text());
    for(int i=1;i<=8;i++) *data+=QString("\n" + dateList[i]->text());
    emit sentData(data);
    close();
}

