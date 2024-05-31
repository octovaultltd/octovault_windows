#include "introviewthree.h"
#include "ui_introviewthree.h"

IntroViewThree::IntroViewThree(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IntroViewThree),
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

IntroViewThree::~IntroViewThree()
{
    delete ui;
}

void IntroViewThree::on_btnNext_clicked()
{
    emit openIntroPageFour();
}


void IntroViewThree::on_btnBack_clicked()
{
    emit openIntroPageTwo();
}


void IntroViewThree::on_btnChangeLogo_clicked()
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

