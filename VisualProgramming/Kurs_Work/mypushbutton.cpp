#include "mypushbutton.h"

myPushButton::myPushButton(QVector<QString> schoolars, QString QuartersDates[][2], QString path, QString str, QWidget *pwdt): QPushButton(str,pwdt)
{
    FilePath=path+"/"+str;
    schoolarTable=new QStandardItemModel();
    for(int i=0;i<4;i++)
    {
        marksTable[i]=new QStandardItemModel();
        resTable[i]=new QStandardItemModel();
    }
    for(int k=0;k<4;k++)
    {
        for(int i=0;i<2;i++)
        {
            Dates[k][i]=QDate::fromString(QuartersDates[k][i],"dd.MM.yyyy");
        }
    }
    curPage=0;
    SetNewSchoolars(schoolars);
    ReadQuarterFile();
    ReadYearFile();
    connect(this,SIGNAL(clicked(bool)),this,SLOT(GetTable()));
}

void myPushButton::ReadQuarterFile()
{
    QFile *file=new QFile(FilePath+"/Quarter.csv");
    if(!file->exists())
    {
        qDebug("File quarter marks not opened");
    }
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    QStringList fileData=QString(file->readAll()).split("\n");
    QStringList days=fileData[0].split(";");
    for(int i=1;i<7;i++) DaysInWeek[i]=days[i-1].toInt();
    QStringList dates=fileData[1].split(";");
    QStringList *marks=new QStringList[fileData.size()];
    schoolarTable->setHeaderData(0,Qt::Horizontal,"ФИО ученика");
    for(int i=2;i<fileData.size();i++) marks[i]=fileData[i].split(";");
    for(int k=0;k<4;k++)
    {
        int first,last;
        qDebug(QString::number(marks[2].size()).toUtf8());
        for(first=0;first<dates.size()-1;first++)
        {
            if(Dates[k][0]<=QDate::fromString(dates[first],"dd.MM.yyyy")) break;
        }
        for(last=first;last<dates.size()-1;last++)
        {
            if(Dates[k][1]<QDate::fromString(dates[last],"dd.MM.yyyy")) break;
        }
        marksTable[k]->setColumnCount(last-first);
        for(int j=0;j<marksTable[k]->columnCount();j++)
        {
            marksTable[k]->setHeaderData(j, Qt::Horizontal, dates[j+first]);
        }
        for(int i=2;i<fileData.size();i++)
        {
            QList<QStandardItem*> rowData;
            for(int j=first;j<last;j++) rowData.push_back(new QStandardItem(marks[i][j]));
            marksTable[k]->appendRow(rowData);
        }
    }
    file->close();
}

void myPushButton::WriteQuarterFile()
{
    QFile *file=new QFile(FilePath+"/Quarter.csv");
    if(!file->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug("WritingQuarterError");
        return;
    }
    QString data="";
    for(int i=1;i<7;i++) data+=QString::number(DaysInWeek[i])+";";
    data+="\n";
    qDebug("1");
    for(int k=0;k<4;k++)
    {
        for(int j=0;j<marksTable[k]->columnCount();j++)
        {
            data+=marksTable[k]->headerData(j,Qt::Horizontal).toString();
        }
    }
    data+="\n";
    qDebug("2");
    for(int i=0;i<marksTable[0]->rowCount();i++)
    {
        for(int k=0;k<4;k++)
        {
            for(int j=0;j<marksTable[k]->columnCount();k++)
            {
                data+=marksTable[k]->data(marksTable[k]->index(i,j)).toString()+";";
            }
        }
        data+="\n";
    }
    qDebug("3");
    file->write(data.toUtf8());
    file->close();
}

