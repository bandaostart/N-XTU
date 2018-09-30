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
    void Open_SearchDialog();
    void Close_SearchDialog();

signals:
    void Signal_DialogClose();
private slots:
    void Slot_Dialog_Close();


private:
    QLabel       *Pixmap_Label;
    QLabel       *TopText_Label;
    QLabel       *BottomText_Label;
    QProgressBar *Progree_Bar;
    QPushButton  *Cancel_Button;
    QPixmap      Pixmap[7];

};

#endif // SEARCHDIALOG_H
