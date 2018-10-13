#ifndef SERWER_H
#define SERWER_H

#include <QMainWindow>
#include <QMessageBox>
#include "UserList.h"
#include <QFileDialog>
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

private:
    Ui::serwer *ui;
    QLocalServer *server;
    QStringList dane;
    QString time;
    UserList * userList;
    QString dbPath;
public slots:
    void showMainWindow();
private slots:
    void run_server();
    void show_server();
    void on_actionLista_u_ytkownik_w_triggered();
    void on_button_addDb_clicked();
};

#endif // SERWER_H
