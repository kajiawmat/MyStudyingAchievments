#ifndef DELSCHOOLBOYWINDOW_H
#define DELSCHOOLBOYWINDOW_H

#include <QDialog>

namespace Ui {
class delSchoolBoyWindow;
}

class delSchoolBoyWindow : public QDialog
{
    Q_OBJECT

public:
    explicit delSchoolBoyWindow(QWidget *parent = 0);
    ~delSchoolBoyWindow();

private:
    Ui::delSchoolBoyWindow *ui;
};

#endif // DELSCHOOLBOYWINDOW_H
