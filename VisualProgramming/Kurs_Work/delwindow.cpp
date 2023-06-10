#include "delwindow.h"
#include "ui_delwindow.h"

delWindow::delWindow(int sw, QVector<QString> *list,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delWindow)
{
    ui->setupUi(this);
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(GetData()));
    if(sw)
    {
        ui->labelList->setText("Список учеников");
        this->setWindowTitle("Удаление учеников");
    }
    else
    {
        ui->labelList->setText("Список предметов");
        this->setWindowTitle("Удаление предметов");
    }
    for(long long i=0;i<list->size();i++)
    {
        QListWidgetItem *it=new QListWidgetItem;
        it->setText(list->value(i));
        it->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
        it->setCheckState(Qt::Unchecked);
        ui->listWidget->addItem(it);
    }
    setLayout(ui->verticalLayout);
}

delWindow::~delWindow()
{
    delete ui;
}

void delWindow::GetData()
{
    QVector<int> delList;
    for(int i=0;i<ui->listWidget->count();i++)
    {
        if(ui->listWidget->item(i)->checkState()==Qt::Checked) {qDebug("Ok");delList.push_back(i);}
    }
    emit sentData(delList);
    close();
}
