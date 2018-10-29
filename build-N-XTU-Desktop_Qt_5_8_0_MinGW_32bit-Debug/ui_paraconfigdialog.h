/********************************************************************************
** Form generated from reading UI file 'paraconfigdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARACONFIGDIALOG_H
#define UI_PARACONFIGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ParaConfigDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLabel *label_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLabel *label_3;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_6;
    QLabel *label_4;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_8;
    QLabel *label_5;
    QLineEdit *lineEdit_9;
    QLineEdit *lineEdit_10;
    QLabel *label_6;
    QLineEdit *lineEdit_11;
    QLineEdit *lineEdit_12;
    QLabel *label_7;
    QLineEdit *lineEdit_13;
    QLineEdit *lineEdit_14;
    QPushButton *Finish_Button;
    QPushButton *Cancel_Button;

    void setupUi(QDialog *ParaConfigDialog)
    {
        if (ParaConfigDialog->objectName().isEmpty())
            ParaConfigDialog->setObjectName(QStringLiteral("ParaConfigDialog"));
        ParaConfigDialog->resize(375, 432);
        gridLayout = new QGridLayout(ParaConfigDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(ParaConfigDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit = new QLineEdit(ParaConfigDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        lineEdit_2 = new QLineEdit(ParaConfigDialog);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 0, 2, 1, 1);

        label_2 = new QLabel(ParaConfigDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_3 = new QLineEdit(ParaConfigDialog);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        gridLayout->addWidget(lineEdit_3, 1, 1, 1, 1);

        lineEdit_4 = new QLineEdit(ParaConfigDialog);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));

        gridLayout->addWidget(lineEdit_4, 1, 2, 1, 1);

        label_3 = new QLabel(ParaConfigDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        lineEdit_5 = new QLineEdit(ParaConfigDialog);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));

        gridLayout->addWidget(lineEdit_5, 2, 1, 1, 1);

        lineEdit_6 = new QLineEdit(ParaConfigDialog);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));

        gridLayout->addWidget(lineEdit_6, 2, 2, 1, 1);

        label_4 = new QLabel(ParaConfigDialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        lineEdit_7 = new QLineEdit(ParaConfigDialog);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));

        gridLayout->addWidget(lineEdit_7, 3, 1, 1, 1);

        lineEdit_8 = new QLineEdit(ParaConfigDialog);
        lineEdit_8->setObjectName(QStringLiteral("lineEdit_8"));

        gridLayout->addWidget(lineEdit_8, 3, 2, 1, 1);

        label_5 = new QLabel(ParaConfigDialog);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        lineEdit_9 = new QLineEdit(ParaConfigDialog);
        lineEdit_9->setObjectName(QStringLiteral("lineEdit_9"));

        gridLayout->addWidget(lineEdit_9, 4, 1, 1, 1);

        lineEdit_10 = new QLineEdit(ParaConfigDialog);
        lineEdit_10->setObjectName(QStringLiteral("lineEdit_10"));

        gridLayout->addWidget(lineEdit_10, 4, 2, 1, 1);

        label_6 = new QLabel(ParaConfigDialog);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        lineEdit_11 = new QLineEdit(ParaConfigDialog);
        lineEdit_11->setObjectName(QStringLiteral("lineEdit_11"));

        gridLayout->addWidget(lineEdit_11, 5, 1, 1, 1);

        lineEdit_12 = new QLineEdit(ParaConfigDialog);
        lineEdit_12->setObjectName(QStringLiteral("lineEdit_12"));

        gridLayout->addWidget(lineEdit_12, 5, 2, 1, 1);

        label_7 = new QLabel(ParaConfigDialog);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 6, 0, 1, 1);

        lineEdit_13 = new QLineEdit(ParaConfigDialog);
        lineEdit_13->setObjectName(QStringLiteral("lineEdit_13"));

        gridLayout->addWidget(lineEdit_13, 6, 1, 1, 1);

        lineEdit_14 = new QLineEdit(ParaConfigDialog);
        lineEdit_14->setObjectName(QStringLiteral("lineEdit_14"));

        gridLayout->addWidget(lineEdit_14, 6, 2, 1, 1);

        Finish_Button = new QPushButton(ParaConfigDialog);
        Finish_Button->setObjectName(QStringLiteral("Finish_Button"));

        gridLayout->addWidget(Finish_Button, 7, 1, 1, 1);

        Cancel_Button = new QPushButton(ParaConfigDialog);
        Cancel_Button->setObjectName(QStringLiteral("Cancel_Button"));

        gridLayout->addWidget(Cancel_Button, 7, 2, 1, 1);


        retranslateUi(ParaConfigDialog);

        QMetaObject::connectSlotsByName(ParaConfigDialog);
    } // setupUi

    void retranslateUi(QDialog *ParaConfigDialog)
    {
        ParaConfigDialog->setWindowTitle(QApplication::translate("ParaConfigDialog", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("ParaConfigDialog", "TextLabel", Q_NULLPTR));
        label_2->setText(QApplication::translate("ParaConfigDialog", "TextLabel", Q_NULLPTR));
        label_3->setText(QApplication::translate("ParaConfigDialog", "TextLabel", Q_NULLPTR));
        label_4->setText(QApplication::translate("ParaConfigDialog", "TextLabel", Q_NULLPTR));
        label_5->setText(QApplication::translate("ParaConfigDialog", "TextLabel", Q_NULLPTR));
        label_6->setText(QApplication::translate("ParaConfigDialog", "TextLabel", Q_NULLPTR));
        label_7->setText(QApplication::translate("ParaConfigDialog", "TextLabel", Q_NULLPTR));
        Finish_Button->setText(QApplication::translate("ParaConfigDialog", "Finish", Q_NULLPTR));
        Cancel_Button->setText(QApplication::translate("ParaConfigDialog", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ParaConfigDialog: public Ui_ParaConfigDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARACONFIGDIALOG_H
