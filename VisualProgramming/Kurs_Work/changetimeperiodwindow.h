#ifndef CHANGETIMEPERIODWINDOW_H
#define CHANGETIMEPERIODWINDOW_H

#include <QDialog>

namespace Ui {
class changeTimePeriodWindow;
}

class changeTimePeriodWindow : public QDialog
{
    Q_OBJECT

signals:
    void sentData(QString*);

public slots:
    void GetData();

public:
    explicit changeTimePeriodWindow(QVector<QString> Subjects, QString Current="", QWidget *parent=0);
    ~changeTimePeriodWindow();

private:
    Ui::changeTimePeriodWindow *ui;
};

#endif // CHANGETIMEPERIODWINDOW_H
