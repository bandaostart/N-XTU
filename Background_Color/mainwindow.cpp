#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPalette>
#include <QColorDialog>
#include <QColor>
#include <QPainter>
#include <QPen>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    color.setRgb(102, 102, 102);

    QString str = "";
    str = "border: 4px solid rgb(208,208,208);border-radius: 6px;background-color: rgb(";
    str += QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+")";
    ui->colorButton->setStyleSheet(str);

    color_pal = this->palette();
    color_pal.setColor(QPalette::Background, color);
    this->setAutoFillBackground(true);
    this->setPalette(color_pal);


//    ui->colorButton->setStyleSheet(" background-color: qlineargradient(x1: 4, y1: 4, x2: 8, y2: 8, stop: 0  rgb(170, 0, 255), stop: 1  rgb(170, 0, 255));min-width: 40px;");
//    QPalette button_pal(ui->textEdit->palette());
//    button_pal.setColor(QPalette::Base, Qt::blue);
//    ui->textEdit->setAutoFillBackground(true);
//    ui->textEdit->setPalette(button_pal);
//    ui->textEdit->setStyleSheet("background-color: rgb(170, 0, 255)");
//    color_pal.setColor(QPalette::Button, color);
//    ui->colorButton->setAutoFillBackground(true);
//    ui->colorButton->setPalette(color_pal);
//    ui->colorButton->setFlat(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_colorButton_clicked()
{
    QColorDialog color_dialog(color, this);

    if (color_dialog.exec() == QDialog::Accepted)
    {
        color = color_dialog.currentColor();

        QString str = "";
        str = "border: 4px solid rgb(208,208,208);border-radius: 6px;background-color: rgb(";
        str += QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+")";
        ui->colorButton->setStyleSheet(str);

        color_pal.setColor(QPalette::Background, color);
        this->setPalette(color_pal);
    }
}

void MainWindow::on_pushButton_clicked()
{

    color.setRgb(102, 102, 102);

    QString str = "";
    str = "border: 4px solid rgb(208,208,208);border-radius: 6px;background-color: rgb(";
    str += QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+")";
    ui->colorButton->setStyleSheet(str);

    color_pal.setColor(QPalette::Background, color);
    this->setPalette(color_pal);
}


void MainWindow::paintEvent(QPaintEvent *event)
{
     Q_UNUSED(event);

//    QPainter painter(this);
//    // 反走样
//    painter.setRenderHint(QPainter::Antialiasing, true);
//    // 设置画笔颜色、宽度
//    painter.setPen(QPen(QColor(0, 160, 230), 2));
//    // 设置画刷颜色
//    painter.setBrush(QColor(255, 160, 90));
//    painter.drawRect(50, 50, 160, 100);
}

