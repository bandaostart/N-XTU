#ifndef SERIALDIALOG_H
#define SERIALDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QListWidgetItem>
#include <QList>

namespace Ui {
class SerialDialog;
}

class SerialDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SerialDialog(QWidget *parent = 0);
    ~SerialDialog();


private:
    int CountPortListItem;
    enum {NumPortListItem = 100};
    QListWidgetItem *PortListItem[NumPortListItem];


private slots:
    void on_SelectPort_Radio_clicked();

    void on_ProvidePort_Radio_clicked();

    void on_RefreshPort_Button_clicked();

    void on_Port_ListView_itemClicked(QListWidgetItem *item);

    void on_Port_LineEdit_textChanged(const QString &arg1);

private:
    Ui::SerialDialog *ui;
};

#endif // SERIALDIALOG_H
