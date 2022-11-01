#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "filemanager.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_signIn_clicked();

    void on_signUp_clicked();

private:
    Ui::MainWindow *ui;
    fileManager fManager;
    bool signedIn=false;\
    void OpenWindow();
};
#endif // MAINWINDOW_H
