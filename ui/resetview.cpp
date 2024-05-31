#include "resetview.h"
#include "ui_resetview.h"
#include "utils/networkmanager.h"

ResetView::ResetView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResetView),
    logoState(0)
{
    ui->setupUi(this);

    if(logoState == 0){
        ui->lblLogo->setHidden(false);
        ui->lblLogoTwo->setHidden(true);
    }else{
        ui->lblLogo->setHidden(true);
        ui->lblLogoTwo->setHidden(false);
    }

    ui->editPass->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->editConfirm->setAttribute(Qt::WA_MacShowFocusRect, 0);

    // Initialize Spinner
    movie = new QMovie(":/img/images/spinner.gif");
    ui->lblSpinner->setMovie(movie);
}

ResetView::~ResetView()
{
    delete ui;
}


void ResetView::on_btnSave_clicked()
{
    QString email = LocalDB::getUsername();
    QString password = ui->editPass->text();
    QString confirm = ui->editConfirm->text();

    if(password.isEmpty()){
        QMessageBox alert;
        alert.setText("Password Cannot Be Empty");
        alert.setStandardButtons(QMessageBox::Ok);
        alert.exec();
    }else if(password != confirm){
        QMessageBox alert;
        alert.setText("Password Must Match");
        alert.setStandardButtons(QMessageBox::Ok);
        alert.exec();
    }else if(password.length() < 6){
        QMessageBox alert;
        alert.setText("Password Must be 6 digit");
        alert.setStandardButtons(QMessageBox::Ok);
        alert.exec();
    }else{
        // Show Spinner
        ui->lblSpinner->show();
        movie->start();

        // Make API Call
        auto response = NetworkManager().callResetAPI(email, LocalDB::getLastOTP(), password, confirm);
        qDebug() << response;

        // Hide Spinner
        movie->stop();
        ui->lblSpinner->hide();

        // Show Alert
        QMessageBox alert;
        alert.setText(response[1]);
        alert.setStandardButtons(QMessageBox::Ok);
        auto action = alert.exec();
        if(action == QMessageBox::Ok){
            if(response[0] == "1"){
                LocalDB::setUsername(email);
                LocalDB::setPassword(password);
                emit openLoginPage();
            }
        }
    }
}


void ResetView::on_btnChangeLogo_clicked()
{
    if(logoState == 1){
        logoState = 0;
        ui->lblLogo->setHidden(false);
        ui->lblLogoTwo->setHidden(true);
    }else{
        logoState = 1;
        ui->lblLogo->setHidden(true);
        ui->lblLogoTwo->setHidden(false);
    }
}


void ResetView::on_btnBack_clicked()
{
    emit openResetVerifyPage();
}


void ResetView::on_btnSHPass_clicked()
{
    if(isPassVisible){
        isPassVisible = false;
        ui->btnSHPass->setIcon(QIcon(":/img/images/icon_show.png"));
        ui->editPass->setEchoMode(QLineEdit::Password);
    }else{
        isPassVisible = true;
        ui->btnSHPass->setIcon(QIcon(":/img/images/icon_hide.png"));
        ui->editPass->setEchoMode(QLineEdit::Normal);
    }
}


void ResetView::on_btnSHPConfirm_clicked()
{
    if(isConfirmPassVisible){
        isConfirmPassVisible = false;
        ui->btnSHPConfirm->setIcon(QIcon(":/img/images/icon_show.png"));
        ui->editConfirm->setEchoMode(QLineEdit::Password);
    }else{
        isConfirmPassVisible = true;
        ui->btnSHPConfirm->setIcon(QIcon(":/img/images/icon_hide.png"));
        ui->editConfirm->setEchoMode(QLineEdit::Normal);
    }
}

