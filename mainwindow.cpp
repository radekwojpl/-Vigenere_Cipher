#include "mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::writeToFile(QString wordToSave, QString keyWord)
{
    QString filename ="C:/Users/radek/Documents/SzyfrowanieTekstu/new.txt";
    QFile file(filename);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << wordToSave<<endl<<keyWord ;
    }
}

void MainWindow::readFromFile(CodeVigenera &obj)
{
    QString filename ="C:/Users/radek/Documents/SzyfrowanieTekstu/new.txt";
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Something wrong with file!";
       return;
    }

    QString w = file.readLine();
    w = w.left(w.length()-1);
    obj.setPhrase(w);
    QString z = file.readLine();
    z = z.left(z.length());
    obj.setKeyWord(z);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Encrypte_clicked()
{
    wordToEncrypt.setPhrase(ui->lineEdit->text());
    QString word = QInputDialog::getText(this, "KEY WORD","KEY WORD");
    if(word.isEmpty())
        return;
    wordToEncrypt.setKeyWord(word);
    wordToEncrypt.setMultipleKeyWord( wordToEncrypt.generateMultipleKeyWord(wordToEncrypt.getPhrase(),wordToEncrypt.getKeyWord()));
    wordToEncrypt.encrypt();
    writeToFile(wordToEncrypt.getEncryptedWord(), wordToEncrypt.getKeyWord());

}

void MainWindow::on_pushButton_Decrypt_clicked()
{
     readFromFile(wordToDecrypt);
     wordToDecrypt.setKeyWord(wordToDecrypt.generateReverseKeyWord(wordToDecrypt.getKeyWord()));
     qDebug()<<wordToDecrypt.getPhrase()<<wordToDecrypt.getKeyWord();
     wordToDecrypt.setMultipleKeyWord( wordToDecrypt.generateMultipleKeyWord(wordToDecrypt.getPhrase(),wordToDecrypt.getKeyWord()));
     wordToDecrypt.encrypt();
     writeToFile(wordToDecrypt.getEncryptedWord(), wordToDecrypt.getKeyWord());
}
