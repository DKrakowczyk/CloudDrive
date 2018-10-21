#include "serwer.h"
#include "ui_serwer.h"
 #include <QPushButton>
#include <stdlib.h>
#include <QtNetwork/qlocalserver.h>
#include <QtNetwork/qlocalsocket.h>
#include <QtNetwork>
#include <QTime>
#include <QPixmap>

serwer::serwer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::serwer)
{
    ui->setupUi(this);
    ui->server_name_field->setText("localhost");
    db_placeholder();

    //Uruchom serwer
    connect(ui->run_server, SIGNAL(clicked()),this,SLOT(run_server()));
    //Informacje o serwerze
    connect(ui->server_status, SIGNAL(clicked()),this,SLOT(show_server()));

    FileManager * fm = new FileManager(this);
    QFile * plik = new QFile("C:/Users/dariu/Documents/qt/serwer/build-serwer-Desktop_Qt_5_11_2_MinGW_32bit-Release/ui_serwer.h");
    fm->createDirectory("ryjek");
    fm->addFile("ryjek",plik);
    fm->changeName("ryjek","ui_serwer.h","judasz na patelni.h");
}


//----------------------------------SERWER----------------------------------
void serwer::run_server()
{
    server = new QLocalServer(this);
    if(!server->listen(ui->server_name_field->text()))
    {
        QMessageBox::critical(this,tr("Komunikat serwera danych"),
                              tr("Nie udało się uruchomić usługi: %1.")
                              .arg(server->errorString()));
    }
    else
    {
        QMessageBox::information(this,tr("Komunikat serwera danych"),
                              tr("Serwer uruchomiony: %1.")
                              .arg(server->serverName()));
    }
    time = QTime::currentTime().toString();

    //Dane udostępniane przez serwer
    dane << tr("SERWER DZIAŁA I ON TO WYSŁAŁ A NIE JAKAŚ PODRABIANA ZMIENNA");

    //Udostępnia dane
    connect(server, &QLocalServer::newConnection, this, &serwer::share_data);

    //Obie linijki poglądowe i do zmiany!
}

void serwer::show_server()
{
    QMessageBox::information(this,tr("Komunikat serwera danych"),
                          tr("Nazwa serwera: %1\nCzas uruchomienia: %2\n")
                                .arg(ui->server_name_field->text())
                                .arg(time));
}

void serwer::share_data()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);
    const QString message = dane.at(0);
    out<< quint32(message.size());
    out<< message;

    QLocalSocket *clientConnection = server->nextPendingConnection();
    connect(clientConnection, &QLocalSocket::disconnected,
            clientConnection, &QLocalSocket::deleteLater);

    clientConnection->write(block);
    clientConnection->flush();
    clientConnection->disconnectFromServer();

}

//----------------------------------OBSŁUGA PRZYCISKÓW----------------------------------
void serwer::on_actionLista_u_ytkownik_w_triggered()
{
    userList = new UserList(this);

    connect(userList,SIGNAL(closeWindow()),this,SLOT(showMainWindow()));
    ui->centralWidget->hide();
    userList->show();

}

void serwer::on_button_addDb_clicked()
{
    dbPath = QFileDialog::getOpenFileName(
                this,
                tr("Wybierz Bazę danych"),
                "../",
               "Pliki Bazy SQLITE (*.db)"

                );

    ui->dbPath->setText(dbPath);
    set_con_str(ui->dbPath->text());
    ui->serwer_info->setText("Dane zostaną zapisane..");
}

//----------------------------------OBSŁUGA BAZY DANYCH----------------------------------
void serwer::set_con_str(QString str)
{
    QFile file;
    file.setFileName("con_string.txt");

    if (file.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this,tr("Komunikat serwera"),tr("Pomyślnie zapisano ścieżkę bazy danych"));
        QTextStream stream (&file);
        stream << str;
    }
    file.close();
}

void serwer::db_placeholder()
{
    QFile file;
    file.setFileName("con_string.txt");

    if(file.open((QIODevice::ReadOnly)))
    {
        QTextStream in(&file);
        QString placeholder = in.readLine();

        if(placeholder != "")
        {
            ui->dbPath->setText(placeholder);
            ui->serwer_info->setText("Pomyślnie wczytano konfigurację!");
            QPixmap pic(":/db/db.png");
            ui->db_image->setPixmap(pic);
        }
        else
        {
            ui->dbPath->setText("Wybierz bazę danych...");
            ui->serwer_info->setText("Skonfiguruj serwer..");
            QPixmap pic(":/db/refresh.png");
            ui->db_image->setPixmap(pic);
        }
    }
    file.close();
}


void serwer::showMainWindow(){
    ui->centralWidget->show();
}

serwer::~serwer()
{
    delete ui;
}
