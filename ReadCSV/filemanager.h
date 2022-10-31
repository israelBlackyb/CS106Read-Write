#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QVector>

class fileManager
{
public:
    fileManager();
    QVector<QVector<QString>> ReadFile(QString fileName, int numCols);
    void WriteFile(QString fileName, QVector<QString> fileContent);
    bool CheckValidUser(QString username, QString fileName);

private:
    bool nameFound= false;
};

#endif // FILEMANAGER_H
