#include "mytablewidget.h"

MyTableWidget::MyTableWidget(QStandardItemModel *schoolerTable,QStandardItemModel *marksTable[4],QStandardItemModel *resTable[4]) : QWidget()
{
    Schooler=schoolerTable;
    for(int i=0;i<4;i++)
    {
        Marks[i]=marksTable[i];
        Results[i]=resTable[i];
    }

    SchoolerView=new QTableView();
    MarksView=new QTableView();
    ResultsView=new QTableView();

    QHBoxLayout *layout=new QHBoxLayout();
    layout->addWidget(SchoolerView);
    layout->addWidget(MarksView);
    layout->addWidget(ResultsView);

    SchoolerView->setModel(Schooler);
    SchoolerView->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    SchoolerView->setMaximumSize(225,10000);
    SchoolerView->setMinimumSize(225,50);
    SchoolerView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    MarksView->setModel(Marks[0]);
    MarksView->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ResultsView->setModel(Results[0]);
    ResultsView->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    ResultsView->setMaximumSize(250,10000);
    ResultsView->setMinimumSize(250,0);
    ResultsView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    SchoolerView->verticalScrollBar()->hide();
    MarksView->verticalHeader()->hide();
    MarksView->verticalScrollBar()->hide();
    ResultsView->verticalHeader()->hide();
    connect(ResultsView->verticalScrollBar(),SIGNAL(valueChanged(int)),MarksView->verticalScrollBar(),SLOT(setValue(int)));
    connect(ResultsView->verticalScrollBar(),SIGNAL(valueChanged(int)),SchoolerView->verticalScrollBar(),SLOT(setValue(int)));


    setLayout(layout);
    //Добавить функциональную зависимость в myPushButton (изменение значения)
    curPage=0;
}

void MyTableWidget::SetView(int id)
{
    if(id<0 || id>=4) return;
    MarksView->setModel(Marks[id]);
    ResultsView->setModel(Results[id]);
}

void MyTableWidget::PageMinus()
{
    if(curPage>0) curPage--;
    MarksView->setModel(Marks[curPage]);
    ResultsView->setModel(Results[curPage]);
    MarksView->verticalScrollBar()->setValue(SchoolerView->verticalScrollBar()->value());
    ResultsView->verticalScrollBar()->setValue(SchoolerView->verticalScrollBar()->value());
    emit SentPage(QString::number(curPage+1)+"/4 четверть");
}

void MyTableWidget::PagePlus()
{
    if(curPage<3) curPage++;
    MarksView->setModel(Marks[curPage]);
    ResultsView->setModel(Results[curPage]);
    MarksView->verticalScrollBar()->setValue(SchoolerView->verticalScrollBar()->value());
    ResultsView->verticalScrollBar()->setValue(SchoolerView->verticalScrollBar()->value());
    emit SentPage(QString::number(curPage+1)+"/4 четверть");
}

void MyTableWidget::GetPage()
{
    emit SentPage(QString::number(curPage+1)+"/4 четверть");
}

void MyTableWidget::SetPage(int id)
{
    MarksView->setModel(Marks[id]);
    ResultsView->setModel(Results[id]);
    MarksView->verticalScrollBar()->setValue(SchoolerView->verticalScrollBar()->value());
    ResultsView->verticalScrollBar()->setValue(SchoolerView->verticalScrollBar()->value());
}
