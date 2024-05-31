#include "loginview.h"
#include "ui_loginview.h"
#include "utils/networkmanager.h"
#include <QDebug>

LoginView::LoginView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginView),
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

    // Set Saved Credentials
    ui->editEmail->setText(LocalDB().getUsername());
    ui->editPass->setText(LocalDB().getPassword());

    // Show/Hide Password
    if(isPassVisible){
        ui->btnShowHide->setIcon(QIcon(":/img/images/icon_hide.png"));
        ui->editPass->setEchoMode(QLineEdit::Normal);
    }else{
        ui->btnShowHide->setIcon(QIcon(":/img/images/icon_show.png"));
        ui->editPass->setEchoMode(QLineEdit::Password);
    }
}

LoginView::~LoginView()
{
    delete ui;
    delete movie;
}

void LoginView::resetCredentials(){
    ui->editEmail->setText(LocalDB().getUsername());
    ui->editPass->setText(LocalDB().getPassword());
}

void LoginView::on_btnSignUp_clicked()
{
    emit openSignUpPage();
}

void LoginView::on_btnForget_clicked()
{
    emit openForgetPage();
}

void LoginView::on_btnShowHide_clicked()
{
    if(isPassVisible){
        isPassVisible = false;
        ui->btnShowHide->setIcon(QIcon(":/img/images/icon_show.png"));
        ui->editPass->setEchoMode(QLineEdit::Password);
    }else{
        isPassVisible = true;
        ui->btnShowHide->setIcon(QIcon(":/img/images/icon_hide.png"));
        ui->editPass->setEchoMode(QLineEdit::Normal);
    }
}

void LoginView::on_btnLogin_clicked()
{
    QString username = ui->editEmail->text();
    QString password = ui->editPass->text();

    if(username.isEmpty() || password.isEmpty()){
        if(username.isEmpty()){
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
    }else{
        // Show Spinner
        ui->lblSpinner->show();
        movie->start();

        // Make API Call
        auto response = NetworkManager().callLoginAPI(username, password);
        qDebug() << response;

        // Hide Spinner
        movie->stop();
        ui->lblSpinner->hide();

        // Parse Response
        if(response[0] == "1"){
            emit openHomePage();
        }else{
            QMessageBox alert;
            alert.setText(response[1]);
            alert.setStandardButtons(QMessageBox::Ok);
            auto action = alert.exec();
            if(action == QMessageBox::Ok){
                if(response[2] == "401"){
                    emit openEmailVerifyPage();
                }
            }
        }
    }
}

void LoginView::on_btnChangeLogo_clicked()
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

