#include "changetimeperiod.h"
#include "ui_changetimeperiod.h"

changeTimePeriod::changeTimePeriod(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changeTimePeriod)
{
    ui->setupUi(this);
}

changeTimePeriod::~changeTimePeriod()
{
    delete ui;
}
