#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QSql>
#include <QFileDialog>
#include <QSqlTableModel>
#include "mypushbutton.h"
#include "structjournal.h"
#include "structjournalwindow.h"
#include "addschoolboywindow.h"
#include "addsubjectwindow.h"
#include "schoolboyswindow.h"
#include "changetimeperiodwindow.h"
#include "database.h"
#include "delwindow.h"
#include "mytablewidget.h"
#include "reswindow.h"
#include "helpwindow.h"
#include "QHelpEvent"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    DataBase *db;
    QSqlTableModel *model;
    QTableView *SchoolBoysView;

signals:
    void changePage(int);

public slots:


private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_tabWidget_tabCloseRequested(int index);
    void on_menubar_loadjournal_clicked();
    void on_menubar_createjournal_clicked();
    void on_menubar_savejournal_clicked();
    void on_menubar_changejournal_clicked();
    void on_menubar_addschoolboy_clicked();
    void on_menubar_delschoolboy_clicked();
    void on_menubar_changeschoolboy_clicked();
    //void on_menubar_resultschoolboy_clicked();
    void on_menubar_addsubject_clicked();
    void on_menubar_delsubject_clicked();
    void on_menubar_changetimeperiod_clicked();
    //void on_menubar_resultsubject_clicked();
    void on_menubar_help_clicked();

    void createJournal(QString*);
    void changeJournal(QString*);
    void addSchoolBoy(QString*);
    void delSchoolBoy(QVector<int>);
    void addSubject(QString*);
    void delSubject(QVector<int>);

    void GetTable(MyTableWidget*, QString);

    void ChangeTable();
    void CloseTab();

private:
    Ui::MainWindow *ui;
    int CurrentPage;
    QString CurrentPath;
    QString CurrentSubject;
    QString Name;
    QString Teacher;
    QVector<QString> SchoolBoys;//в mypushbutton
    QVector<myPushButton*> Buttons;
    QString QuartersDates[4][2];
    QStringList GetDate(QDate first, QDate last, int times[]);
    int SetSchoolBoy(QString Name, int L, int R);
    void CreateSubjectFile(QString str);
};

#endif // MAINWINDOW_H
