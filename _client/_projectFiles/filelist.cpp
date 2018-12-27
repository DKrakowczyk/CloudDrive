#include "filelist.h"
#include "ui_filelist.h"
#include "client.h"
FileList::FileList(QWidget* parent)
    : QWidget(parent, Qt::Window)
    , ui(new Ui::FileList)
{
    ui->setupUi(this);
    QPixmap pic(":/client/list.png");
    ui->listIcon->setPixmap(pic);
}

FileList::~FileList()
{
    delete ui;
}

void FileList::on_logoutButton_clicked()
{
    QMessageBox::information(this, tr("Message of the client application"),
        tr("Logged out successfully."));

    this->close();
}

void FileList::setLogin(QString log)
{
    login = log;
    ui->loginLabel->setText("Hello: " + login);
}
void FileList::updateAll(QList<QByteArray> lista)
{
    foreach (QString files, lista) {
        if (files != "") {
            ui->listWidget->addItem(files);
        }
    }
}
void FileList::showSuccess()
{
    QMessageBox::information(this, tr("Message of the client application"),
        tr("The file has been successfully sent."));
}
void FileList::showError()
{
    QMessageBox::critical(this, tr("Message of the client application"),
        tr("There was a problem with uploading the file."));
}
void FileList::showDeleted()
{
    QMessageBox::information(this, tr("Message of the client application"),
        tr("The file has been successfully removed from server."));
}
void FileList::on_addFileButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Choose files"), "../", "All files (*)");
    QByteArray buffer;
    QFile* file = new QFile(filePath);
    if (!file->open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Message of the client application"),
            tr("Cannot open the file"));
    }
    else {
        buffer = file->readAll(); //w zmiennej buffer zapisany plik
        QFileInfo fileInfo(file->fileName());
        QString filename(fileInfo.fileName());
        qDebug() << filename;
        QByteArray fileToSend;
        fileToSend.append("send|" + login + "|" + filename + "|"); //send|login|filename
        fileToSend.append(buffer); //dodanie pliku
        emit sendFile(fileToSend); //wyemitowanie sygnalu z kompletnym plikiem
        file->close();

        this->close();
    }
}

void FileList::on_downloadButton_clicked()
{
    QString filename = ui->listWidget->currentItem()->text();
    QByteArray downloadString;
    downloadString.append("get|" + login + "|" + filename + "|");
    emit getFile(downloadString);
    qDebug() << downloadString;
    QMessageBox::information(this, tr("Message of the client application"),
        tr("The file has been successfully downloaded."));
}

void FileList::on_delButton_clicked()
{
    QString filename = ui->listWidget->currentItem()->text();
        if(filename!="")
        {
        QByteArray downloadString;
        downloadString.append("del|"+login+"|"+filename+"|");
        emit delFile(downloadString);
        qDebug() << downloadString;
        this->close();
        }
}
