#include "serialdialog.h"
#include "ui_serialdialog.h"
#include <QGridLayout>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QtSerialPort/QSerialPortInfo>
#include <QList>

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


    /*串口查找发现*/
    SerivalDiscover();



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
        ui->Port_ListView->setCurrentRow(0);
        ui->Pixmap2_Label->hide();
        ui->Status_Browser->setText("Select and configure the Serial/USB port where the radio module is connected to.");
    }
    else
    {
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
        ui->Pixmap2_Label->show();
        ui->Status_Browser->setText("You must specify the serial port.");
    }
    else
    {
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
    ui->Port_ListView->clear();
}



//串口选择
void SerialDialog::on_Port_ListView_itemClicked(QListWidgetItem *item)
{
    ui->Pixmap2_Label->hide();

    ui->Status_Browser->setText("Select and configure the Serial/USB port where the radio module is connected to.");
}




void SerialDialog::on_Port_LineEdit_textChanged(const QString &arg1)
{
    if (ui->Port_LineEdit->text() == "")
    {
        ui->Pixmap2_Label->show();
        ui->Status_Browser->setText("You must specify the serial port.");
    }
    else
    {
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
        ui->Port_ListView->setCurrentRow(0);
        ui->Pixmap2_Label->hide();
        ui->Status_Browser->setText("Select and configure the Serial/USB port where the radio module is connected to.");
    }
    else
    {
        ui->Pixmap2_Label->show();
        ui->Status_Browser->setText("You must select one Serial/USB port.");
    }
}
