#include "resetverifyview.h"
#include "ui_resetverifyview.h"
#include "utils/networkmanager.h"

ResetVerifyView::ResetVerifyView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResetVerifyView),
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

    ui->leOne->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->leTwo->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->leThree->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->leFour->setAttribute(Qt::WA_MacShowFocusRect, 0);

    // Initialize Spinner
    movie = new QMovie(":/img/images/spinner.gif");
    ui->lblSpinner->setMovie(movie);
}

ResetVerifyView::~ResetVerifyView()
{
    delete ui;
}


void ResetVerifyView::on_btnVerify_clicked()
{
    //emit openResetPage();
    QString username = LocalDB::getUsername();
    QString tokenPartOne = ui->leOne->text();
    QString tokenPartTwo = ui->leTwo->text();
    QString tokenPartThree = ui->leThree->text();
    QString tokenPartFour = ui->leFour->text();
    QString token = tokenPartOne+tokenPartTwo+tokenPartThree+tokenPartFour;

    if(username.isEmpty() || token.isEmpty()){
        if(username.isEmpty()){
            QMessageBox alert;
            alert.setText("Username Cannot Be Empty");
            alert.setStandardButtons(QMessageBox::Ok);
            alert.exec();
        }else if(token.isEmpty()){
            QMessageBox alert;
            alert.setText("Token Cannot Be Empty");
            alert.setStandardButtons(QMessageBox::Ok);
            alert.exec();
        }
    }else{
        // Show Spinner
        ui->lblSpinner->show();
        movie->start();

        // Make API Call
        auto response = NetworkManager().callTokenVerifyAPI(username, token, "2");
        qDebug() << response;

        // Hide Spinner
        movie->stop();
        ui->lblSpinner->hide();

        // Parse Response
        if(response[0] == "1"){
            LocalDB::setLastOTP(token);
            emit openResetPage();
        }else{
            QMessageBox alert;
            alert.setText(response[1]);
            alert.setStandardButtons(QMessageBox::Ok);
            alert.exec();
        }
    }
}


void ResetVerifyView::on_btnBack_clicked()
{
    emit openForgetPage();
}


void ResetVerifyView::on_btnChangeLogo_clicked()
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


void ResetVerifyView::on_btnResend_clicked()
{
    ui->lblSpinner->show();
    movie->start();

    // Make API Call
    auto response = NetworkManager().callResendTokenAPI(LocalDB::getUsername());
    qDebug() << response;

    // Hide Spinner
    movie->stop();
    ui->lblSpinner->hide();

    // Parse Response
    QMessageBox alert;
    alert.setText(response[1]);
    alert.setStandardButtons(QMessageBox::Ok);
    alert.exec();
}

