#include "referview.h"
#include "ui_referview.h"

ReferView::ReferView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReferView)
{
    ui->setupUi(this);
}

ReferView::~ReferView()
{
    delete ui;
}

void ReferView::on_btnBack_clicked()
{
    emit openProfilePage();
}


void ReferView::on_btnStart_clicked()
{
    emit openReferBalancePage();
}

