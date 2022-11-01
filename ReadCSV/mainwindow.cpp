#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLineEdit>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QLineEdit* userField = ui->userField;
    userField->setPlaceholderText("Insert Username Here");

    QLineEdit* passField = ui->passField;
    passField->setPlaceholderText("Insert Password Here");
    passField->setEchoMode(QLineEdit::EchoMode::Password);
    //add button to hide/show password

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_signIn_clicked() {
    QLineEdit* userField = ui->userField;
    QLineEdit* passField = ui->passField;

    QVector<QVector<QString>> fileContent = fManager.ReadFile("LoginInformation", 3); //.csv extension is being appended at the other end

    for(int i= 0; i<fileContent.size(); i++) {
        if(userField->text() == fileContent.at(i).at(0)) {
            if(passField->text() == fileContent.at(i).at(1)) { //column 1 (2nd column) contains the password, checks if it is true
               signedIn= true; //if passwords match, log in is successful
                QMessageBox::information(this, "login", "You have successfully logged in"); //informs user
            }
            else {
                QMessageBox::warning(this, "Login", "Incorrect Password"); //if the password doesn't match, gives warning
            }
        }
        else{
            continue; //goes to next col to check
        }
    }
    if(!signedIn){
        QMessageBox::warning(this, "Login", "User not found"); //if the login is not complete, issues warning
    }
}

void MainWindow::on_signUp_clicked(){ //when the button is clicekd
    QLineEdit* userField = ui->userField; //assgins the text in userfield to the variable of userField
    QLineEdit* passField = ui->passField; //same as above but ofr passfield
    QVector<QString> content; //init var

    content.append(userField->text());
    content.append(passField->text());
    content.append("1");

    if(fManager.CheckValidUser(userField->text(), "LoginInformation")){ //
        fManager.WriteFile("LoginInformation", content);

        QMessageBox box(this);
        box.setIcon(QMessageBox::Information);
        box.setText("You have successfully signed up");
        box.setWindowTitle("Sign up");
        box.setStandardButtons(QMessageBox::Ok);
        int returnVal=box.exec();
        switch (returnVal) {
        case QMessageBox::Ok:
            OpenWindow();
            break;
        default:
            break;
        }
    }
    else {
        QMessageBox::warning(this, "sign up", "User with this name already exists");
    }
}

void MainWindow::OpenWindow() {
    qDebug("Function has been called");
}


