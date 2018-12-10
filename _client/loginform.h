#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);
    QString getLogin();
    QString getPassword();
    ~LoginForm();

private slots:
    void on_closeButton_clicked();
    void on_loginButton_clicked();

signals:

    void loginUser(QString);
private:
    Ui::LoginForm *ui;
};

#endif // LOGINFORM_H
