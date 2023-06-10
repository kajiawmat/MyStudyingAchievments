#include "nikolaev.h"
#include "ui_nikolaev.h"
#include <QtWidgets>



Nikolaev::Nikolaev(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Nikolaev)
{
    ui->setupUi(this);
}

Nikolaev::~Nikolaev()
{
    delete ui;
}

void Nikolaev::receiveData(QString str)
{
    QStringList lst = str.split("*");
    ui->textEdit->setText(lst.at(1)+"\n"+lst.at(0));
    if(lst.size()>1)
    {
        QImage image1(lst.at(0));
        ui->label->setPixmap(QPixmap::fromImage(image1));
    }
}

void Nikolaev::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button->text()=="Reset")
    {
        ui->textEdit->clear();
        ui->label->clear();
    }
    else if(button->text()=="Save")
    {
        QString filename = QFileDialog::getSaveFileName(0, "Сохранить файл", QDir::currentPath());
        QTextDocumentWriter writer;
        writer.setFileName(filename);
        writer.write(ui->textEdit->document());
    }
    else if(button->text()=="Open")
    {
        QString filename = QFileDialog::getOpenFileName(0, "Открыть файл", QDir::currentPath());
        QFile file(filename);
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            ui->textEdit->setPlainText(file.readAll());
            QStringList inf = ui->textEdit->toPlainText().split("\n");
            QImage image2(inf.at(5));
            ui->label->setPixmap(QPixmap::fromImage(image2));
        }
    }
}
