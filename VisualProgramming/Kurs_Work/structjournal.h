#ifndef STRUCTJOURNAL_H
#define STRUCTJOURNAL_H

#include<QDate>
#include<QStringList>
#include<QFile>
#include<QDebug>
#include<QTextDocumentWriter>

class StructJournal
{
public:
    StructJournal();
    ~StructJournal();
    QString QuartersDates[4][2];
    QStringList Subjects;
    QList<QString*> SubjectDays;
    QStringList SchoolBoys;
    QStringList BirthDates;

    void ReadJournalFile(QString *FilePath);
    void WriteJournalFile(QString *FilePath);
    void SetData(QString str);

private:
    QString ClassName;
    QString TeacherName;
};

#endif // STRUCTJOURNAL_H
