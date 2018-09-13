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





/*布局相关处理------------------------------------------------------------------------------*/
//    QGridLayout *firstLayout = new QGridLayout;

//    firstLayout->addWidget(ui->Text_label,     0, 0, 1, 2);
//    firstLayout->addWidget(ui->Pixmap2_Label,  1, 0, 1, 1);
//    firstLayout->addWidget(ui->Status_Browser, 1, 1, 1, 3);
//    firstLayout->addWidget(ui->Pixmap_Label,   0, 4, 2, 1);
//    firstLayout->addWidget(ui->First_Line,     2, 0, 1, 5);
//    //layout->setRowStretch(2,20);

//    QGridLayout *secondLayout = new QGridLayout;
//    secondLayout->addWidget(ui->SelectPort_Radio,   0, 0, 1, 2);
//    secondLayout->addWidget(ui->Port_ListView,      1, 1, 1, 2);
//    secondLayout->addWidget(ui->RefreshPort_Button, 2, 2, 1, 1);
//    secondLayout->addWidget(ui->ProvidePort_Radio,  3, 0, 1, 2);
//    secondLayout->addWidget(ui->Port_LineEdit,      4, 1, 1, 2);
//    secondLayout->addWidget(ui->SetDefault_Button,  5, 2, 1, 1);

//    QFormLayout *ThirdLayout = new QFormLayout;
//    ThirdLayout->addRow(ui->BaudRate_Label, ui->BaudRate_Box);
//    ThirdLayout->addRow(ui->DataBits_Label, ui->DataBits_Box);
//    ThirdLayout->addRow(ui->Parity_Label,   ui->Parity_Box);
//    ThirdLayout->addRow(ui->StopBits_Label, ui->StopBits_Box);
//    ThirdLayout->addRow(ui->FlowCtrl_Label, ui->FlowCtrl_Box);

//    QVBoxLayout *mainLayout = new QVBoxLayout;
//    mainLayout->addLayout(firstLayout,  0);
//    mainLayout->addLayout(secondLayout, 1);
//    mainLayout->addLayout(ThirdLayout,  2);
//    setLayout(mainLayout);
}

SerialDialog::~SerialDialog()
{
    delete ui;
}



//自动查找串口功能 Radio
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



//用户手动输入 Radio
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



//串口重新查找
void SerialDialog::on_RefreshPort_Button_clicked()
{
    SerivalDiscover();
}


//参数默认配置
void SerialDialog::on_SetDefault_Button_clicked()
{
    ui->BaudRate_Box->setCurrentIndex(3);
    ui->DataBits_Box->setCurrentIndex(1);
    ui->Parity_Box->setCurrentIndex(0);
    ui->StopBits_Box->setCurrentIndex(0);
    ui->FlowCtrl_Box->setCurrentIndex(0);
}



//串口选择
void SerialDialog::on_Port_ListView_itemClicked(QListWidgetItem *item)
{
    item->text();
    ui->Pixmap2_Label->hide();
    ui->Status_Browser->setText("Select and configure the Serial/USB port where the radio module is connected to.");
}




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







//串口发现操作
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



//串口选定
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


    if(!Serial_Port_Map.contains(Serial_Port_Settings.portName))
    {
        Serial_Port_Map.insert(Serial_Port_Settings.portName, new SerialTxThread());
    }

    if (!Serial_Port_Map.value(Serial_Port_Settings.portName)->SerialOpen(Serial_Port_Settings))
    {
        Serial_Port_Map.remove(Serial_Port_Settings.portName);
        QMessageBox::critical(NULL, "Error discovering device",
                              "COM > serOpenPort failed:Port not valid                           ", QMessageBox::Ok);
    }
    else
    {
        QDialog::accept();
    }
}


//串口选择取消
void SerialDialog::on_Cancel_Button_clicked()
{
    QDialog::accept();
}






















