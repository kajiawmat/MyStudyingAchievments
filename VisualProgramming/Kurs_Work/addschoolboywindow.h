#ifndef ADDSCHOOLBOYWINDOW_H
#define ADDSCHOOLBOYWINDOW_H

#include <QDialog>

namespace Ui {
class addSchoolBoyWindow;
}

class addSchoolBoyWindow : public QDialog
{
    Q_OBJECT

public:
    explicit addSchoolBoyWindow(QWidget *parent = 0);
    ~addSchoolBoyWindow();

public slots:
    void GetData();

signals:
    void sentData(QString*);

private:
    Ui::addSchoolBoyWindow *ui;
};

#endif // ADDSCHOOLBOYWINDOW_H
