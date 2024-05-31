#include "treechildview.h"
#include "ui_treechildview.h"
#include "utils/localdb.h"
#include <QPainter>
#include <QStyleOption>
#include <QDebug>

TreeChildView::TreeChildView(QJsonObject data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TreeChildView),
    data(data)
{
    ui->setupUi(this);

    // Set City Name
    ui->lblChildName->setText(data.value("ipName").toString());

    // Check Favourite Server Or Not
    if(LocalDB().isFavServer(data.value("ip_id").toInt())){
        QPixmap pixmap(":/img/images/icon_favourite_fill.png");
        ui->lblFavButton->setPixmap(pixmap);
        ui->lblFavButton->setScaledContents(true);
    }else{
        QPixmap pixmap(":/img/images/icon_favourite_outline.png");
        ui->lblFavButton->setPixmap(pixmap);
        ui->lblFavButton->setScaledContents(true);
    }

    // Check Selected Or Not
    if(LocalDB().getActiveServerID() == data.value("ip_id").toInt()){
        QPixmap pixmap(":/img/images/icon_radio_selected.png");
        ui->lblLockImage->setPixmap(pixmap);
        ui->lblLockImage->setScaledContents(true);
    }else{
        QPixmap pixmap(":/img/images/icon_radio_unselected.png");
        ui->lblLockImage->setPixmap(pixmap);
        ui->lblLockImage->setScaledContents(true);
    }

    // Install Event Filter For Fav Button
    ui->lblFavButton->installEventFilter(this);
}

TreeChildView::~TreeChildView()
{
    delete ui;
}

QJsonObject TreeChildView::getBundleData(){
    return data;
}

void TreeChildView::toggleFavourite()
{
    int ipID = data.value("ip_id").toInt();
    if(LocalDB().isFavServer(ipID)){
        LocalDB().removeFavourite(ipID);
        QPixmap pixmap(":/img/images/icon_favourite_outline.png");
        ui->lblFavButton->setPixmap(pixmap);
        ui->lblFavButton->setScaledContents(true);
    }else{
        LocalDB().addFavourite(ipID);
        QPixmap pixmap(":/img/images/icon_favourite_fill.png");
        ui->lblFavButton->setPixmap(pixmap);
        ui->lblFavButton->setScaledContents(true);
    }
}

bool TreeChildView::eventFilter(QObject *watched, QEvent *event)
{
    if((event->type() == QEvent::MouseButtonRelease || event->type() == QEvent::MouseButtonPress) && watched == ui->lblFavButton){
        if(event->type() == QEvent::MouseButtonRelease)
            toggleFavourite();
        return true;
    }
    return false;
}

void TreeChildView::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}
