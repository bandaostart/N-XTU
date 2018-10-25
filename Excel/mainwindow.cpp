#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAxObject>
#include <QDir>
#include <QFileInfo>
#include <QDateTime>
#include <QDate>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //新建对象
    Excel = new QAxObject(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



//连接控件
void MainWindow::on_pushButton_clicked()
{
    //连接Excel控件
    Excel->setControl("Excel.Application");

    //设置窗体是否显示 true: 显示 false：不显示
    //Excel->setProperty("Visible", false);

    //不显示任何警告信息，如果为true 那么关闭的时候回出现“文件保存”等类似信息
    Excel->setProperty("DisplayAlerts", false);
}



//打开工作薄集合
void MainWindow::on_pushButton_2_clicked()
{
    //获取工作薄集合
    WorkBooks = Excel->querySubObject("WorkBooks");
}




//创建一个新工作薄
void MainWindow::on_pushButton_3_clicked()
{
    WorkBooks->dynamicCall("Add"); // 新建一个工作簿
    WorkBook = Excel->querySubObject("ActiveWorkBook"); // 获取当前工作簿
}



//打开一个存在的工作薄
void MainWindow::on_pushButton_4_clicked()
{
    QDate       Current_Time;
    QDir        Dir;
    QFileInfo   FileInfo;
    QString     WorkPath;

    //获取当前时间
    Current_Time = QDate::currentDate();

    //获取工作路径
    WorkPath = Dir.currentPath();
    WorkPath += "/";
    WorkPath += (QString("%1").arg(Current_Time.year(),  4, 10, QLatin1Char('0')).toUpper()+"-");
    WorkPath += (QString("%1").arg(Current_Time.month(), 2, 10, QLatin1Char('0')).toUpper()+"-");
    WorkPath += (QString("%1").arg(Current_Time.day(),   2, 10, QLatin1Char('0')).toUpper());
    WorkPath += ".xlsx";


    //打开工作薄 如果存在打开如果不存在关闭
    FileInfo.setFile(WorkPath);
    if (FileInfo.isFile())
    {
        WorkBook = WorkBooks->querySubObject("Open(const QString&)", WorkPath);
    }
    else
    {
        WorkBooks->dynamicCall("Add"); // 新建一个工作簿
        WorkBook = Excel->querySubObject("ActiveWorkBook"); // 获取当前工作簿
    }



//    ui->textEdit->insertPlainText(WorkPath);
//    ui->textEdit->insertPlainText("\n\n");
//    ui->textEdit->moveCursor(QTextCursor::End);
}



//保存工作薄
void MainWindow::on_pushButton_5_clicked()
{
    QDate       Current_Time;
    QDir        Dir;
    QString     WorkPath;

    //获取当前时间
    Current_Time = QDate::currentDate();

    //获取工作路径
    WorkPath = Dir.currentPath();
    WorkPath += "/";
    WorkPath += (QString("%1").arg(Current_Time.year(),  4, 10, QLatin1Char('0')).toUpper()+"-");
    WorkPath += (QString("%1").arg(Current_Time.month(), 2, 10, QLatin1Char('0')).toUpper()+"-");
    WorkPath += (QString("%1").arg(Current_Time.day(),   2, 10, QLatin1Char('0')).toUpper());
    WorkPath += ".xlsx";



    //保存文件
    //WorkBook->dynamicCall("Save()");

    //另存为文件
    WorkBook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(WorkPath));



    WorkBook->dynamicCall("Close(Boolean)", false); //关闭文件
    Excel->dynamicCall("Quit(void)");              //关闭exce
    delete Excel;
}


//打开一个sheet
void MainWindow::on_pushButton_6_clicked()
{
    //获取所有的Sheets
    WorkSheets = WorkBook->querySubObject("Sheets");

    //获取第一个Sheet
    WorkSheet = WorkSheets->querySubObject("Item(int)",1);

    //另一种方式
    //QAxObject* worksheet = workbook->querySubObject("WorkSheets(int)", 1);
}




