#include "changetimeperiodwindow.h"
#include "ui_changetimeperiodwindow.h"

changeTimePeriodWindow::changeTimePeriodWindow(QVector<QString> Subjects, QString Current, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changeTimePeriodWindow)
{
    ui->setupUi(this);
    for(int i=0;i<Subjects.size();i++)
    {
        ui->comboBox->addItem(Subjects[i]);
    }
    ui->comboBox->setCurrentText(Current);
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(GetData()));
}

changeTimePeriodWindow::~changeTimePeriodWindow()
{
    delete ui;
}

void changeTimePeriodWindow::GetData()
{
    QString* data = new QString(ui->comboBox->currentText() + "\n" +
                               ui->dateEdit->text() + "\n" +
                               ui->dateEdit_2->text() + "\n" +
                               ui->SpinBox->text() + "\n" +
                               ui->SpinBox_2->text() + "\n" +
                               ui->SpinBox_3->text() + "\n" +
                               ui->SpinBox_4->text() + "\n" +
                               ui->SpinBox_5->text() + "\n" +
                               ui->SpinBox_6->text());
    emit sentData(data);
    emit accept();
}
