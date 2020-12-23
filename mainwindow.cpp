#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QDir>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Adaptar el tamano de plainTextEdit al de la ventana
    setCentralWidget(ui->plainTextEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_triggered()
{
    QFile file;
    QTextStream input;
    QString nameFile;
    nameFile = QFileDialog::getOpenFileName(this, "Open");
    if(nameFile.isEmpty()) return;
    file.setFileName(nameFile);
    file.open(QIODevice::Text | QIODevice::ReadOnly);
    if(!file.isOpen()){
        QMessageBox::critical(this, "Error", file.errorString());
        return;
    }
    input.setDevice(&file);
    ui->plainTextEdit->setPlainText(input.readAll());
    file.close();
}

void MainWindow::on_actionSave_as_triggered()
{
    QFile file;
    QTextStream output;
    QString nameFile;
    nameFile = QFileDialog::getSaveFileName(this, "Save As...");
    if(nameFile.isEmpty()) return;
    file.setFileName(nameFile);
    file.open((QIODevice::Text | QIODevice::WriteOnly));
    if(!file.isOpen()){
        QMessageBox::critical(this, "Error", file.errorString());
        return;
    }
    output.setDevice(&file);
    output<<ui->plainTextEdit->toPlainText();
    file.flush();
    file.close();
}

void MainWindow::on_actionCut_triggered()
{
    ui->plainTextEdit->cut();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->plainTextEdit->paste();
}

void MainWindow::on_actionAbout_triggered()
{
    QString cadena = "Notes\nVersion 1.0\n";
    QMessageBox::information(this, "About", cadena);
}

void MainWindow::on_actionCopy_triggered()
{
    ui->plainTextEdit->copy();
}

void MainWindow::on_actionClose_triggered()
{
    close();
}

void MainWindow::on_actionNew_triggered()
{
    ui->plainTextEdit->setPlainText("");
}
