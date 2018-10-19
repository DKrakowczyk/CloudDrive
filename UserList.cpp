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
    this->refresh();
    connect(ui->tableView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClicked(const QModelIndex &)));

}

UserList::~UserList()
{
    delete ui;
    delete bazaDanych;
    delete editForm;
}

void UserList::on_pushButton_clicked()
{
    emit closeWindow();
    this->close();
}

void UserList::onTableClicked(const QModelIndex & indexNumber){
    editForm = new userEditForm(this);
    QString id = indexNumber.siblingAtColumn(0).data().toString();
    QString login = indexNumber.siblingAtColumn(1).data().toString();
    QString password = indexNumber.siblingAtColumn(2).data().toString();
    connect(editForm, SIGNAL(deleteSignal()), this, SLOT(deleteRow(id)));
    editForm->setFields(id,login,password);
    editForm->show();
}

void UserList::deleteRow(QString row){
    bazaDanych->deleteRow(row.toInt());
    this->refresh();
}

void UserList::refresh(){
ui->tableView->setModel(bazaDanych->getData("select * from users"));
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
