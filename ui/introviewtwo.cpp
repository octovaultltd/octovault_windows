#include "introviewtwo.h"
#include "ui_introviewtwo.h"

IntroViewTwo::IntroViewTwo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IntroViewTwo),
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

IntroViewTwo::~IntroViewTwo()
{
    delete ui;
}

void IntroViewTwo::on_btnBack_clicked()
{
    emit openIntroPageOne();
}


void IntroViewTwo::on_btnNext_clicked()
{
    emit openIntroPageThree();
}


void IntroViewTwo::on_btnChangeLogo_clicked()
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

