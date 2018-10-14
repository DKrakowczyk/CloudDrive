#include "UserList.h"
#include "ui_UserList.h"

UserList::UserList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserList)
{
    ui->setupUi(this);
    setDbPath();
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
void UserList::setDbPath(){
    QFile file;
    file.setFileName("con_string.txt");

    if(file.open((QIODevice::ReadOnly)))
    {
        QTextStream in(&file);
        QString con_str = in.readLine();
        if(con_str != "")
        {
            dbPath = con_str;
        }
    }

}
