#include "serialdialog.h"
#include "ui_serialdialog.h"
#include <QGridLayout>
#include <QFormLayout>
#include <QVBoxLayout>

SerialDialog::SerialDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SerialDialog)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
    this->setMinimumSize(420, 650);

    //textBrowser style set
    ui->Status_Browser->setStyleSheet("QTextBrowser{border-width:0;border-style:outset}");
    ui->Status_Browser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QGridLayout *firstLayout = new QGridLayout;
    firstLayout->addWidget(ui->Text_label,     0, 0, 1, 3);
    firstLayout->addWidget(ui->Pixmap2_Label,  1, 0, 1, 1);
    firstLayout->addWidget(ui->Status_Browser, 1, 1, 2, 1);
    firstLayout->addWidget(ui->Parity_Label,   0, 3, 3, 1);
    firstLayout->addWidget(ui->First_Line,     2, 0, 1, 4);
    //    layout->setRowStretch(2,20);

    QGridLayout *secondLayout = new QGridLayout;
    secondLayout->addWidget(ui->SelectPort_Radio,   0, 0, 1, 2);
    secondLayout->addWidget(ui->Port_ListView,      1, 1, 1, 2);
    secondLayout->addWidget(ui->RefreshPort_Button, 2, 2, 1, 1);
    secondLayout->addWidget(ui->ProvidePort_Radio,  3, 0, 1, 2);
    secondLayout->addWidget(ui->Port_LineEdit,      4, 1, 1, 2);
    secondLayout->addWidget(ui->SetDefault_Button,  5, 2, 1, 1);

    QFormLayout *ThirdLayout = new QFormLayout;
    ThirdLayout->addRow(ui->BaudRate_Label, ui->BaudRate_Box);
    ThirdLayout->addRow(ui->DataBits_Label, ui->DataBits_Box);
    ThirdLayout->addRow(ui->Parity_Label,   ui->Parity_Box);
    ThirdLayout->addRow(ui->StopBits_Label, ui->StopBits_Box);
    ThirdLayout->addRow(ui->FlowCtrl_Label, ui->FlowCtrl_Box);





    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(firstLayout);
    setLayout(mainLayout);
}

SerialDialog::~SerialDialog()
{
    delete ui;
}
