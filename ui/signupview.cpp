#include "signupview.h"
#include "ui_signupview.h"
#include "utils/networkmanager.h"
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

SignUpView::SignUpView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignUpView),
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

    // Initialize Spinner
    movie = new QMovie(":/img/images/spinner.gif");
    ui->lblSpinner->setMovie(movie);

    // Remove Default Frame
    ui->editEmail->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->editPass->setAttribute(Qt::WA_MacShowFocusRect, 0);
    ui->editConfirm->setAttribute(Qt::WA_MacShowFocusRect, 0);
}

SignUpView::~SignUpView()
{
    delete ui;
    delete movie;
}

void SignUpView::on_btnSignIn_clicked()
{
    emit openLoginPage();
}

void SignUpView::on_btnSignUp_clicked()
{

    //emit openEmailVerifyPage();

    QString email = ui->editEmail->text();
    QString password = ui->editPass->text();
    QString confirm = ui->editConfirm->text();

    if(email.isEmpty() || password.isEmpty()){
        if(email.isEmpty()){
            QMessageBox alert;
            alert.setText("Username Cannot Be Empty");
            alert.setStandardButtons(QMessageBox::Ok);
            alert.exec();
        }else if(password.isEmpty()){
            QMessageBox alert;
            alert.setText("Password Cannot Be Empty");
            alert.setStandardButtons(QMessageBox::Ok);
            alert.exec();
        }
    }else if(password != confirm){
        QMessageBox alert;
        alert.setText("Password Must Match");
        alert.setStandardButtons(QMessageBox::Ok);
        alert.exec();
    }else if(!checkEmailIsValid(email)){
        QMessageBox alert;
        alert.setText("Email Address Invalid");
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
        auto response = NetworkManager().callSignUpAPI(email, password);
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
                emit openEmailVerifyPage();
            }
        }
    }
}

void SignUpView::on_btnSHPass_clicked()
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

void SignUpView::on_btnSHPConfirm_clicked()
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

bool SignUpView::checkEmailIsValid(QString email){
    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
    mailREX.setPatternSyntax(QRegExp::RegExp);
    return mailREX.exactMatch(email);
}

void SignUpView::on_btnTerms_clicked()
{
    QString url = "https://octovaultvpn.com/t-c";
    QDesktopServices::openUrl(QUrl(url));
}


void SignUpView::on_btnPrivacy_clicked()
{
    QString url = "https://octovaultvpn.com/privacy-policy";
    QDesktopServices::openUrl(QUrl(url));
}


void SignUpView::on_btnChangeLogo_clicked()
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

