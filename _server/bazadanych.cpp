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

void BazaDanych::deleteRow(QString row){
    QSqlQuery * query = new QSqlQuery(mydb);
    query->prepare("delete from users where login = :row");
    query->bindValue(":row", row);
    query->exec();
}

void BazaDanych::addUser(QString login, QString password)
{
    QSqlQuery * query = new QSqlQuery(mydb);
    query->prepare("INSERT INTO users(login,password) VALUES(:log,:pass)");
    query->bindValue(":log", login);
    query->bindValue(":pass", password);
    query->exec();
}
bool BazaDanych::userExist(QString login, QString password)
{
    QSqlQueryModel *  model = new QSqlQueryModel();
    QSqlQuery * query = new QSqlQuery(mydb);
    query->prepare("SELECT login FROM users WHERE login = :log AND password= :pass");
    query->bindValue(":log", login);
    query->bindValue(":pass", password);
    query->exec();
    model->setQuery(*query);
   mydb.close();
    if(  model->data(model->index(0,0)).toString() == "") return false;
    else return true;

}
void BazaDanych::changeData(QString row,QString log, QString pass){
    QSqlQuery * query = new QSqlQuery(mydb);
    query->prepare("update users set login = :log, password= :pass where login = :row");
    query->bindValue(":row", row);
    query->bindValue(":log", log);
    query->bindValue(":pass", pass);
    query->exec();
}


BazaDanych::~BazaDanych(){
    mydb.close();
}

