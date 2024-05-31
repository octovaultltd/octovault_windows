#include "aboutview.h"
#include "ui_aboutview.h"
#include <QDesktopServices>
#include <QUrl>

AboutView::AboutView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutView)
{
    ui->setupUi(this);
}

AboutView::~AboutView()
{
    delete ui;
}

void AboutView::on_btnBack_clicked()
{
    emit openProfilePage();
}


void AboutView::on_btnFb_clicked()
{
    QString url = "https://www.facebook.com/ScyberVPNHub";
    QDesktopServices::openUrl(QUrl(url));
}


void AboutView::on_btnInsta_clicked()
{
    QString url = "https://instagram.com/octovault?igshid=YmMyMTA2M2Y=";
    QDesktopServices::openUrl(QUrl(url));
}


void AboutView::on_btnYoutube_clicked()
{
    QString url = "https://www.facebook.com/ScyberVPNHub";
    QDesktopServices::openUrl(QUrl(url));
}


void AboutView::on_btnLinkedIn_clicked()
{
    QString url = "https://www.facebook.com/ScyberVPNHub";
    QDesktopServices::openUrl(QUrl(url));
}


void AboutView::on_btnTwitter_clicked()
{
    QString url = "https://www.facebook.com/ScyberVPNHub";
    QDesktopServices::openUrl(QUrl(url));
}


void AboutView::on_btnReddit_clicked()
{
    QString url = "https://www.facebook.com/ScyberVPNHub";
    QDesktopServices::openUrl(QUrl(url));
}


void AboutView::on_btnTerms_clicked()
{
    QString url = "https://octovaultvpn.com/t-c";
    QDesktopServices::openUrl(QUrl(url));
}

