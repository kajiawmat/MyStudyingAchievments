#include "database.h"

DataBase::DataBase(QString Path,QObject *parent) : QObject(parent)
{
    PathDB=Path;
}

DataBase::~DataBase()
{

}

void DataBase::connectToDB()
{
    if(!QFile(PathDB+"/"+DATABASE_NAME).exists())
    {
        this->restoreDB();
    }else{
        this->openDB();
    }
}

bool DataBase::restoreDB()
{
    if(this->openDB()){
        if(!this->createTableSchoolBoy())
        {
            qDebug("restore not completed");
            return false;
        } else
        {
            qDebug("restore completed");
            return true;
        }
    } else {
        qDebug() << "Didn't restore database";
        return false;
    }
}

bool DataBase::openDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(PathDB+"/"+DATABASE_NAME);
    if(db.open()){
        qDebug("Database opened");
        return true;
    } else {
        qDebug("Database didn't open");
        return false;
    }
}

void DataBase::closeDB()
{
    db.close();
}

bool DataBase::createTableSchoolBoy()
{
    QSqlQuery query;
    if(!query.exec("CREATE TABLE SchoolBoy (Name	TEXT NOT NULL, BirthDate	TEXT NOT NULL, Address	TEXT, Phone	TEXT, MotherName	TEXT, MotherPhone	TEXT, FatherName	TEXT, FatherPhone	TEXT,PRIMARY KEY(Name))"))
    {
        qDebug() << "DataBase: CreatingError" << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        qDebug("query SchoolBoy created");
        return true;
    }
}



