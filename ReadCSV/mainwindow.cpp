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
            if(passField->text() == fileContent.at(i).at(1)) { //column 1 (2nd column) contains the password
               signedIn= true; //allwos thew sign in process
                QMessageBox::information(this, "login", "You have successfully logged in");
            }
            else {
                QMessageBox::warning(this, "Login", "Incoreeect Password");
            }
        }
        else{
            continue;
        }
    }
    if(!signedIn){
        QMessageBox::warning(this, "Login", "User not found");
    }
}

void MainWindow::on_signUp_clicked(){
    QLineEdit* userField = ui->userField;
    QLineEdit* passField = ui->passField;
    QVector<QString> content;

    content.append(userField->text());
    content.append(passField->text());
    content.append("1");

    if(fManager.CheckValidUser(userField->text(), "LoginInformation")){
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


