#include "client.h"
#include "ui_client.h"
#include "filemanager.h"
static inline qint32 ArrayToInt(QByteArray source);

client::client(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::client)
{
    ui->setupUi(this);
    QPixmap pic(":/client/client.png");
    ui->clientIcon->setPixmap(pic);
    socket = new QTcpSocket(this);
    //--FORMULARZ LOGOWANIA------------------
    loginForm = new LoginForm(this);
    connect(loginForm, SIGNAL(loginUser(QString)), this, SLOT(sendLoginData(QString)));
    //--POBIERANIE DANYCH Z SERWERA------------------------------------
    connect(socket, SIGNAL(readyRead()), this, SLOT(getResponseFromServer()));
    //--FORMULARZ REJESTRACJI
    registerForm = new userRegister(this);
    connect(registerForm, SIGNAL(registerUser(QString)), this, SLOT(getRegisterData(QString)));

    ui->logIn->setDisabled(1);
    ui->Register->setDisabled(1);
    ui->disconnectClient->setDisabled(1);
}

bool client::connectToServer()
{
    socket->connectToHost(ui->serverName->text(), ui->server_port->text().toInt(), QIODevice::ReadWrite);

    if (socket->waitForConnected()) {
        QMessageBox::information(this, tr("Message of the client application"),
            tr("Connected!"));
    }
    return 1;
}
QByteArray IntToArray(qint32 source) //Use qint32 to ensure that the number have 4 bytes
{
    //Avoid use of cast, this is the Qt way to serialize objects
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;
    return temp;
}
qint32 ArrayToInt(QByteArray source)
{
    qint32 temp;
    QDataStream data(&source, QIODevice::ReadWrite);
    data >> temp;
    return temp;
}
void client::process()
{
    QByteArray* buffer = new QByteArray();
    qint32* s = new qint32(0);
    buffers.insert(socket, buffer);
    sizes.insert(socket, s);
}
void client::getResponseFromServer()
{
    process();

    QByteArray* buffer = buffers.value(socket);
    qint32* s = sizes.value(socket);
    qint32 size = *s;
    while (socket->bytesAvailable() > 0) {
        buffer->append(socket->readAll());
        while ((size == 0 && buffer->size() >= 4) || (size > 0 && buffer->size() >= size)) //While can process data, process it
        {
            if (size == 0 && buffer->size() >= 4) //jesli rozmiar dotarl zapisz
            {
                size = ArrayToInt(buffer->mid(0, 4));
                *s = size;
                buffer->remove(0, 4);
            }
            if (size > 0 && buffer->size() >= size) // jezeli doszly cale wyemiutuj
            {
                QByteArray data = buffer->mid(0, size);
                buffer->remove(0, size);
                size = 0;
                *s = size;

                QList<QByteArray> dane = data.split('|');
                QString check = dane.takeAt(0);

                if (check == "log") {
                    QString response = dane.takeAt(0);
                    if (response == "success") {
                        fileList = new FileList(this);
                        loginForm->close();
                        fileList->show();
                        logUser = dane.takeAt(0);
                        QString trash = dane.takeAt(0); //------------------------------------------------
                        QString trash2 = dane.takeAt(0); //-ZMIENNE USUWAJĄCE ZŁE ODP Z SERWERA-----------
                        QString trash3 = dane.takeAt(0); //-----------------------------------------------
                        fileList->updateAll(dane);
                        fileList->setLogin(logUser);
                        connect(fileList, SIGNAL(sendFile(QByteArray)), this, SLOT(sendFileToServer(QByteArray)));
                        connect(fileList, SIGNAL(getFile(QByteArray)), this, SLOT(downloadFromServer(QByteArray)));
                        connect(fileList, SIGNAL(delFile(QByteArray)), this, SLOT(deleteFromServer(QByteArray)));
                        QMessageBox::information(this, tr("Message of the client application"),
                            tr("User %1 logged in successfully!")
                                .arg(logUser));
                    }
                    else if (response == "error") {
                        QMessageBox::information(this, tr("Message of the client application"),
                            tr("Bad login or password"));
                    }
                }
                else if (check == "reg") {
                    QString login = dane.takeAt(0);
                    if (login != "") {
                        QString password = dane.takeAt(0);
                        QMessageBox::information(this, tr("Message of the client application"),
                            tr("User %1 registered successfully!\nHashed password: %2")
                                .arg(login)
                                .arg(password));
                    }
                }
                else if (check == "send") {

                    fileList = new FileList(this);
                    fileList->show();
                    fileList->setLogin(logUser);
                    connect(fileList, SIGNAL(sendFile(QByteArray)), this, SLOT(sendFileToServer(QByteArray)));
                    connect(fileList, SIGNAL(getFile(QByteArray)), this, SLOT(downloadFromServer(QByteArray)));
                    connect(fileList, SIGNAL(delFile(QByteArray)), this, SLOT(deleteFromServer(QByteArray)));
                    QString response = dane.takeAt(0);
                    QString trash = dane.takeAt(0); //------------------------------------------------
                    QString trash2 = dane.takeAt(0); //-ZMIENNE USUWAJĄCE ZŁE ODP Z SERWERA-----------
                    QString trash3 = dane.takeAt(0); //-----------------------------------------------
                    fileList->updateAll(dane);
                    if (response == "success") {
                        fileList->showSuccess();
                    }
                    else if(response == "deleted"){
                        fileList->showDeleted();
                    }
                    else {
                        fileList->showError();
                    }
                }
                else if (check == "get") {

                    QString login = dane.takeAt(0);
                    QString filename = dane.takeAt(0);
                    int toRemove = 4 + login.length() + 1 + filename.length() + 1;
                    if (login != "" && filename != "") {
                        FileManager* fm = new FileManager(this);
                        QFile* plik = new QFile(filename);
                        fm->createDirectory(login);
                        if (!plik->open(QIODevice::ReadWrite)) {
                        }
                        else {
                            QByteArray buffer = data.remove(0, toRemove);
                            plik->write(buffer);
                            plik->close();
                            fm->addFile(login, plik);
                        }
                    }
                }
            }
        }
    }
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
    qDebug() << registerString;
    QByteArray regArray;
    regArray.append(registerString);
    writeData(regArray);
}

void client::sendLoginData(QString loginString)
{
    qDebug() << loginString;
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

void client::on_disconnectClient_clicked()
{
    socket->disconnectFromHost();
    ui->logIn->setDisabled(1);
    ui->Register->setDisabled(1);
    ui->disconnectClient->setDisabled(1);
}

void client::on_connectTo_clicked()
{
    connectToServer();
    ui->Register->setEnabled(1);
    ui->logIn->setEnabled(1);
    ui->disconnectClient->setEnabled(1);
}
//Metoda wysylajaca dane do usuniecia z serwera
void client::deleteFromServer(QByteArray delString)
{
    writeData(delString);
}
