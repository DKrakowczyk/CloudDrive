#include "usereditform.h"
#include "ui_usereditform.h"

userEditForm::userEditForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::userEditForm)
{
    ui->setupUi(this);
    this->move(150,150);
}

userEditForm::~userEditForm()
{
    delete ui;
}

void userEditForm::setFields(QString _login,QString _password){
    this->login = _login;
    this->password = _password;
    setLabels();
}

void userEditForm::setLabels(){
    ui->textLogin->setPlainText(login);
    ui->textPassword->setPlainText(password);

}

void userEditForm::on_buttonReject_clicked()
{
    this->close();
}

void userEditForm::on_buttonDelete_clicked()
{
   emit deleteSignal();
    this->close();
}

QString userEditForm::getLogin(){
    return this->ui->textLogin->toPlainText();
}

QString userEditForm::getpassword(){
    return this->ui->textPassword->toPlainText();
}

void userEditForm::on_buttonAccept_clicked()
{
    emit changeSignal();
    this->close();
}
