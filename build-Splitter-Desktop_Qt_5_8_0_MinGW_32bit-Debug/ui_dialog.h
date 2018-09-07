/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeView>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QSplitter *splitter;
    QTreeView *treeView;
    QTextEdit *textEdit;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(577, 469);
        splitter = new QSplitter(Dialog);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setGeometry(QRect(9, 9, 512, 192));
        splitter->setMinimumSize(QSize(100, 100));
        splitter->setOrientation(Qt::Horizontal);
        treeView = new QTreeView(splitter);
        treeView->setObjectName(QStringLiteral("treeView"));
        splitter->addWidget(treeView);
        textEdit = new QTextEdit(splitter);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        splitter->addWidget(textEdit);

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
