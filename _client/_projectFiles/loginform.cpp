#include "loginform.h"
#include "ui_loginform.h"
#include <QCryptographicHash>

LoginForm::LoginForm(QWidget* parent)
    : QWidget(parent, Qt::Window)
    , ui(new Ui::LoginForm)
{
    ui->setupUi(this);
    QPixmap pic(":/client/login.png");
    ui->logIcon->setPixmap(pic);
}

LoginForm::~LoginForm()
{
    delete ui;
}

QString LoginForm::getLogin()
{
    return ui->loginInput->text();
}

QString LoginForm::getPassword()
{
    QString password = ui->passwordInput->text();
    QString hashed = QString(QCryptographicHash::hash((password.toUtf8()), QCryptographicHash::Md5).toHex());
    return hashed;
}

void LoginForm::on_closeButton_clicked()
{

    this->close();
}

void LoginForm::on_loginButton_clicked()
{
    QString registerString = "log|" + this->getLogin() + "|" + this->getPassword() + "|";
    emit loginUser(registerString);
}
