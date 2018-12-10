#ifndef USERREGISTER_H
#define USERREGISTER_H

#include <QWidget>

namespace Ui {
class userRegister;
}

class userRegister : public QWidget
{
    Q_OBJECT

public:
    explicit userRegister(QWidget *parent = nullptr);
    ~userRegister();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::userRegister *ui;

signals:
    void registerUser(QString);
};

#endif // USERREGISTER_H
