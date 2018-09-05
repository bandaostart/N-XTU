#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPalette>
#include <QColorDialog>
#include <QColor>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPalette color_pal(ui->comboBox->palette());
    color_pal.setColor(QPalette::Window, QColor(0, 255, 0));
    ui->comboBox->setPalette(color_pal);
    ui->comboBox->update();

//    color_pal.setColor(QPalette::ButtonText, QColor(0, 255, 0));
//    ui->colorButton->setAutoFillBackground(true);
//    ui->colorButton->setPalette(color_pal);


//    QPalette button_pal(ui->textEdit->palette());
//    button_pal.setColor(QPalette::Base, Qt::blue);
//    ui->textEdit->setAutoFillBackground(true);
//    ui->textEdit->setPalette(button_pal);
//    ui->textEdit->setStyleSheet("background-color: rgb(170, 0, 255)");
}

MainWindow::~MainWindow()
{
    delete ui;
}
