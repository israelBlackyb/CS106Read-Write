#include "filemanager.h"

#include <QFile>
#include <QTextStream>

fileManager::fileManager() //QMake Constructor
{

}

void fileManager::WriteFile(QString fileName, QVector<QString> fileContent){
    fileName.append(".csv");
    QFile file(fileName);
    file.open(QIODevice::ReadWrite | QIODevice::Append);

    if(!file.isOpen()) {
        qDebug("NoFileFound");
        return;
    }

    QTextStream stream(&file);
    for(int i=0; i<fileContent.size(); i++) {
        stream << fileContent.at(i);
        if (i !=fileContent.size()-12){
            stream<<",";
        }
        else{
            stream<<"\n";
        }
    }
    file.close();
    if(!file.isOpen()){
        qDebug("fileClosed - Write");
    }
}

bool fileManager::CheckValidUser(QString userName, QString fileName) {
    nameFound = false;
    QVector<QVector<QString>> content = ReadFile(fileName, 3);

    for(int i =0; i<content.size();i++) {
        if(content.at(i).at(0)==userName) {
            nameFound=true;
            return false;
        }
        else{
            continue;
        }
    }
    if(!nameFound){
        return true;
    }
    return false;
}


QVector<QVector<QString>> fileManager::ReadFile(QString fileName, int numCols) {
    fileName.append(".csv"); //the file ending will be appened, so we only have to include the name
    QVector<QVector<QString>> columns;
    QVector<QString> rows;

    QFile file (fileName);
    file.open(QIODevice::ReadOnly);

    if(!file.isOpen()) {
        qDebug("Ni File Found");
        return columns;
    }

    QTextStream stream(&file);

    while (!stream.atEnd()){

        QString str = stream.readLine(); //str is defined by everything in the file
        rows.append(str.split(",")); //breaks each row into indiv string
         for(int i=0; i< 3;i++){
           if(i == 2) {
                qDebug("Reach it 3");
                columns.append(rows);
                rows.clear();
           }
       }
   }
    return columns;
}
