#include "bazadanych.h"

BazaDanych::BazaDanych(QString type,QString path):dbType(type),pathToDbFile(path)
{
startDb();
}

void BazaDanych::startDb(){
    mydb = QSqlDatabase::addDatabase(dbType);
    mydb.setDatabaseName(pathToDbFile);
    if(!mydb.open()){
       status = "błąd połączenia z bazą danych...";
    } else{
       status = "Połączono z bazą danych!";
    }
}

QString BazaDanych::getStatus(){
    return status;
}

QSqlQueryModel * BazaDanych::getData(QString q){
        QSqlQueryModel *  model = new QSqlQueryModel();
        QSqlQuery * query = new QSqlQuery(mydb);
        query->prepare(q);
        query->exec();
        model->setQuery(*query);
        return model;
}

void BazaDanych::deleteRow(int row){
    QSqlQueryModel *  model = new QSqlQueryModel();
    QSqlQuery * query = new QSqlQuery(mydb);
    query->prepare("delete * from users where id = ?");
    query->addBindValue(row);
    query->exec();
}

BazaDanych::~BazaDanych(){
    mydb.close();
}

