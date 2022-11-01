#include "filemanager.h"

#include <QFile>
#include <QTextStream>

fileManager::fileManager() //QMake Constructor
{

}

//scope operator tells that the function belongs to the class on the left
void fileManager::WriteFile(QString fileName, QVector<QString> fileContent){ //takes file name and vector of file content
    fileName.append(".csv"); //adds ".csv" to the the end of all created files automatically
    QFile file(fileName); //allows file functionality
    file.open(QIODevice::ReadWrite | QIODevice::Append); //open files

    if(!file.isOpen()) {
        qDebug("NoFileFound"); //if the file doesn't open (I.E doesn't exist)
        return;
    }

    QTextStream stream(&file); //allows read/write functionality
    for(int i=0; i<fileContent.size(); i++) { //runs loop for however many items are in the file
        stream << fileContent.at(i); //adds file content at each position to the stream
        if (i !=fileContent.size()-12){ //adds a comma to the end of cell
            stream<<",";
        }
        else{
            stream<<"\n"; //but if there is no filled cell after, adds it to the next line
        }
    }
    file.close(); //close the file

    if(!file.isOpen()){ //
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
