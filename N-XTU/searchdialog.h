#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <QCommandLinkButton>


class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(QWidget *parent = 0);
    ~SearchDialog();

private:

    QCommandLinkButton *Cancel_Button;

};

#endif // SEARCHDIALOG_H
