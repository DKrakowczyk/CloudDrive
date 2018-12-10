#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QDebug>
class FileManager : public QObject
{
    Q_OBJECT
public:
    explicit FileManager(QObject *parent = nullptr);
    void createDirectory(QString);
    QFile returnFile(QString,QString);
    void addFile(QString,QFile*);
    void removeFile(QString,QString);
    void changeName(QString,QString,QString);
private:
QDir directory;
signals:

public slots:
};

#endif // FILEMANAGER_H
