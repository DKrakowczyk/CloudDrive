#ifndef USEREDITFORM_H
#define USEREDITFORM_H

#include <QWidget>
namespace Ui {
class userEditForm;
}

class userEditForm : public QWidget
{
    Q_OBJECT

public:
    explicit userEditForm(QWidget *parent = nullptr);
    ~userEditForm();
    void setFields(QString,QString);
    QString getLogin();
    QString getpassword();
private slots:
    void on_buttonReject_clicked();

    void on_buttonDelete_clicked();

    void on_buttonAccept_clicked();

private:
    Ui::userEditForm *ui;
    QString login,password;
    void setLabels();

signals:
    void deleteSignal();
    void changeSignal();
};

#endif // USEREDITFORM_H
