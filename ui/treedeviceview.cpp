#include "treedeviceview.h"
#include "ui_treedeviceview.h"

TreeDeviceView::TreeDeviceView(QJsonArray mainArray, int index, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TreeDeviceView),
    mainArray(mainArray),
    index(index)
{
    ui->setupUi(this);

    // Set Data Value
    QJsonObject device = mainArray.at(index).toObject();
    ui->lblDeviceName->setText(device.value("brand").toString()+" "+device.value("model").toString());
    ui->lblOsName->setText(device.value("os_name").toString()+" "+device.value("os_version").toString());

    // Set Border
    if(index == 0){
        if(mainArray.size() > 1){
            ui->itemHolder->setStyleSheet("QWidget{border-top:1px solid #36353a;border-left:1px solid #36353a;border-right:1px solid #36353a;border-top-left-radius:10px;border-top-right-radius:10px;}");
        }else{
            ui->itemHolder->setStyleSheet("QWidget{border:1px solid #36353a;border-radius:10px;}");
        }
    }else if(index == mainArray.size()-1){
        ui->itemHolder->setStyleSheet("QWidget{border-bottom:1px solid #36353a;border-left:1px solid #36353a;border-right:1px solid #36353a;border-bottom-left-radius:10px;border-bottom-right-radius:10px;}");
    }else{
        ui->itemHolder->setStyleSheet("QWidget{border-left:1px solid #36353a;border-right:1px solid #36353a;}");
    }
}

TreeDeviceView::~TreeDeviceView()
{
    delete ui;
}
