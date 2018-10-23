/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QTextEdit *textEdit;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(775, 613);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(460, 20, 281, 31));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(460, 70, 281, 31));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(460, 120, 281, 31));
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(460, 170, 281, 31));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(20, 20, 421, 541));
        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(460, 520, 281, 31));
        pushButton_6 = new QPushButton(centralWidget);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(460, 220, 281, 31));
        pushButton_7 = new QPushButton(centralWidget);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(460, 270, 281, 31));
        pushButton_8 = new QPushButton(centralWidget);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setGeometry(QRect(460, 320, 281, 31));
        pushButton_9 = new QPushButton(centralWidget);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));
        pushButton_9->setGeometry(QRect(460, 370, 281, 31));
        pushButton_10 = new QPushButton(centralWidget);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));
        pushButton_10->setGeometry(QRect(460, 470, 281, 31));
        pushButton_11 = new QPushButton(centralWidget);
        pushButton_11->setObjectName(QStringLiteral("pushButton_11"));
        pushButton_11->setGeometry(QRect(460, 420, 281, 31));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 775, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "1-\350\277\236\346\216\245\346\216\247\344\273\266Excel", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "2-\346\211\223\345\274\200\345\267\245\344\275\234\350\226\204\351\233\206\345\220\210", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "3-\346\226\260\345\273\272\344\270\200\344\270\252\345\267\245\344\275\234\350\226\204", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("MainWindow", "3-\346\211\223\345\274\200\344\270\200\344\270\252\345\267\245\344\275\234\350\226\204", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("MainWindow", "11-\344\277\235\345\255\230\345\267\245\344\275\234\350\226\204\345\271\266\351\200\200\345\207\272", Q_NULLPTR));
        pushButton_6->setText(QApplication::translate("MainWindow", "4-\346\211\223\345\274\200\344\270\200\344\270\252sheet\345\267\245\344\275\234\350\241\250", Q_NULLPTR));
        pushButton_7->setText(QApplication::translate("MainWindow", "6-\350\216\267\345\217\226\345\267\245\344\275\234\350\241\250\347\232\204\350\241\214\346\225\260\345\222\214\345\210\227\346\225\260", Q_NULLPTR));
        pushButton_8->setText(QApplication::translate("MainWindow", "7-\345\206\231\345\215\225\345\205\203\346\240\274\346\225\260\346\215\256", Q_NULLPTR));
        pushButton_9->setText(QApplication::translate("MainWindow", "8-\350\257\273\345\217\226\345\215\225\345\205\203\346\240\274\346\225\260\346\215\256", Q_NULLPTR));
        pushButton_10->setText(QApplication::translate("MainWindow", "10-\350\256\276\347\275\256\345\215\225\345\205\203\346\240\274\346\240\274\345\274\217", Q_NULLPTR));
        pushButton_11->setText(QApplication::translate("MainWindow", "9-\345\210\240\351\231\244\345\215\225\345\205\203\346\240\274\346\225\260\346\215\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
