#include "premiumview.h"
#include "ui_premiumview.h"

PremiumView::PremiumView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PremiumView)
{
    ui->setupUi(this);
}

PremiumView::~PremiumView()
{
    delete ui;
}

void PremiumView::on_btnBack_clicked()
{
    emit openProfilePage();
}

