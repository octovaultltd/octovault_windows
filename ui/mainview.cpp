#include "mainview.h"
#include "ui_mainview.h"
#include <QDebug>
#include "utils/localdb.h"

MainView::MainView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainView),
    m_state(0),
    shouldQuit(false)
{
    ui->setupUi(this);

    // Initialize System Tray
    loadTray();

//    QSettings settings("OctoVault", "Kolpolok Limited");
//    settings.clear();

    // Check If User Is Logged In Or Not
    if(LocalDB::isLoggedIn()){
        CommonData::getVPNConnection()->setUsername(LocalDB().getUsername());
        CommonData::getVPNConnection()->setPassword(LocalDB().getPassword());
        CommonData::getVPNConnection()->setOpenConfig("", "");
        ui->stackedWidget->setCurrentIndex(4);
    }else{
        if(LocalDB::isFirstLaunch()){
            ui->stackedWidget->setCurrentIndex(5);
        }else{
            ui->stackedWidget->setCurrentIndex(8);
        }
    }

    // Listeners
    connect(ui->login, &LoginView::openSignUpPage, this, &MainView::goToSignUpPage);
    connect(ui->login, &LoginView::openForgetPage, this, &MainView::goToForgetPage);
    connect(ui->splash, &SplashView::openHomePage, this, &MainView::goToHomePage);
    connect(ui->signup, &SignUpView::openLoginPage, this, &MainView::goToLoginPage);
    connect(ui->forget, &ForgetView::openLoginPage, this, &MainView::goToLoginPage);
    connect(ui->login, &LoginView::openHomePage, this, &MainView::goToHomePage);
    connect(ui->signup, &SignUpView::resetLoginCredentials, ui->login, &LoginView::resetCredentials);
    connect(ui->home, &HomeView::openLoginPage, this, &MainView::goToLoginPage);
    connect(ui->splash, &SplashView::openIntroPageOne, this, &MainView::goToIntroPageOne);
    connect(ui->introOne, &IntroViewOne::openIntroPageTwo, this, &MainView::goToIntroPageTwo);
    connect(ui->introTwo, &IntroViewTwo::openIntroPageOne, this, &MainView::goToIntroPageOne);
    connect(ui->introTwo, &IntroViewTwo::openIntroPageThree, this, &MainView::goToIntroPageThree);
    connect(ui->introThree, &IntroViewThree::openIntroPageTwo, this, &MainView::goToIntroPageTwo);
    connect(ui->introThree, &IntroViewThree::openIntroPageFour, this, &MainView::goToIntroPageFour);
    connect(ui->introFour, &IntroViewFour::openLoginPage, this, &MainView::goToLoginPage);
    connect(ui->introFour, &IntroViewFour::openSignUpPage, this, &MainView::goToSignUpPage);
    connect(ui->signup, &SignUpView::openEmailVerifyPage, this, &MainView::goToEmailVerifyPage);
    connect(ui->login, &LoginView::openEmailVerifyPage, this, &MainView::goToEmailVerifyPage);
    connect(ui->emailVerify, &EmailVerifyView::openLoginPage, this, &MainView::goToLoginPage);
    connect(ui->emailVerify, &EmailVerifyView::openSignUpPage, this, &MainView::goToSignUpPage);
    connect(ui->forget, &ForgetView::openResetVerifyPage, this, &MainView::goToResetVerifyPage);
    connect(ui->resetVerify, &ResetVerifyView::openResetPage, this, &MainView::goToResetPage);
    connect(ui->resetVerify, &ResetVerifyView::openForgetPage, this, &MainView::goToForgetPage);
    connect(ui->reset, &ResetView::openLoginPage, this, &MainView::goToLoginPage);
    connect(ui->reset, &ResetView::openResetVerifyPage, this, &MainView::goToResetVerifyPage);
    connect(CommonData::getVPNConnection().get(), &OpenConnectConnection::statusChanged, this, &MainView::onStatusChanged, Qt::QueuedConnection);
}

MainView::~MainView()
{
    delete ui;
}

