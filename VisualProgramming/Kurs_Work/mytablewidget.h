#ifndef MYTABLEWIDGET_H
#define MYTABLEWIDGET_H

#include <QtWidgets>

class MyTableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyTableWidget(QStandardItemModel *schoolerTable,QStandardItemModel *marksTable[4],QStandardItemModel *resTable[4]);

public slots:
    void PagePlus();
    void PageMinus();
    void GetPage();
    void SetPage(int id);

signals:
    void SentPage(QString page);

private:
    QStandardItemModel *Schooler;
    QStandardItemModel *Marks[4];
    QStandardItemModel *Results[4];
    QTableView *SchoolerView;
    QTableView *MarksView;
    QTableView *ResultsView;
    int curPage;
    void SetView(int id);
};

#endif // MYTABLEWIDGET_H