//获取工作表的行数和列数
void MainWindow::on_pushButton_7_clicked()
{
    //获取Sheet范围
    QAxObject *UsedRange = WorkSheet->querySubObject("UsedRange");

    //获取行
    WorkRow = UsedRange->querySubObject("Rows");

    //获取列
    WorkColumn = UsedRange->querySubObject("Columns");

    //起始行
    StartRow = UsedRange->property("Row").toInt();

    //起始列
    StartColumn = UsedRange->property("Column").toInt();

    //行个数
    AllRowsNum = WorkRow->property("Count").toInt();

    //列个数
    AllColumnsNum = WorkRow->property("Count").toInt();


    QString str= "";

    str += "AllRowNum: ";
    str += QString::number(AllRowsNum);

    str += "; AllRowColumn: ";
    str += QString::number(AllColumnsNum);

    str += "; StartRow: ";
    str += QString::number(StartRow);

    str += "; StartColumn: ";
    str += QString::number(StartColumn);

    ui->textEdit->insertPlainText(str);
    ui->textEdit->insertPlainText("\n\n");
    ui->textEdit->moveCursor(QTextCursor::End);
}


//写单元格数据
void MainWindow::on_pushButton_8_clicked()
{
    //获取单元格-基于坐标
    QAxObject* cell_1 = WorkSheet->querySubObject("Cells(int, int)", StartRow, StartColumn);

    //获取单元格-基于行列名称
    QAxObject* cell_2 = WorkSheet->querySubObject("Range(QVariant, QVariant)", "A2");
    QAxObject* cell_3 = WorkSheet->querySubObject("Range(QVariant, QVariant)", "B1");
    QAxObject* cell_4 = WorkSheet->querySubObject("Range(QVariant, QVariant)", "B2");

    //写入内容-方式1
    cell_1->setProperty("Value", QVariant("0001020304050607"));


    //写入内容方式2
    cell_2->dynamicCall("SetValue(conts QVariant&)", "08090A0B0C0D0E0F");
    cell_3->dynamicCall("SetValue(conts QVariant&)", "0001020304050607");
    cell_4->dynamicCall("SetValue(conts QVariant&)", "08090A0B0C0D0E0F");
}


//读取单元格数据
void MainWindow::on_pushButton_9_clicked()
{
    QString str;

    //获取单元格-基于坐标
    QAxObject* cell_1 = WorkSheet->querySubObject("Cells(int, int)", StartRow, StartColumn);

    //获取单元格-基于行列名称
    QAxObject* cell_2 = WorkSheet->querySubObject("Range(QVariant, QVariant)", "A2");


    //读取内容-方式1
    str = cell_1->property("Value").toString();
    ui->textEdit->insertPlainText(str);
    ui->textEdit->insertPlainText("\n\n");
    ui->textEdit->moveCursor(QTextCursor::End);


    //读取内容-方式2
    str = cell_2->dynamicCall("Value()").toString();
    ui->textEdit->insertPlainText(str);
    ui->textEdit->insertPlainText("\n\n");
    ui->textEdit->moveCursor(QTextCursor::End);

}


//设置单元格格式
void MainWindow::on_pushButton_10_clicked()
{
    //设置字体颜色和宽度
    QAxObject* font;
    QAxObject* cell = WorkSheet->querySubObject("Range(QVariant, QVariant)", "A1");
    font = cell->querySubObject("Font");

    cell->setProperty("ColumnWidth", 20);
    font->setProperty("Color",  QColor(255, 0, 0));


    //设置自适应宽度
    QAxObject *autoFitRange = WorkSheet->querySubObject("Columns(A:I)");
    autoFitRange->dynamicCall("AutoFit");

    //设置字体居中
    autoFitRange->setProperty("HorizontalAlignment",-4108);

    //设置整列颜色
    QAxObject *BFitRange = WorkSheet->querySubObject("Columns(B)");
    font = BFitRange->querySubObject("Font");
    font->setProperty("Color", QColor(255,0,0));
}


//删除单元格格式
void MainWindow::on_pushButton_11_clicked()
{
    //清空单元格内容
    QAxObject* cell = WorkSheet->querySubObject("Range(QVariant, QVariant)", "A1");
    cell->dynamicCall("ClearContents()");
}













