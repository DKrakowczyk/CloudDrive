#include "filemanager.h"

FileManager::FileManager(QObject* parent)
    : QObject(parent)
{
    directory = QDir::currentPath();
}

void FileManager::createDirectory(QString login)
{
    directory.mkdir(login);
}

void FileManager::addFile(QString login, QFile* file)
{
    QFileInfo fileInfo(file->fileName());
    QString newFilePath = QDir::currentPath() + "/" + login + "/" + fileInfo.fileName();
    qDebug() << " FILENAME: " << file->fileName() << "  | DIRNAME: " << QDir::currentPath() + "/" + login + "/" + fileInfo.fileName();
    QFile::copy(file->fileName(), newFilePath);
}

void FileManager::removeFile(QString login, QString name)
{
    QString FilePath = QDir::currentPath() + "/" + login + "/" + name;
    QFile::remove(FilePath);
}

void FileManager::changeName(QString login, QString oldName, QString newName)
{
    QString FilePath = QDir::currentPath() + "/" + login + "/" + oldName;
    QString newNamePath = QDir::currentPath() + "/" + login + "/" + newName;
    QFile::rename(FilePath, newNamePath);
}
