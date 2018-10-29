#include "searchdialog.h"


SearchDialog::SearchDialog(QWidget *parent) :QDialog(parent)
{
    //搜索图片设置
    Pixmap[0].load(":/image/xbee_search1.png");
    Pixmap[1].load(":/image/xbee_search2.png");
    Pixmap[2].load(":/image/xbee_search3.png");
    Pixmap[3].load(":/image/xbee_search4.png");
    Pixmap[4].load(":/image/xbee_search5.png");
    Pixmap[5].load(":/image/xbee_search6.png");
    Pixmap[6].load(":/image/xbee_search7.png");


    //图片和说明创建
    Pixmap_Label      = new QLabel(this);
    Pixmap_Label->setPixmap(Pixmap[0]);
    Pixmap_Label->setGeometry(5 ,28, 64, 64);

    TopText_Label     = new QLabel(this);
    TopText_Label->setText("Disocvering radio modules connected to you machine....");
    TopText_Label->setGeometry(84, 5, 370, 20);

    BottomText_Label  = new QLabel(this);
    BottomText_Label->setText("Estimated ramaining time : ");
    BottomText_Label->setGeometry(84, 55, 370, 20);


   //创建进度栏
    Progree_Bar       = new QProgressBar(this);
    Progree_Bar->setGeometry(84, 30, 370, 20);
    Progree_Bar->setRange(0, 100);
    Progree_Bar->setValue(0);
    Progree_Bar->setTextVisible(false);


    //取消按钮创建
    Cancel_Button = new QPushButton("Cancel", this);
    Cancel_Button->setIcon(QIcon(":/image/error.png"));
    Cancel_Button->setGeometry(364, 80, 90, 25);
    connect(Cancel_Button, &QPushButton::clicked, this, &SearchDialog::Cancel_Button_Close);



    //窗体属性设置
    this->setFixedSize(465, 110);
    this->setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    this->setWindowTitle("Discovering radio modules");
    this->setWindowModality(Qt::ApplicationModal);

    connect(this, &SearchDialog::Signal_DialogClose, this, &SearchDialog::Slot_Dialog_Close);
}

SearchDialog::~SearchDialog()
{

}


//设置搜索进度
void SearchDialog::Set_SearchDisplay(int count, int total_num)
{

    Pixmap_Label->setPixmap(Pixmap[count % 7]);
    Progree_Bar->setValue(count*(100/total_num));
    BottomText_Label->setText("Estimated ramaining time : "+QString::number(count*(100/total_num))+"%");
}


void SearchDialog::Slot_Dialog_Close()
{
    this->close();
}



void SearchDialog::Cancel_Button_Close()
{
    this->close();

    emit this->Signal_CancelClose(Port_Name);
}











