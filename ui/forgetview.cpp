#include "forgetview.h"
#include "ui_forgetview.h"
#include "utils/networkmanager.h"

ForgetView::ForgetView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ForgetView),
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
}

ForgetView::~ForgetView()
{
    delete ui;
}

void ForgetView::on_btnSignIn_clicked()
{
    emit openLoginPage();
}

void ForgetView::on_btnSubmit_clicked()
{
    //emit openResetVerifyPage();
    QString email = ui->editEmail->text();
    if(email.isEmpty()){
        QMessageBox alert;
        alert.setText("Email Cannot Be Empty");
        alert.setStandardButtons(QMessageBox::Ok);
        alert.exec();
    }else if(!checkEmailIsValid(email)){
        QMessageBox alert;
        alert.setText("Email Address Invalid");
        alert.setStandardButtons(QMessageBox::Ok);
        alert.exec();
    }else{
        // Show Spinner
        ui->lblSpinner->show();
        movie->start();

        // Make API Call
        auto response = NetworkManager().callForgetAPI(email);
        qDebug() << response;

        // Hide Spinner
        movie->stop();
        ui->lblSpinner->hide();

        // Parse Response
        QMessageBox alert;
        alert.setText(response[1]);
        alert.setStandardButtons(QMessageBox::Ok);
        int action = alert.exec();
        if(action == QMessageBox::Ok){
            LocalDB::setUsername(email);
            emit openResetVerifyPage();
        }
    }
}

bool ForgetView::checkEmailIsValid(QString email){
    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
    mailREX.setPatternSyntax(QRegExp::RegExp);
    return mailREX.exactMatch(email);
}


void ForgetView::on_btnChangeLogo_clicked()
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

