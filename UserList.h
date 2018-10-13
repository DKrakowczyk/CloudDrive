#ifndef USERLIST_H
#define USERLIST_H
#include "bazadanych.h"
#include <QWidget>

namespace Ui {
class UserList;
}

class UserList : public QWidget
{
    Q_OBJECT

public:
    explicit UserList(QWidget *parent = nullptr);
    void setDbPath(QString);
    ~UserList();
signals:
    void closeWindow();
private slots:
    void on_pushButton_clicked();

private:
    Ui::UserList *ui;
    BazaDanych * bazaDanych;
    QString dbPath;
};

#endif // USERLIST_H
