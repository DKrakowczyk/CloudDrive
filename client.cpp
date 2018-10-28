#include "client.h"
#include "ui_client.h"
#include "filemanager.h"
static inline qint32 ArrayToInt(QByteArray source);

client::client(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::client)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    //--FORMULARZ LOGOWANIA------------------
    loginForm = new LoginForm(this);
    connect(loginForm, SIGNAL(loginUser(QString)), this, SLOT(sendLoginData(QString)));
    //--POBIERANIE DANYCH Z SERWERA------------------------------------
    connect(socket, SIGNAL(readyRead()), this, SLOT(readFortune()));
    //--FORMULARZ REJESTRACJI
    registerForm = new userRegister(this);
    connect(registerForm, SIGNAL(registerUser(QString)), this, SLOT(getRegisterData(QString)));

    connect(ui->connectTo, SIGNAL(clicked()), this, SLOT(connectToServer()));
    ui->logIn->setDisabled(1);
    ui->Register->setDisabled(1);
}

bool client::connectToServer()
{
    socket->connectToHost(ui->serverName->text(), ui->server_port->text().toInt(), QIODevice::ReadWrite);
    if (socket->state() == QAbstractSocket::ConnectedState) {
        QMessageBox::information(this, tr("Komunikat aplikacji klienckiej"),
            tr("Połączono "));
        ui->Register->setEnabled(1);
        ui->logIn->setEnabled(1);
    }
    return socket->waitForConnected();
}
QByteArray IntToArray(qint32 source) //Use qint32 to ensure that the number have 4 bytes
{
    //Avoid use of cast, this is the Qt way to serialize objects
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;
    return temp;
}

void client::readFortune()
{
    QByteArray line = socket->readLine();
    QList<QByteArray> dane = line.split('|');
    QString check = dane.takeAt(0);


    if (check == "log")
    {
        QString response = dane.takeAt(0);
        if(response == "success")
        {
            fileList = new FileList(this);
            loginForm->close();
            fileList->show();
            logUser = dane.takeAt(0);
            QString trash = dane.takeAt(0);//------------------------------------------------
            QString trash2 = dane.takeAt(0);//-ZMIENNE USUWAJĄCE ZŁE ODP Z SERWERA-----------
            QString trash3 = dane.takeAt(0);//-----------------------------------------------
             fileList->updateAll(dane);
            fileList->setLogin(logUser);
            connect(fileList, SIGNAL(sendFile(QByteArray)), this, SLOT(sendFileToServer(QByteArray)));
            connect(fileList, SIGNAL(getFile(QByteArray)), this, SLOT(downloadFromServer(QByteArray)));
            QMessageBox::information(this, tr("Komunikat aplikacji klienckiej"),
                tr("Użytkownik %1 zalogowany pomyślnie!")
                                     .arg(logUser));
            }
            else if(response == "error")
            {
                QMessageBox::information(this, tr("Komunikat aplikacji klienckiej"),
                    tr("Błędny login lub hasło"));
            }
            qDebug() << "Response  " << response;
        }
    else if(check == "reg")
    {
         QString login = dane.takeAt(0);
         if(login != "")
         {
             QString password = dane.takeAt(0);
             QMessageBox::information(this, tr("Komunikat aplikacji klienckiej"),
             tr("Użytkownik %1 zarejestrowany pomyślnie!\nHasło: %2")
             .arg(login).arg(password));
         }
    }
    else if(check == "send")
    {
        qDebug() << "POWINNO UPDATOWAC";
        fileList = new FileList(this);
        fileList->show();
        fileList->setLogin(logUser);
        connect(fileList, SIGNAL(sendFile(QByteArray)), this, SLOT(sendFileToServer(QByteArray)));
        connect(fileList, SIGNAL(getFile(QByteArray)), this, SLOT(downloadFromServer(QByteArray)));
        QString response = dane.takeAt(0);
        QString trash = dane.takeAt(0);//------------------------------------------------
        QString trash2 = dane.takeAt(0);//-ZMIENNE USUWAJĄCE ZŁE ODP Z SERWERA-----------
        QString trash3 = dane.takeAt(0);//-----------------------------------------------
        fileList->updateAll(dane);
        if(response == "success")
        {
            fileList->showSuccess();
        }
        else
        {
            fileList->showError();
        }

    }
    else if(check=="get")
    {
        qDebug() << "Przyszedł plik";
        QString login = dane.takeAt(0);
        QString filename = dane.takeAt(0);
        int toRemove = 4+login.length()+1+filename.length()+1;
        if (login != "" && filename != "")
        {
                FileManager * fm = new FileManager(this);
                QFile * plik = new QFile(filename);
                fm->createDirectory(login);
                if (!plik->open(QIODevice::ReadWrite))
                {

                }
                else
                {
                    QByteArray buffer = line.remove(0,toRemove);
                    plik->write(buffer);
                    plik->close();
                    fm->addFile(login,plik);
                    qDebug() << "dodano";
                    //tworzenie odpowiedzi dla klienta

                }
        }
    }

 qDebug() << line;

}
bool client::writeData(QByteArray data)
{

    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->write(IntToArray(data.size())); //write size of data
        socket->write(data); //write the data itself
        return socket->waitForBytesWritten();
    }
    else
        return false;
}
void client::disconnectFromServer()
{
    qDebug() << "rozlaczono";
 socket->disconnectFromHost();
}
//-----------------------------------------------------
client::~client()
{
    delete ui;
}
void client::showMainWindow()
{
    ui->centralWidget->show();
}
void client::on_Register_clicked()
{
    registerForm->show();
}

void client::getRegisterData(QString registerString)
{
    qDebug()<<registerString;
    QByteArray regArray;
    regArray.append(registerString);
    writeData(regArray);
}

void client::sendLoginData(QString loginString)
{
    qDebug()<<loginString;
    login = loginForm->getLogin();
    QByteArray regArray;
    regArray.append(loginString);
    writeData(regArray);
}

void client::sendFileToServer(QByteArray file)
{
    qDebug() << "Rozpoczeto przesylanie";
    writeData(file);
}

void client::on_logIn_clicked()
{
    loginForm->show();
}
void client::downloadFromServer(QByteArray downloadString)
{
    qDebug() << "Rozpoczęto pobieranie";
    writeData(downloadString);
}
