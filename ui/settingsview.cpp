#include "settingsview.h"
#include "ui_settingsview.h"
#include "utils/networkmanager.h"

SettingsView::SettingsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsView)
{
    ui->setupUi(this);

    // Initialize Spinner
    movie = new QMovie(":/img/images/spinner.gif");
    ui->lblSpinner->setMovie(movie);
}

SettingsView::~SettingsView()
{
    delete ui;
}

void SettingsView::on_btnBack_clicked()
{
    emit openProfilePage();
}

void SettingsView::on_btnDelete_clicked()
{
    // Show Spinner
    ui->lblSpinner->show();
    movie->start();

    // Make API Call
    auto response = NetworkManager().callDeleteAccountAPI();
    qDebug() << response;

    // Hide Spinner
    movie->stop();
    ui->lblSpinner->hide();

    // Parse Response
    if(response[0] == "1"){
        emit openLoginPage();
    }else{
        QMessageBox alert;
        alert.setText(response[1]);
        alert.setStandardButtons(QMessageBox::Ok);
        alert.exec();
    }
}

