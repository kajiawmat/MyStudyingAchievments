#ifndef ADDSUBJECTWINDOW_H
#define ADDSUBJECTWINDOW_H

#include <QDialog>

namespace Ui {
class addSubjectWindow;
}

class addSubjectWindow : public QDialog
{
    Q_OBJECT

public slots:
    void GetData();

signals:
    void sentData(QString*);

public:
    explicit addSubjectWindow(QWidget *parent = 0);
    ~addSubjectWindow();

private:
    Ui::addSubjectWindow *ui;
};

#endif // ADDSUBJECTWINDOW_H