void MainView::loadTray(){
    if(QSystemTrayIcon::isSystemTrayAvailable()){
        // Initialize System Tray
        systemTray = new QSystemTrayIcon(this);
        // Initialize Menu
        auto trayMenu = new QMenu(this);
        // Add Buttons/Actions In Menu
        auto quitAction = new QAction("Quit", this);
        trayAction = new QAction("Connect", this);
        // Define Quit Action Function
        connect(quitAction, &QAction::triggered, this, [=](bool){
            if(m_state == 2){
                shouldQuit = true;
                CommonData::getVPNConnection()->disconnect();
            }else{
                qApp->quit();
            }
        });
        // Define Connect Action Function
        connect(trayAction, &QAction::triggered, this, [=](bool){
            if(m_state == 2){
                auto connectResult = CommonData::getVPNConnection()->connect();
                qDebug() << "Connect Result : "+ QString::number(connectResult);
            }else{
                CommonData::getVPNConnection()->disconnect();
            }
        });
        trayMenu->addAction(quitAction);
        trayMenu->addAction(trayAction);
        // Add Menu In System Tray
        systemTray->setContextMenu(trayMenu);
        // Add Double Click Action
        connect(systemTray, &QSystemTrayIcon::activated, this, [=](QSystemTrayIcon::ActivationReason reason){
            if(reason == QSystemTrayIcon::DoubleClick)
                this->show();
        });
        // Add System Tray Icon And Show
        QIcon trayIcon(":/img/images/tray_icon_disconnected.png");
        systemTray->setIcon(trayIcon);
        systemTray->show();
    }else{
        qDebug()<<"System Doesn't Support Tray";
        systemTray = nullptr;
    }
}

void MainView::onStatusChanged(int state)
{
    auto opcState = static_cast<OpenConnectConnection::Status>(state);

    if(opcState == OpenConnectConnection::CONNECTING)
    {
        trayAction->setText("Connecting");
        trayAction->setDisabled(true);
        QIcon icon(":/img/images/tray_icon_connecting.png");
        systemTray->setIcon(icon);
    }
    else if(opcState == OpenConnectConnection::IDLE)
    {
        trayAction->setText("Connect");
        trayAction->setDisabled(false);
        QIcon icon(":/img/images/tray_icon_disconnected.png");
        systemTray->setIcon(icon);
        if(shouldQuit){
            shouldQuit = false;
            qApp->exit();
        }
    }
    else if(opcState == OpenConnectConnection::CONNECTED)
    {
        trayAction->setText("Disconnect");
        trayAction->setDisabled(false);
        QIcon icon(":/img/images/tray_icon_connected.png");
        systemTray->setIcon(icon);
    }
    else if(opcState == OpenConnectConnection::IDLING)
    {
        trayAction->setText("Disconnecting");
        trayAction->setDisabled(true);
        QIcon icon(":/img/images/tray_icon_connecting.png");
        systemTray->setIcon(icon);
    }
}

void MainView::goToLoginPage(){
    LocalDB().setLoggedIn(false);
    ui->stackedWidget->setCurrentIndex(1);
}

void MainView::goToSignUpPage(){
    ui->stackedWidget->setCurrentIndex(2);
}

void MainView::goToForgetPage(){
    ui->stackedWidget->setCurrentIndex(3);
}

void MainView::goToHomePage(){
    ui->stackedWidget->setCurrentIndex(4);
}

void MainView::goToIntroPageOne(){
    ui->stackedWidget->setCurrentIndex(5);
}

void MainView::goToIntroPageTwo(){
    ui->stackedWidget->setCurrentIndex(6);
}

void MainView::goToIntroPageThree(){
    ui->stackedWidget->setCurrentIndex(7);
}

void MainView::goToIntroPageFour(){
    LocalDB().setFirstLaunch(false);
    ui->stackedWidget->setCurrentIndex(8);
}

void MainView::goToResetPage(){
    ui->stackedWidget->setCurrentIndex(9);
}

void MainView::goToEmailVerifyPage(){
    ui->stackedWidget->setCurrentIndex(10);
}

void MainView::goToResetVerifyPage(){
    ui->stackedWidget->setCurrentIndex(11);
}
