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
    void setFields(QString,QString,QString);
private slots:
    void on_buttonReject_clicked();

    void on_buttonDelete_clicked();

private:
    Ui::userEditForm *ui;
    QString id,login,password;
    void setLabels();

signals:
    void deleteSignal();
};

#endif // USEREDITFORM_H
