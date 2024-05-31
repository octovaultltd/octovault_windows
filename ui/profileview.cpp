#include "profileview.h"
#include "ui_profileview.h"
#include "utils/localdb.h"
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>

ProfileView::ProfileView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProfileView)
{
    ui->setupUi(this);
    updateView();
}

ProfileView::~ProfileView()
{
    delete ui;
}

void ProfileView::on_btnSubscription_clicked()
{
    QString url = "https://octovaultvpn.com/packages";
    QDesktopServices::openUrl(QUrl(url));
}

void ProfileView::on_btnSettings_clicked()
{
    emit openSettingsPage();
}


void ProfileView::on_btnDevice_clicked()
{
    emit openDevicePage();
}


void ProfileView::on_btnRefer_clicked()
{
    emit openReferPage();
}


void ProfileView::on_btnSupport_clicked()
{
    emit openSupportPage();
}


void ProfileView::on_btnAbout_clicked()
{
    emit openAboutPage();
}


void ProfileView::on_btnLogout_clicked()
{
    emit openLoginPage();
}

void ProfileView::showEvent( QShowEvent* event ) {
    QWidget::showEvent( event );
    updateView();
}

void ProfileView::updateView()
{
    if(LocalDB().getUserStatus() == "3"){
        ui->subscriptionHolder->setStyleSheet("QWidget{background:transparent;border: 1px solid #36353a;border-radius: 10px;}");
        ui->lblSubscription->setStyleSheet("QLabel{color:#FFFFFF;border-color:transparent;}");
        ui->lblSubsLogo->setStyleSheet("QLabel{border-color:transparent}");
        ui->lblExpiry->setStyleSheet("QLabel{color:#E84E4E;border-color:transparent;}");
        ui->lblExpiry->setText("No active subscription");
        QPixmap pixmap(":/img/images/icon_subscription.png");
        ui->lblSubsLogo->setPixmap(pixmap);
        ui->lblSubsLogo->setScaledContents(true);
    }else{
        ui->subscriptionHolder->setStyleSheet("QWidget{background:#F8AF3F;border-radius: 10px;}");
        ui->lblSubscription->setStyleSheet("QLabel{color:#000000;border-color:transparent;}");
        ui->lblSubsLogo->setStyleSheet("QLabel{border-color:transparent;}");
        ui->lblExpiry->setStyleSheet("QLabel{color:#818083;border-color:transparent;}");
        QPixmap pixmap(":/img/images/icon_subscription_black.png");
        ui->lblSubsLogo->setPixmap(pixmap);
        ui->lblSubsLogo->setScaledContents(true);
        ui->lblExpiry->setText(QString::number(LocalDB::getExpireInDays())+" days until expire");
    }
}

