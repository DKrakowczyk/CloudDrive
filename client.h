#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtNetwork>
#include "userregister.h"
#include "loginform.h"
#include "filelist.h"
namespace Ui {
class client;
}

class client : public QMainWindow
{
    Q_OBJECT

public:
    explicit client(QWidget *parent = nullptr);
    ~client();
    bool connectToServer();
    void displayError(QLocalSocket::LocalSocketError);
    bool writeData(QByteArray);

private slots:
        void readFortune();
        void on_Register_clicked();
        void getRegisterData(QString);
        void on_connectTo_clicked();
        void sendLoginData(QString);
        void on_logIn_clicked();
public slots:
        void showMainWindow();
private:
    LoginForm * loginForm;
    Ui::client *ui;
    userRegister *registerForm;
    QTcpSocket  *socket;
    QString login;
    FileList * fileList;
};

#endif // CLIENT_H
