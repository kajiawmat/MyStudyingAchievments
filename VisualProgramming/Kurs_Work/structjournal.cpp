#include "structjournal.h"

StructJournal::StructJournal()
{

}

StructJournal::~StructJournal()
{
    Subjects.clear();
    SubjectDays.clear();
    SchoolBoys.clear();
    BirthDates.clear();
}

void StructJournal::ReadJournalFile(QString *FilePath)
{
    QFile *file=new QFile(*FilePath);
    if(!file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug("File with journal data not found");
        return;
    }
    QStringList data=QString(file->readAll()).split("\n\n");
    if(data.count()!=3)
    {
        qDebug("File with journal data corrupted");
        return;
    }
    QStringList temp=data[0].split("\n");
    ClassName=temp[0];
    TeacherName=temp[1];
    for(int i=0;i<4;i++) for(int j=0;j<2;j++) QuartersDates[i][j]=temp[i*2+j+2];
    temp.clear();
    temp=data[1].split("\n");
    Subjects.clear();
    SubjectDays.clear();
    for(int i=0;i<temp.size();i++)
    {
        QStringList sub=temp[i].split(" ");
        Subjects.push_back(sub[0]);
        QString days[6];
        for(int i=0;i<6;i++)
        {
            days[i]=sub[i+1];
        }
        SubjectDays.push_back(days);
    }
    temp.clear();
    temp=data[2].split("\n");
    SchoolBoys.clear();
    BirthDates.clear();
    for(int i=0;i<temp.size();i++)
    {
        QStringList boy=temp[i].split(" ");
        SchoolBoys.push_back(boy[0]);
        BirthDates.push_back(boy[1]);
    }
    file->close();
}

void StructJournal::WriteJournalFile(QString *FilePath)
{
    QFile *file=new QFile(*FilePath);
    if(!file->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug("WritingJournalError");
        return;
    }
    QString data="";
    data+=QString(ClassName+"\n"+TeacherName+"\n");
    for(int i=0;i<4;i++) for(int j=0;j<2;j++) data+=QString(QuartersDates[i][j]+"\n");
    data+="\n";
    for(int i=0;i<Subjects.size();i++)
    {
        data+=QString(Subjects[i] + " " +
                SubjectDays[i][0] + " " +
                SubjectDays[i][1] + " " +
                SubjectDays[i][2] + " " +
                SubjectDays[i][3] + " " +
                SubjectDays[i][4] + " " +
                SubjectDays[i][5] + "\n");
    }
    data+="\n";
    for(int i=0;i<SchoolBoys.size();i++)
    {
        data+=QString(SchoolBoys[i] + " " + BirthDates[i] + "\n");
    }
    QTextStream writer(file);
    writer << data;
    file->close();
}
