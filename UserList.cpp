#include "UserList.h"
#include "ui_UserList.h"

UserList::UserList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserList)
{
    ui->setupUi(this);

    bazaDanych = new BazaDanych("QSQLITE",dbPath);
    ui->label_dbStatus->setText(bazaDanych->getStatus());
    ui->tableView->setModel(bazaDanych->getData("select * from users"));
}

UserList::~UserList()
{
    delete ui;
    delete bazaDanych;
}

void UserList::on_pushButton_clicked()
{
    emit closeWindow();
    this->close();
}
void UserList::setDbPath(QString path){
    dbPath = path;
}
