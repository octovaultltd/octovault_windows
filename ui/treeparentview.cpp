#include "treeparentview.h"
#include "ui_treeparentview.h"

TreeParentView::TreeParentView(QJsonObject data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TreeParentView),
    data(data)
{
    ui->setupUi(this);

    // Set Country Flag
    QPixmap pixmap(data.value("countryImage").toString());
    ui->lblParentImage->setPixmap(pixmap);
    ui->lblParentImage->setScaledContents(true);
    // Set Country Name
    ui->lblParentName->setText(data.value("countryName").toString());
    // Set Expanded
    setExpanded(data.value("isExpanded").toBool());
}

TreeParentView::~TreeParentView()
{
    delete ui;
}

void TreeParentView::setExpanded(bool expanded)
{
    if(expanded){
        QPixmap pixmap(":/img/images/icon_down_arrow_gray.png");
        ui->lblParentArrow->setPixmap(pixmap);
        ui->lblParentArrow->setScaledContents(true);
    }else{
        QPixmap pixmap(":/img/images/icon_front_arrow_gray.png");
        ui->lblParentArrow->setPixmap(pixmap);
        ui->lblParentArrow->setScaledContents(true);
    }
}
