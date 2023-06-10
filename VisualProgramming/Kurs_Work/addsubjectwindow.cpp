#include "addsubjectwindow.h"
#include "ui_addsubjectwindow.h"

addSubjectWindow::addSubjectWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addSubjectWindow)
{
    ui->setupUi(this);
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(GetData()));
}

addSubjectWindow::~addSubjectWindow()
{
    delete ui;
}

void addSubjectWindow::GetData()
{
    if(ui->subjectName->text()=="")
    {
        ui->errorLabel->setText("Введите название предмета");
        return;
    }
    QString* data = new QString(ui->subjectName->text() + "\n" +
                               ui->spinBox->text() + "\n" +
                               ui->spinBox_2->text() + "\n" +
                               ui->spinBox_3->text() + "\n" +
                               ui->spinBox_4->text() + "\n" +
                               ui->spinBox_5->text() + "\n" +
                               ui->spinBox_6->text());
    emit sentData(data);
    emit accept();
}
