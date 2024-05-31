#include "referwithdrawview.h"
#include "ui_referwithdrawview.h"

ReferWithdrawView::ReferWithdrawView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReferWithdrawView)
{
    ui->setupUi(this);
}

ReferWithdrawView::~ReferWithdrawView()
{
    delete ui;
}

void ReferWithdrawView::on_btnBack_clicked()
{
    emit openReferBalancePage();
}

