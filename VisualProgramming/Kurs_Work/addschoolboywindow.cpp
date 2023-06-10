#include "addschoolboywindow.h"
#include "ui_addschoolboywindow.h"

addSchoolBoyWindow::addSchoolBoyWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addSchoolBoyWindow)
{
    ui->setupUi(this);
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(GetData()));
}

addSchoolBoyWindow::~addSchoolBoyWindow()
{
    delete ui;
}

void addSchoolBoyWindow::GetData()
{
    if(ui->schoolBoyName->text()=="")
    {
        ui->errorLabel->setText("Введите имя ученика");
        return;
    }
    QString* data=new QString(ui->schoolBoyName->text() + "\n" +
                             ui->schoolBoyBirthDate->date().toString("dd.MM.yyyy") + "\n" +
                             ui->schoolBoyAddress->text() + "\n" +
                             ui->schoolBoyPhone->text() + "\n" +
                             ui->motherName->text() + "\n" +
                             ui->motherPhone->text() + "\n" +
                             ui->fatherName->text() + "\n" +
                             ui->fatherPhone->text());
    emit sentData(data);
    emit accept();
}
