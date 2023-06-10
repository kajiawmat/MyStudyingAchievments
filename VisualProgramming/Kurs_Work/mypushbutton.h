#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H
#include <QtWidgets>
#include"mytablewidget.h"
class myPushButton : public QPushButton
{
    Q_OBJECT

signals:
    void sentTable(MyTableWidget *table,QString text);

public slots:
    void GetTable();

public:
    explicit myPushButton(QVector<QString> schoolars, QString QuartersDates[4][2], QString path, QString str="File", QWidget *pwdt=0);
    void ReadQuarterFile();
    void WriteQuarterFile();
    void ReadYearFile();
    void WriteYearFile();
    void InsertRow(int id, QString name);
    void DeleteRow(int id);
    void InsertColumns(QString first, QString last, int quarter, int days[7]=NULL);
    void DeleteColumns(QString first, QString last, int quarter);
    void SetNewSchoolars(QVector<QString> schoolars);

private:
    QString FilePath;
    QStandardItemModel *schoolarTable;
    QStandardItemModel *marksTable[4];
    QStandardItemModel *resTable[4];
    QList<QString> resYear;
    QList<int> *bNum;
    QList<int> *oNum;
    QList<int> *nNum;
    QDate Dates[4][2];
    int DaysInWeek[7];
    int curPage;
};

#endif // MYPUSHBUTTON_H
