#include "serialdialog.h"
#include "ui_serialdialog.h"
#include <QGridLayout>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QtSerialPort/QSerialPortInfo>
#include <QList>
#include <QMessageBox>

QT_USE_NAMESPACE

SerialDialog::SerialDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SerialDialog)
{
    ui->setupUi(this);

    this->setWindowTitle("Add Radio Modules");
    this->setWindowFlags(Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
    this->setMinimumSize(420, 600);

    //textBrowser style set
    ui->Status_Browser->setStyleSheet("QTextBrowser{border-width:0;border-style:outset}");
    ui->Status_Browser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->SelectPort_Radio->setChecked(true);
    ui->Port_LineEdit->setEnabled(false);

    ui->BaudRate_Box->setCurrentIndex(3);
    ui->DataBits_Box->setCurrentIndex(1);
}

SerialDialog::~SerialDialog()
{
    delete ui;
}




/*RadioButton 槽函数 自动查找串口功能选择-----------------------------------------------------------------------------------------*/
void SerialDialog::on_SelectPort_Radio_clicked()
{
    if (ui->Port_ListView->count() != 0)
    {
        ui->Finish_Button->setEnabled(true);
        ui->Port_ListView->setCurrentRow(0);
        ui->Pixmap2_Label->hide();
        ui->Status_Browser->setText("Select and configure the Serial/USB port where the radio module is connected to.");
    }
    else
    {
        ui->Finish_Button->setEnabled(false);
        ui->Pixmap2_Label->show();
        ui->Status_Browser->setText("You must select one Serial/USB port.");
    }
    ui->RefreshPort_Button->setEnabled(true);
    ui->Port_ListView->setEnabled(true);
    ui->Port_LineEdit->setEnabled(false);
}




/*RadioButton 槽函数 手动输入串口功能选择---------------------------------------------------------------------------------------*/
void SerialDialog::on_ProvidePort_Radio_clicked()
{
    if (ui->Port_LineEdit->text() == "")
    {
        ui->Finish_Button->setEnabled(false);
        ui->Pixmap2_Label->show();
        ui->Status_Browser->setText("You must specify the serial port.");
    }
    else
    {
        ui->Finish_Button->setEnabled(true);
        ui->Pixmap2_Label->hide();
        ui->Status_Browser->setText("Select and configure the Serial/USB port where the radio module is connected to.");
    }
    ui->Port_ListView->setCurrentRow(-1);
    ui->Port_LineEdit->setEnabled(true);
    ui->RefreshPort_Button->setEnabled(false);
    ui->Port_ListView->setEnabled(false);
}




/*Refresh Button 槽函数 串口重新查找-----------------------------------------------------------------------------------------*/
void SerialDialog::on_RefreshPort_Button_clicked()
{
    SerivalDiscover();
}




/*set Default Button 槽函数 串口参数默认设置---------------------------------------------------------------------------------*/
void SerialDialog::on_SetDefault_Button_clicked()
{
    ui->BaudRate_Box->setCurrentIndex(3);
    ui->DataBits_Box->setCurrentIndex(1);
    ui->Parity_Box->setCurrentIndex(0);
    ui->StopBits_Box->setCurrentIndex(0);
    ui->FlowCtrl_Box->setCurrentIndex(0);
}



/*List Widget 槽函数 串口选择--------------------------------------------------------------------------------------------*/
void SerialDialog::on_Port_ListView_itemClicked(QListWidgetItem *item)
{
    item->text();
    ui->Pixmap2_Label->hide();
    ui->Status_Browser->setText("Select and configure the Serial/USB port where the radio module is connected to.");
}



/*Line Edit 槽函数 速度输出串口-----------------------------------------------------------------------------------------*/
void SerialDialog::on_Port_LineEdit_textChanged(const QString &arg1)
{
    if (arg1 == "")
    {
        ui->Finish_Button->setEnabled(false);
        ui->Pixmap2_Label->show();
        ui->Status_Browser->setText("You must specify the serial port.");
    }
    else
    {
        ui->Finish_Button->setEnabled(true);
        ui->Pixmap2_Label->hide();
        ui->Status_Browser->setText("Select and configure the Serial/USB port where the radio module is connected to.");
    }
}



/*Finish Button 槽函数 打开串口---------------------------------------------------------------------------------------*/
void SerialDialog::on_Finish_Button_clicked()
{
    Serial_Port_Settings.baud      = ui->BaudRate_Box->currentText().toInt();
    Serial_Port_Settings.dataBits  = ui->DataBits_Box->currentText().toInt();
    switch(ui->Parity_Box->currentIndex())
    {
        case 0:
            Serial_Port_Settings.parity = 0;
        break;

        case 1:
            Serial_Port_Settings.parity = 2;
        break;

        case 2:
            Serial_Port_Settings.parity = 5;
        break;

        case 3:
            Serial_Port_Settings.parity = 3;
        break;

        case 4:
            Serial_Port_Settings.parity = 4;
        break;
    }
    Serial_Port_Settings.stopBits = ui->StopBits_Box->currentText().toInt();
    Serial_Port_Settings.flowCtrl = ui->FlowCtrl_Box->currentIndex();
    if(ui->SelectPort_Radio->isChecked())
    {
        Serial_Port_Settings.portName = ui->Port_ListView->currentItem()->text();
    }
    else
    {
        Serial_Port_Settings.portName = ui->Port_LineEdit->text();
    }


    QDialog::accept();
}



/*Cancel Button 槽函数 串口取消-----------------------------------------------------------------------------------------*/
void SerialDialog::on_Cancel_Button_clicked()
{
    QDialog::reject();
}





/*电脑串口检测函数------------------------------------------------------------------------------------------------------*/
void SerialDialog::SerivalDiscover()
{
    QVector<QString> PortName_str;

    ui->Port_ListView->clear();
    PortListItem.clear();

    const auto SerialInfos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : SerialInfos)
    {
        PortName_str.push_back(info.portName());
    }

    std::sort(PortName_str.begin(), PortName_str.end());
    std::sort(PortName_str.begin(), PortName_str.end(),  [](const QString &s1, const QString &s2){return s1.size()  < s2.size();});
    for ( const QString &str : PortName_str)
    {
        PortListItem.push_back(new QListWidgetItem(ui->Port_ListView));
        PortListItem.back()->setIcon(QIcon(":/image/serial_port.png"));
        PortListItem.back()->setText(str);
    }

    if (ui->Port_ListView->count() != 0)
    {
        ui->Finish_Button->setEnabled(true);
        ui->Port_ListView->setCurrentRow(0);
        ui->Pixmap2_Label->hide();
        ui->Status_Browser->setText("Select and configure the Serial/USB port where the radio module is connected to.");
    }
    else
    {
        ui->Finish_Button->setEnabled(false);
        ui->Pixmap2_Label->show();
        ui->Status_Browser->setText("You must select one Serial/USB port.");
    }
}























