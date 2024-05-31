#include "accountview.h"
#include "ui_accountview.h"

AccountView::AccountView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountView)
{
    ui->setupUi(this);
}

AccountView::~AccountView()
{
    delete ui;
}

void AccountView::on_btnBack_clicked()
{
    emit openProfilePage();
}

