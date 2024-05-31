#include "introviewone.h"
#include "ui_introviewone.h"

IntroViewOne::IntroViewOne(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IntroViewOne),
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

IntroViewOne::~IntroViewOne()
{
    delete ui;
}

void IntroViewOne::on_btnNext_clicked()
{
    emit openIntroPageTwo();
}


void IntroViewOne::on_btnChangeLogo_clicked()
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

