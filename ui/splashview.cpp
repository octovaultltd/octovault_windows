#include "splashview.h"
#include "ui_splashview.h"

SplashView::SplashView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SplashView)
{
    ui->setupUi(this);

    // initialize Spinner
    movie = new QMovie(":/img/images/spinner.gif");
    ui->lblSpinner->setMovie(movie);
}

SplashView::~SplashView()
{
    delete ui;
    delete movie;
}

void SplashView::getFirestoreData()
{
    // Show Spinner
    ui->lblSpinner->show();
    movie->start();

    // Make API Call
    auto response = NetworkManager().getFirestoreData();

    // Hide Spinner
    movie->stop();
    ui->lblSpinner->hide();

    // Parse Response
    if(response == "Success"){
        if(LocalDB::isFirstLaunch()){
            emit openIntroPageOne();
        }else{
            if(LocalDB::isLoggedIn()){
                emit openHomePage();
            }else{
                emit openIntroPageFour();
            }
        }
    }else{
        showAlert(response);
    }
}

void SplashView::showAlert(QString msg)
{
    QMessageBox alert;
    alert.setText(msg);
    alert.setStandardButtons(QMessageBox::Retry);
    int result = alert.exec();
    if(result == QMessageBox::Retry){
        qDebug() << "Retry Pressed";
        getFirestoreData();
    }
}

void SplashView::showEvent(QShowEvent *)
{
    QTimer::singleShot(0, this, &SplashView::getFirestoreData);
}
