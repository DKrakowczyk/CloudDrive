#include "userregister.h"
#include "ui_userregister.h"
#include <QCryptographicHash>
userRegister::userRegister(QWidget *parent) :
    QWidget(parent, Qt::Window),
    ui(new Ui::userRegister)
{
    ui->setupUi(this);
    QPixmap pic(":/client/note.png");
    ui->regIcon->setPixmap(pic);
}

userRegister::~userRegister()
{
    delete ui;
}

void userRegister::on_closeButton_clicked()
{
    this->close();
}

void userRegister::on_registerButton_clicked()
{
    QString password = ui->userPassword->text();
    QString hashed = QString(QCryptographicHash::hash((password.toUtf8()),QCryptographicHash::Md5).toHex());
    QString registerString = "reg|"+ui->userLogin->text()+"|"+hashed+"|";
    emit registerUser(registerString);
    this->close();
}
