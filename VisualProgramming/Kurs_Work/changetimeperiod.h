#ifndef CHANGETIMEPERIOD_H
#define CHANGETIMEPERIOD_H

#include <QDialog>

namespace Ui {
class changeTimePeriod;
}

class changeTimePeriod : public QDialog
{
    Q_OBJECT

public:
    explicit changeTimePeriod(QWidget *parent = 0);
    ~changeTimePeriod();

private:
    Ui::changeTimePeriod *ui;
};

#endif // CHANGETIMEPERIOD_H
