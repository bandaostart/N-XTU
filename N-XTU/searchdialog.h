#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>


class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(QWidget *parent = 0);
    ~SearchDialog();

public:
    void Set_SearchDisplay(int count, int total_num);

signals:
    void Signal_DialogClose();
    void Signal_CancelClose(const QString &portname);

private slots:
    void Slot_Dialog_Close();
    void Cancel_Button_Close();


private:
    QLabel       *Pixmap_Label;
    QLabel       *TopText_Label;
    QLabel       *BottomText_Label;
    QProgressBar *Progree_Bar;
    QPushButton  *Cancel_Button;
    QPixmap      Pixmap[7];

public:
    QString      Port_Name;

};

#endif // SEARCHDIALOG_H
