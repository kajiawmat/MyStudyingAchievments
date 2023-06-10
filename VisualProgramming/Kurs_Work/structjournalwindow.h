#ifndef STRUCTJOURNALWINDOW_H
#define STRUCTJOURNALWINDOW_H

#include <QDialog>
#include <QDateEdit>
#include <QSignalMapper>
#include <QHelpEvent>

namespace Ui {
class structJournalWindow;
}

class structJournalWindow : public QDialog
{
    Q_OBJECT

signals:
    void sentData(QString*);

public slots:
    void CheckNewDate(int ind);
    void GetData();

public:
    explicit structJournalWindow(QString Name="", QString Teacher="", QWidget *parent = 0);
    ~structJournalWindow();

private:
    Ui::structJournalWindow *ui;
    QDateEdit* dateList[9];
    QSignalMapper* mapDate;
};

#endif // STRUCTJOURNALWINDOW_H
