/********************************************************************************
** Form generated from reading UI file 'modulepara.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODULEPARA_H
#define UI_MODULEPARA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModulePara
{
public:
    QLabel *label;
    QTextEdit *textEdit;

    void setupUi(QWidget *ModulePara)
    {
        if (ModulePara->objectName().isEmpty())
            ModulePara->setObjectName(QStringLiteral("ModulePara"));
        ModulePara->resize(400, 96);
        label = new QLabel(ModulePara);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 61, 71));
        label->setPixmap(QPixmap(QString::fromUtf8(":/image/xbee_zigbee_64.png")));
        textEdit = new QTextEdit(ModulePara);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(90, 10, 271, 71));

        retranslateUi(ModulePara);

        QMetaObject::connectSlotsByName(ModulePara);
    } // setupUi

    void retranslateUi(QWidget *ModulePara)
    {
        ModulePara->setWindowTitle(QApplication::translate("ModulePara", "Form", Q_NULLPTR));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ModulePara: public Ui_ModulePara {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODULEPARA_H
