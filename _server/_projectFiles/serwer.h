#ifndef SERWER_H
#define SERWER_H

#include <QMainWindow>
#include <QMessageBox>
#include "UserList.h"
#include <QFileDialog>
#include <QtNetwork>
#include "filemanager.h"
QT_BEGIN_NAMESPACE
class QLocalServer;
QT_END_NAMESPACE

namespace Ui {
class serwer;
}

class serwer : public QMainWindow
{
    Q_OBJECT
public:
    explicit serwer(QWidget *parent = nullptr);
    ~serwer();
    QByteArray shareFileNames(QString);
private:
    QSqlDatabase mydb;
    Ui::serwer *ui;
    QTcpServer *server;
    QStringList dane;
    QString time;
    UserList *userList;
    QString dbPath;
    QHash<QTcpSocket*, QByteArray*> buffers;
    QHash<QTcpSocket*, qint32*> sizes;
public slots:
    void showMainWindow();
    void set_con_str(QString);
    void db_placeholder();
    void share_data(QByteArray);
private slots:
    void onNewConnection();
    void show_server();
    void on_actionLista_u_ytkownik_w_triggered();
    void on_button_addDb_clicked();
    void newServerConnection();
    void disconnected();
    void readyRead();
    void on_stop_server_clicked();
    void chooseAction(QByteArray);
signals:
    void logged();
};

#endif // SERWER_H
