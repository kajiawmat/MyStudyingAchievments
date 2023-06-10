#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>

#define DATABASE_NAME       "DataBase.db"

#define TABLE               "SchoolBoy"
#define TABLE_NAME          "Name"
#define TABLE_BIRTHDATE     "BirthDate"
#define TABLE_ADDRESS       "Address"
#define TABLE_PHONE         "Phone"
#define TABLE_MOTHERNAME    "MotherName"
#define TABLE_MOTHERPHONE   "MotherPhone"
#define TABLE_FATHERNAME    "FatherName"
#define TABLE_FATHERPHONE   "FatherPhone"

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QString Path, QObject *parent = nullptr);
    ~DataBase();

    void connectToDB();

private:
    QSqlDatabase    db;
    QString PathDB;
    bool openDB();
    bool restoreDB();
    void closeDB();
    bool createTableSchoolBoy();
};

#endif // DATABASE_H
