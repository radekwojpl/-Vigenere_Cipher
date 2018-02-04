#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <codevigenera.h>
#include <QString>
#include <QChar>
#include <QDebug>
#include <QInputDialog>
#include <thread>
#include <future>
#include <iostream>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    void writeToFile(QString, QString);
    void readFromFile(CodeVigenera&);
    CodeVigenera wordToEncrypt;
    CodeVigenera wordToDecrypt;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_Encrypte_clicked();

    void on_pushButton_Decrypt_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
