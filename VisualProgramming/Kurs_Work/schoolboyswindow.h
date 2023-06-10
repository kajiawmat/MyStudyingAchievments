#ifndef SCHOOLBOYSWINDOW_H
#define SCHOOLBOYSWINDOW_H

#include <QDialog>
#include <QLayout>
#include<QTableView>
#include<QSql>
#include<QSqlTableModel>

namespace Ui {
class schoolBoysWindow;
}

class schoolBoysWindow : public QDialog
{
    Q_OBJECT


public slots:
    void SaveChanges();

public:
    explicit schoolBoysWindow(QTableView *Schoolers, QSqlTableModel *model, QWidget *parent = 0);
    ~schoolBoysWindow();

private:
    Ui::schoolBoysWindow *ui;
    QSqlTableModel *Model;
};

#endif // SCHOOLBOYSWINDOW_H
