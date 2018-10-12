#ifndef SERWER_H
#define SERWER_H

#include <QMainWindow>
#include <QMessageBox>

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

private slots:
    void run_server();
    void show_server();
};

#endif // SERWER_H
