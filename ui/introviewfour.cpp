#include "introviewfour.h"
#include "ui_introviewfour.h"

IntroViewFour::IntroViewFour(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IntroViewFour),
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
}

IntroViewFour::~IntroViewFour()
{
    delete ui;
}


void IntroViewFour::on_btnSignUp_clicked()
{
    emit openSignUpPage();
}


void IntroViewFour::on_btnLogin_clicked()
{
    emit openLoginPage();
}


void IntroViewFour::on_btnChangeLogo_clicked()
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

