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

    if(!file.isOpen()){ //if the file isn't open, gives message
        qDebug("fileClosed - Write");
    }
}

bool fileManager::CheckValidUser(QString userName, QString fileName) { // used to see if the username is in the file
    nameFound = false; //double checks to make sure this variable is false
    QVector<QVector<QString>> content = ReadFile(fileName, 3); //assigns the items in the file iteration to the variable

    for(int i =0; i<content.size();i++) { //loops through content and stops when none left
        if(content.at(i).at(0)==userName) { //if the entered username matches any in the list, returns true
            nameFound=true;
            return false; //idk
        }
        else{
            continue; //if the name isn't found, it goes to the next col
        }
    }
    if(!nameFound){
        return true; //if it isn't found, exits
    }
    return false; //If it gets pass both checks (unlikely) it is gauranteed to return false
}


QVector<QVector<QString>> fileManager::ReadFile(QString fileName, int numCols) { //a vector of vectors of strings
    fileName.append(".csv"); //the file ending will be appened, so we only have to include the name
    QVector<QVector<QString>> columns; //init variable columns of type vector
    QVector<QString> rows; //init variable rows

    QFile file (fileName); //variable of file
    file.open(QIODevice::ReadOnly); //

    if(!file.isOpen()) { //if no file is opened, gives error message
        qDebug("No File Found");
        return columns;
    }

    QTextStream stream(&file); // var of type

    while (!stream.atEnd()){ //while the loop is not at the end of the stream

        QString str = stream.readLine(); //str is defined by everything in the file
        rows.append(str.split(",")); //breaks each row into indiv string
         for(int i=0; i< 3;i++){ //loop 3 times
           if(i == 2) {
                qDebug("Reach it 3");
                columns.append(rows); //adds an additional row to the vector
                rows.clear();
           }
       }
   }
    return columns;
}
