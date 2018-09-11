/********************************************************************************
** Form generated from reading UI file 'serialdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIALDIALOG_H
#define UI_SERIALDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_SerialDialog
{
public:
    QDialogButtonBox *OkCancel_Button;
    QFrame *Second_Line;
    QLabel *Text_label;
    QTextBrowser *Status_Browser;
    QLabel *Pixmap2_Label;
    QRadioButton *SelectPort_Radio;
    QRadioButton *ProvidePort_Radio;
    QLineEdit *Port_LineEdit;
    QPushButton *RefreshPort_Button;
    QLabel *BaudRate_Label;
    QLabel *DataBits_Label;
    QLabel *Parity_Label;
    QLabel *StopBits_Label;
    QLabel *FlowCtrl_Label;
    QComboBox *BaudRate_Box;
    QComboBox *DataBits_Box;
    QComboBox *Parity_Box;
    QComboBox *StopBits_Box;
    QComboBox *FlowCtrl_Box;
    QCheckBox *Program_CheckBox;
    QPushButton *SetDefault_Button;
    QLabel *Pixmap_Label;
    QFrame *First_Line;
    QListWidget *Port_ListView;

    void setupUi(QDialog *SerialDialog)
    {
        if (SerialDialog->objectName().isEmpty())
            SerialDialog->setObjectName(QStringLiteral("SerialDialog"));
        SerialDialog->resize(420, 600);
        OkCancel_Button = new QDialogButtonBox(SerialDialog);
        OkCancel_Button->setObjectName(QStringLiteral("OkCancel_Button"));
        OkCancel_Button->setGeometry(QRect(40, 550, 371, 32));
        OkCancel_Button->setOrientation(Qt::Horizontal);
        OkCancel_Button->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        Second_Line = new QFrame(SerialDialog);
        Second_Line->setObjectName(QStringLiteral("Second_Line"));
        Second_Line->setGeometry(QRect(0, 530, 450, 3));
        Second_Line->setFrameShape(QFrame::HLine);
        Second_Line->setFrameShadow(QFrame::Sunken);
        Text_label = new QLabel(SerialDialog);
        Text_label->setObjectName(QStringLiteral("Text_label"));
        Text_label->setGeometry(QRect(10, 10, 151, 21));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        Text_label->setFont(font);
        Status_Browser = new QTextBrowser(SerialDialog);
        Status_Browser->setObjectName(QStringLiteral("Status_Browser"));
        Status_Browser->setGeometry(QRect(39, 31, 301, 31));
        Pixmap2_Label = new QLabel(SerialDialog);
        Pixmap2_Label->setObjectName(QStringLiteral("Pixmap2_Label"));
        Pixmap2_Label->setGeometry(QRect(18, 32, 16, 16));
        Pixmap2_Label->setPixmap(QPixmap(QString::fromUtf8(":/image/error.png")));
        SelectPort_Radio = new QRadioButton(SerialDialog);
        SelectPort_Radio->setObjectName(QStringLiteral("SelectPort_Radio"));
        SelectPort_Radio->setGeometry(QRect(20, 90, 191, 16));
        ProvidePort_Radio = new QRadioButton(SerialDialog);
        ProvidePort_Radio->setObjectName(QStringLiteral("ProvidePort_Radio"));
        ProvidePort_Radio->setGeometry(QRect(20, 220, 191, 16));
        Port_LineEdit = new QLineEdit(SerialDialog);
        Port_LineEdit->setObjectName(QStringLiteral("Port_LineEdit"));
        Port_LineEdit->setGeometry(QRect(40, 240, 371, 21));
        RefreshPort_Button = new QPushButton(SerialDialog);
        RefreshPort_Button->setObjectName(QStringLiteral("RefreshPort_Button"));
        RefreshPort_Button->setGeometry(QRect(304, 190, 101, 23));
        BaudRate_Label = new QLabel(SerialDialog);
        BaudRate_Label->setObjectName(QStringLiteral("BaudRate_Label"));
        BaudRate_Label->setGeometry(QRect(21, 280, 54, 25));
        DataBits_Label = new QLabel(SerialDialog);
        DataBits_Label->setObjectName(QStringLiteral("DataBits_Label"));
        DataBits_Label->setGeometry(QRect(21, 310, 54, 25));
        Parity_Label = new QLabel(SerialDialog);
        Parity_Label->setObjectName(QStringLiteral("Parity_Label"));
        Parity_Label->setGeometry(QRect(21, 340, 36, 25));
        StopBits_Label = new QLabel(SerialDialog);
        StopBits_Label->setObjectName(QStringLiteral("StopBits_Label"));
        StopBits_Label->setGeometry(QRect(21, 370, 54, 25));
        FlowCtrl_Label = new QLabel(SerialDialog);
        FlowCtrl_Label->setObjectName(QStringLiteral("FlowCtrl_Label"));
        FlowCtrl_Label->setGeometry(QRect(21, 400, 72, 25));
        BaudRate_Box = new QComboBox(SerialDialog);
        BaudRate_Box->setObjectName(QStringLiteral("BaudRate_Box"));
        BaudRate_Box->setGeometry(QRect(99, 280, 311, 25));
        DataBits_Box = new QComboBox(SerialDialog);
        DataBits_Box->setObjectName(QStringLiteral("DataBits_Box"));
        DataBits_Box->setGeometry(QRect(99, 310, 311, 25));
        Parity_Box = new QComboBox(SerialDialog);
        Parity_Box->setObjectName(QStringLiteral("Parity_Box"));
        Parity_Box->setGeometry(QRect(99, 340, 311, 25));
        StopBits_Box = new QComboBox(SerialDialog);
        StopBits_Box->setObjectName(QStringLiteral("StopBits_Box"));
        StopBits_Box->setGeometry(QRect(99, 370, 311, 25));
        FlowCtrl_Box = new QComboBox(SerialDialog);
        FlowCtrl_Box->setObjectName(QStringLiteral("FlowCtrl_Box"));
        FlowCtrl_Box->setGeometry(QRect(99, 400, 311, 25));
        Program_CheckBox = new QCheckBox(SerialDialog);
        Program_CheckBox->setObjectName(QStringLiteral("Program_CheckBox"));
        Program_CheckBox->setGeometry(QRect(180, 440, 231, 16));
        SetDefault_Button = new QPushButton(SerialDialog);
        SetDefault_Button->setObjectName(QStringLiteral("SetDefault_Button"));
        SetDefault_Button->setGeometry(QRect(314, 470, 81, 23));
        Pixmap_Label = new QLabel(SerialDialog);
        Pixmap_Label->setObjectName(QStringLiteral("Pixmap_Label"));
        Pixmap_Label->setGeometry(QRect(340, 10, 71, 51));
        Pixmap_Label->setPixmap(QPixmap(QString::fromUtf8(":/image/header_add_device.png")));
        First_Line = new QFrame(SerialDialog);
        First_Line->setObjectName(QStringLiteral("First_Line"));
        First_Line->setGeometry(QRect(0, 70, 420, 3));
        First_Line->setFrameShape(QFrame::HLine);
        First_Line->setFrameShadow(QFrame::Sunken);
        Port_ListView = new QListWidget(SerialDialog);
        Port_ListView->setObjectName(QStringLiteral("Port_ListView"));
        Port_ListView->setGeometry(QRect(40, 110, 371, 71));
        OkCancel_Button->raise();
        Second_Line->raise();
        Text_label->raise();
        Status_Browser->raise();
        Pixmap2_Label->raise();
        Pixmap_Label->raise();
        First_Line->raise();
        SelectPort_Radio->raise();
        ProvidePort_Radio->raise();
        Port_LineEdit->raise();
        RefreshPort_Button->raise();
        BaudRate_Label->raise();
        DataBits_Label->raise();
        Parity_Label->raise();
        StopBits_Label->raise();
        FlowCtrl_Label->raise();
        BaudRate_Box->raise();
        DataBits_Box->raise();
        Parity_Box->raise();
        StopBits_Box->raise();
        FlowCtrl_Box->raise();
        Program_CheckBox->raise();
        SetDefault_Button->raise();
        Port_ListView->raise();

        retranslateUi(SerialDialog);
        QObject::connect(OkCancel_Button, SIGNAL(accepted()), SerialDialog, SLOT(accept()));
        QObject::connect(OkCancel_Button, SIGNAL(rejected()), SerialDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SerialDialog);
    } // setupUi

    void retranslateUi(QDialog *SerialDialog)
    {
        SerialDialog->setWindowTitle(QApplication::translate("SerialDialog", "Dialog", Q_NULLPTR));
        Text_label->setText(QApplication::translate("SerialDialog", "Add a radio module", Q_NULLPTR));
        Status_Browser->setHtml(QApplication::translate("SerialDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Select and configure the Serial/USB port where the radio module is connected to.</p></body></html>", Q_NULLPTR));
        Pixmap2_Label->setText(QString());
        SelectPort_Radio->setText(QApplication::translate("SerialDialog", "Select the Serial/USB port\357\274\232", Q_NULLPTR));
        ProvidePort_Radio->setText(QApplication::translate("SerialDialog", "Provide a port name manually", Q_NULLPTR));
        RefreshPort_Button->setText(QApplication::translate("SerialDialog", "Refresh Ports", Q_NULLPTR));
        BaudRate_Label->setText(QApplication::translate("SerialDialog", "Baud Rate", Q_NULLPTR));
        DataBits_Label->setText(QApplication::translate("SerialDialog", "Data Bits", Q_NULLPTR));
        Parity_Label->setText(QApplication::translate("SerialDialog", "Parity", Q_NULLPTR));
        StopBits_Label->setText(QApplication::translate("SerialDialog", "Stop Bits", Q_NULLPTR));
        FlowCtrl_Label->setText(QApplication::translate("SerialDialog", "Flow Control", Q_NULLPTR));
        BaudRate_Box->clear();
        BaudRate_Box->insertItems(0, QStringList()
         << QApplication::translate("SerialDialog", "1200", Q_NULLPTR)
         << QApplication::translate("SerialDialog", "2400", Q_NULLPTR)
         << QApplication::translate("SerialDialog", "4800", Q_NULLPTR)
         << QApplication::translate("SerialDialog", "9600", Q_NULLPTR)
         << QApplication::translate("SerialDialog", "19200", Q_NULLPTR)
         << QApplication::translate("SerialDialog", "38400", Q_NULLPTR)
         << QApplication::translate("SerialDialog", "57600", Q_NULLPTR)
         << QApplication::translate("SerialDialog", "115200", Q_NULLPTR)
         << QApplication::translate("SerialDialog", "230400", Q_NULLPTR)
         << QApplication::translate("SerialDialog", "460800", Q_NULLPTR)
         << QApplication::translate("SerialDialog", "921600", Q_NULLPTR)
        );
        DataBits_Box->clear();
        DataBits_Box->insertItems(0, QStringList()
         << QApplication::translate("SerialDialog", "7", Q_NULLPTR)
         << QApplication::translate("SerialDialog", "8", Q_NULLPTR)
        );
        Parity_Box->clear();
        Parity_Box->insertItems(0, QStringList()
         << QApplication::translate("SerialDialog", "None", Q_NULLPTR)
         << QApplication::translate("SerialDialog", "Even", Q_NULLPTR)
         << QApplication::translate("SerialDialog", "Mark", Q_NULLPTR)
         << QApplication::translate("SerialDialog", "Odd", Q_NULLPTR)
         << QApplication::translate("SerialDialog", "Space", Q_NULLPTR)
        );
        StopBits_Box->clear();
        StopBits_Box->insertItems(0, QStringList()
         << QApplication::translate("SerialDialog", "1", Q_NULLPTR)
         << QApplication::translate("SerialDialog", "2", Q_NULLPTR)
        );
        FlowCtrl_Box->clear();
        FlowCtrl_Box->insertItems(0, QStringList()
         << QApplication::translate("SerialDialog", "None", Q_NULLPTR)
         << QApplication::translate("SerialDialog", "Hardware", Q_NULLPTR)
         << QApplication::translate("SerialDialog", "Xon/Xoff", Q_NULLPTR)
        );
        Program_CheckBox->setText(QApplication::translate("SerialDialog", "The radio module is programmable", Q_NULLPTR));
        SetDefault_Button->setText(QApplication::translate("SerialDialog", "Set defaults", Q_NULLPTR));
        Pixmap_Label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SerialDialog: public Ui_SerialDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIALDIALOG_H