void myPushButton::ReadYearFile()
{
    QFile *file=new QFile(FilePath+"/Year.csv");
    if(!file->exists())
    {
        qDebug("File year marks not opened");
    }
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    QString fileStr=QString(file->readAll());
    //qDebug(fileStr.toUtf8());
    if(fileStr=="") return;
    QStringList fileData=fileStr.split("\n");
    file->close();
    for(int k=0;k<4;k++)
    {
        resTable[k]->setColumnCount(2);
        resTable[k]->setRowCount(fileData.size()-1);
        resTable[k]->setHeaderData(0,Qt::Horizontal,"Ср. оценка");
        resTable[k]->setHeaderData(1,Qt::Horizontal,"Итог. оценка");
    }
    for(int i=0;i<fileData.size()-1;i++)
    {
        QStringList temp=fileData[i].split(";");
        for(int k=0;k<4;k++)
        {
            resTable[k]->setData(resTable[k]->index(i,1),temp[k]);
        }
    }
}


void myPushButton::WriteYearFile()
{
    QFile *file=new QFile(FilePath+"/Year.csv");
    file->open(QIODevice::WriteOnly | QIODevice::Text);
    QString data="";
    for(int i=0;i<resTable[0]->rowCount();i++)
    {
        for(int k=0;k<4;k++) data+=(resTable[k]->data(resTable[k]->index(i,1))).toString()+";";
        data+=";;;\n";
    }
    file->write(data.toUtf8());
    file->close();
}

void myPushButton::InsertRow(int id, QString name)
{
    schoolarTable->insertRow(id);
    for(int i=0;i<4;i++)
    {
        marksTable[i]->insertRow(id);
        resTable[i]->insertRow(id);
        //Для ResWindow я также должен буду добавлять в списки пропущенных и сумм с кол-вом на нужную позицию элемент
    }
    schoolarTable->setData(schoolarTable->index(id,0),name);
}

void myPushButton::DeleteRow(int id)
{
    schoolarTable->removeColumn(id);
    for(int i=0;i<4;i++)
    {
        marksTable[i]->removeRow(id);
        resTable[i]->removeRow(id);
    }
}

void myPushButton::InsertColumns(QString first, QString last, int quarter, int days[])
{
    int id,day;
    if(days==NULL) days=DaysInWeek;
    QDate First=QDate::fromString(first,"dd.MM.yyyy");
    QDate Last=QDate::fromString(last,"dd.MM.yyyy");
    QDate Temp;
    for(id=0;id<marksTable[quarter]->columnCount();id++)
    {
        Temp=QDate::fromString(marksTable[quarter]->headerData(id,Qt::Horizontal).toString(),"dd.MM.yyyy");
        if(Temp>First) break;
    }
    for(;id<marksTable[quarter]->columnCount();First=First.addDays(1))
    {
        Temp=QDate::fromString(marksTable[quarter]->headerData(id,Qt::Horizontal).toString(),"dd.MM.yyyy");
        if(Temp>Last) break;
        day=First.dayOfWeek();
        if(day==7) continue;
        for(int i=0;i<days[day];i++)
        {
            marksTable[quarter]->insertColumn(id);
            marksTable[quarter]->setHeaderData(id,Qt::Horizontal,First.toString("dd.MM.yyyy"));
            id++;
        }
    }
}

void myPushButton::DeleteColumns(QString first, QString last, int quarter)
{
    int id;
    QDate First=QDate::fromString(first,"dd.MM.yyyy");
    QDate Last=QDate::fromString(last,"dd.MM.yyyy");
    QDate Temp;
    for(id=0;id<marksTable[quarter]->columnCount();id++)
    {
        Temp=QDate::fromString(marksTable[quarter]->headerData(id,Qt::Horizontal).toString(),"dd.MM.yyyy");
        if(Temp>First) break;
    }
    while(id<marksTable[quarter]->columnCount())
    {
        Temp=QDate::fromString(marksTable[quarter]->headerData(id,Qt::Horizontal).toString(),"dd.MM.yyyy");
        if(Temp>Last) break;
        marksTable[curPage]->removeColumn(id);
    }
}

void myPushButton::SetNewSchoolars(QVector<QString> schoolars)
{
    schoolarTable->clear();
    for(int i=0;i<schoolars.size();i++)
    {
        schoolarTable->insertRow(i,new QStandardItem(schoolars[i]));
    }
}

void myPushButton::GetTable()
{
    MyTableWidget *table=new MyTableWidget(schoolarTable,marksTable,resTable);
    emit sentTable(table,text());
}
