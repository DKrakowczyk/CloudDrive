#include "serwer.h"
#include "ui_serwer.h"
 #include <QPushButton>
#include <stdlib.h>
#include <QtNetwork/qlocalserver.h>
#include <QtNetwork/qlocalsocket.h>
#include <QtNetwork>
#include <QTime>

serwer::serwer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::serwer)
{
    ui->setupUi(this);
    ui->server_name_field->setText("localhost");
    //Uruchom serwer
    connect(ui->run_server, SIGNAL(clicked()),this,SLOT(run_server()));
    connect(ui->server_status, SIGNAL(clicked()),this,SLOT(show_server()));
}


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
}

void serwer::show_server()
{
    QMessageBox::information(this,tr("Komunikat serwera danych"),
                          tr("Nazwa serwera: %1\nCzas uruchomienia: %2")
                             .arg(ui->server_name_field->text())
                                .arg(time));
}

serwer::~serwer()
{
    delete ui;
}
