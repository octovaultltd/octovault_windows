#include "supportview.h"
#include "ui_supportview.h"
#include <QDesktopServices>
#include <QUrl>

SupportView::SupportView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SupportView)
{
    ui->setupUi(this);
}

SupportView::~SupportView()
{
    delete ui;
}

void SupportView::on_btnBack_clicked()
{
    emit openProfilePage();
}


void SupportView::on_btnLiveChat_clicked()
{
    QString url = "https://octovaultvpn.com/support";
    QDesktopServices::openUrl(QUrl(url));
}


void SupportView::on_btnEmail_clicked()
{
    QString url = "https://octovaultvpn.com/support";
    QDesktopServices::openUrl(QUrl(url));
}


void SupportView::on_btnFaq_clicked()
{
    QString url = "https://octovaultvpn.com/support";
    QDesktopServices::openUrl(QUrl(url));
}

