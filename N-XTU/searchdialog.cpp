#include "searchdialog.h"


SearchDialog::SearchDialog(QWidget *parent) :QDialog(parent)
{

    Cancel_Button = new QCommandLinkButton(this);

    this->setFixedSize(500, 130);
    this->setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    this->setWindowTitle("Discovering radio modules");
}

SearchDialog::~SearchDialog()
{

}
