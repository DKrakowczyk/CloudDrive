#include "serwer.h"
#include "ui_serwer.h"

#include <QPushButton>
#include <stdlib.h>
#include <QtNetwork/qlocalserver.h>
#include <QtNetwork/qlocalsocket.h>
#include <QtNetwork>
#include <QTime>
#include <QPixmap>
static inline qint32 ArrayToInt(QByteArray source);

serwer::serwer(QWidget* parent)
    : QMainWindow(parent)
    ,

    ui(new Ui::serwer)
{
    server = new QTcpServer(this);
    ui->setupUi(this);
    ui->server_name_field->setText("localhost");
    ui->actionLista_u_ytkownik_w->setDisabled(1);
    db_placeholder();

    //Uruchom serwer
    connect(ui->run_server, SIGNAL(clicked()), this, SLOT(newServerConnection()));
    //Informacje o serwerze
    connect(ui->server_status, SIGNAL(clicked()), this, SLOT(show_server()));
    connect(server, SIGNAL(newConnection()), SLOT(onNewConnection()));
    //    FileManager * fm = new FileManager(this);
    //    QFile * plik = new QFile("C:/Users/dariu/Documents/qt/serwer/build-serwer-Desktop_Qt_5_11_2_MinGW_32bit-Release/ui_serwer.h");
    //    fm->createDirectory("ryjek");
    //    fm->addFile("ryjek",plik);
    //    fm->changeName("ryjek","ui_serwer.h","judasz na patelni.h");
}

void serwer::chooseAction(QByteArray data)
{
    QByteArray analyze = data;
    QList<QByteArray> dane = analyze.split('|');
    QString check = dane.takeAt(0);
    BazaDanych* baza = new BazaDanych("QSQLITE", ui->dbPath->text());

        if (check == "log")
        {
            QByteArray login = dane.takeAt(0);
            QByteArray password = dane.takeAt(0); //poprzednie wywolanie wyciaga QByteArray i ten staje sie 1

        }
        else if(check == "reg")
        {
                QString login = dane.takeAt(0);
                QString password = dane.takeAt(0);
                if (login != "" && password != "")
                {
                    qDebug()<<"login:"+login+"password"+password;
                    QByteArray response;
                    response.append("reg|"+login+"|"+password);
                    baza->addUser(login,password);
                    share_data(response);

                }
         }
        else if(check== "send")
        {

        }
        else if(check=="get")
        {

        }
}
void serwer::share_data(QByteArray response)
{
    QTcpSocket *user = (QTcpSocket*)sender();
    QByteArray block;
    block.append(response);
    user->write(block);
}
//----------------------------------SERWER----------------------------------
void serwer::newServerConnection()
{

    if (!server->listen((QHostAddress)ui->server_name_field->text(), ui->server_port->text().toInt())) {
        QMessageBox::critical(this, tr("Komunikat serwera danych"),
            tr("Nie udało się uruchomić usługi: %1.")
                .arg(server->errorString()));
    }
    else {
        QMessageBox::information(this, tr("Komunikat serwera danych"),
            tr("Serwer uruchomiony: %1.")
                .arg(ui->server_name_field->text()));

        //Kontrola inputow
        ui->stop_server->setEnabled(1);
        ui->server_status->setEnabled(1);
        ui->run_server->setDisabled(1);
        ui->server_name_field->setDisabled(1);
        ui->server_port->setDisabled(1);
        ui->button_addDb->setDisabled(1);
        ui->dbPath->setDisabled(1);
        ui->actionLista_u_ytkownik_w->setEnabled(1);
    }
    time = QTime::currentTime().toString();
}

void serwer::onNewConnection()
{
    while (server->hasPendingConnections()) {
        QTcpSocket* socket = server->nextPendingConnection();
        connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
        QByteArray* buffer = new QByteArray();
        qint32* s = new qint32(0);
        buffers.insert(socket, buffer);
        sizes.insert(socket, s);
    }
}

void serwer::disconnected()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray *buffer = buffers.value(socket);
    qint32 *s = sizes.value(socket);
    socket->deleteLater();
    delete buffer;
    delete s;
}

void serwer::readyRead()
{
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
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
                chooseAction(data);
                qDebug() << data;
            }
        }
    }

}
qint32 ArrayToInt(QByteArray source)
{
    qint32 temp;
    QDataStream data(&source, QIODevice::ReadWrite);
    data >> temp;
    return temp;
}
void serwer::show_server()
{
    QMessageBox::information(this, tr("Komunikat serwera danych"),
        tr("Nazwa serwera: %1\nPort: %2\nCzas uruchomienia: %3\n")
            .arg(ui->server_name_field->text())
            .arg(ui->server_port->text())
            .arg(time));
}

//----------------------------------OBSŁUGA PRZYCISKÓW----------------------------------
void serwer::on_actionLista_u_ytkownik_w_triggered()
{
    userList = new UserList(this);
    connect(userList, SIGNAL(closeWindow()), this, SLOT(showMainWindow()));
    ui->centralWidget->hide();
    userList->show();
}

void serwer::on_button_addDb_clicked()
{
    dbPath = QFileDialog::getOpenFileName(
        this,
        tr("Wybierz Bazę danych"),
        "../",
        "Pliki Bazy SQLITE (*.db)");

    ui->dbPath->setText(dbPath);
    set_con_str(ui->dbPath->text());
    ui->serwer_info->setText("Dane zostaną zapisane..");
}
void serwer::on_stop_server_clicked()
{
    server->close();
    if (!server->isListening()) {
        QMessageBox::information(this, tr("Komunikat serwera danych"),
            tr("Serwer zatrzymany: %1.")
                .arg(ui->server_name_field->text()));
    }
    //Kontrola inputow
    ui->stop_server->setDisabled(1);
    ui->server_status->setDisabled(1);
    ui->run_server->setEnabled(1);
    ui->server_name_field->setEnabled(1);
    ui->server_port->setEnabled(1);
    ui->button_addDb->setEnabled(1);
    ui->dbPath->setEnabled(1);
}

//----------------------------------OBSŁUGA BAZY DANYCH----------------------------------
void serwer::set_con_str(QString str)
{
    QFile file;
    file.setFileName("con_string.txt");

    if (file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Komunikat serwera"), tr("Pomyślnie zapisano ścieżkę bazy danych"));
        QTextStream stream(&file);
        stream << str;
    }
    file.close();
}

void serwer::db_placeholder()
{
    QFile file;
    file.setFileName("con_string.txt");

    if (file.open((QIODevice::ReadOnly))) {
        QTextStream in(&file);
        QString placeholder = in.readLine();

        if (placeholder != "") {
            ui->dbPath->setText(placeholder);
            ui->serwer_info->setText("Pomyślnie wczytano konfigurację!");
            QPixmap pic(":/db/db.png");
            ui->db_image->setPixmap(pic);
        }
        else {
            ui->dbPath->setText("Wybierz bazę danych...");
            ui->serwer_info->setText("Skonfiguruj serwer..");
            QPixmap pic(":/db/refresh.png");
            ui->db_image->setPixmap(pic);
        }
    }
    file.close();
}

void serwer::showMainWindow()
{
    ui->centralWidget->show();
}

serwer::~serwer()
{
    delete ui;
}

