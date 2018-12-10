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

    void displayError(QLocalSocket::LocalSocketError);
    bool writeData(QByteArray);

private slots:
        void getResponseFromServer();
        void on_Register_clicked();
        void getRegisterData(QString);
        bool connectToServer();
        void sendLoginData(QString);
        void on_logIn_clicked();
        void sendFileToServer(QByteArray);
        void downloadFromServer(QByteArray);
        void on_disconnectClient_clicked();

        void on_connectTo_clicked();

public slots:
        void showMainWindow();
signals:
        void loginData(QString);
private:
    LoginForm * loginForm;
    Ui::client *ui;
    userRegister *registerForm;
    QTcpSocket  *socket;
    QString login;
    FileList * fileList;
      QString logUser;
      QHash<QTcpSocket*, QByteArray*> buffers; //bufor do przetrzymywania danych az dojda cale
      QHash<QTcpSocket*, qint32*> sizes;
      void process();
};

#endif // CLIENT_H
