#ifndef USERLIST_H
#define USERLIST_H
#include "bazadanych.h"
#include "usereditform.h"
#include <QWidget>

namespace Ui {
class UserList;
}

class UserList : public QWidget
{
    Q_OBJECT

public:
    explicit UserList(QWidget *parent = nullptr);
    void setDbPath();
    void refresh();
    ~UserList();
signals:
    void closeWindow();
private slots:
    void on_pushButton_clicked();
public slots:
   void onTableClicked(const QModelIndex &);
   void changeRow();
   void deleteRow();
private:
    Ui::UserList *ui;
    BazaDanych * bazaDanych;
    userEditForm * editForm;
    QString dbPath;
    QString currentId,login,password;
};

#endif // USERLIST_H
