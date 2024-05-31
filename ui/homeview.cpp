#include "homeview.h"
#include "ui_homeview.h"
#include "utils/commondata.h"
#include "utils/localdb.h"
#include "utils/networkmanager.h"
#include <cmath>
#include <QString>
#include <QQuickItem>

HomeView::HomeView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeView),
    m_state(0)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    // Setup Map
    updateMapView();

    // For Periodically fetching OpenConnect Stats
    m_statsTimer = new QTimer(this);
    connect(m_statsTimer, &QTimer::timeout, this, &HomeView::onStatsTimeout);

    connect(CommonData::getVPNConnection().get(), &OpenConnectConnection::statusChanged, this, &HomeView::onStatusChanged, Qt::QueuedConnection);
    connect(CommonData::getVPNConnection().get(), &OpenConnectConnection::statsChanged, this, &HomeView::updateStats, Qt::QueuedConnection);

    // Listeners
    connect(ui->profile, &ProfileView::openSubscriptionPage, this, &HomeView::goToSubscriptionPage);
    connect(ui->profile, &ProfileView::openSettingsPage, this, &HomeView::goToSettingsPage);
    connect(ui->profile, &ProfileView::openDevicePage, this, &HomeView::goToDevicePage);
    connect(ui->profile, &ProfileView::openReferPage, this, &HomeView::goToReferPage);
    connect(ui->profile, &ProfileView::openSupportPage, this, &HomeView::goToSupportPage);
    connect(ui->profile, &ProfileView::openAboutPage, this, &HomeView::goToAboutPage);
    connect(ui->profile, &ProfileView::openLoginPage, this, &HomeView::goToLoginPage);
    connect(ui->about, &AboutView::openProfilePage, this, &HomeView::goToProfilePage);
    connect(ui->account, &AccountView::openProfilePage, this, &HomeView::goToProfilePage);
    connect(ui->device, &DeviceView::openProfilePage, this, &HomeView::goToProfilePage);
    connect(ui->premium, &PremiumView::openProfilePage, this, &HomeView::goToProfilePage);
    connect(ui->refer, &ReferView::openProfilePage, this, &HomeView::goToProfilePage);
    connect(ui->settings, &SettingsView::openProfilePage, this, &HomeView::goToProfilePage);
    connect(ui->settings, &SettingsView::openLoginPage, this, &HomeView::goToLoginPage);
    connect(ui->support, &SupportView::openProfilePage, this, &HomeView::goToProfilePage);
    connect(ui->tools, &ToolsView::openProfilePage, this, &HomeView::goToProfilePage);
    connect(ui->refer, &ReferView::openReferBalancePage, this, &HomeView::goToReferBalancePage);
    connect(ui->referBalance, &ReferBalanceView::openReferPage, this, &HomeView::goToReferPage);
    connect(ui->referBalance, &ReferBalanceView::openReferWithdrawPage, this, &HomeView::goToReferWithdrawPage);
    connect(ui->referWithdraw, &ReferWithdrawView::openReferBalancePage, this, &HomeView::goToReferBalancePage);
    connect(ui->server, &ServerView::connectVPNFromServerPage, this, &HomeView::connectVPN);

    // Update UI
    updateUI();
}

HomeView::~HomeView()
{
    delete ui;
}

void HomeView::onStatusChanged(OpenConnectConnection::Status status)
{
    auto opcState = static_cast<OpenConnectConnection::Status>(status);

    qDebug() << "Connect Status : "+ QString::number( opcState );

    if(opcState == OpenConnectConnection::CONNECTING){
        m_state = 1;
        ui->btnConnect->setText("CONNECTING");
        update();
    }else if(opcState == OpenConnectConnection::IDLING){
        m_state = 3;
        update();
    }else if(opcState == OpenConnectConnection::IDLE){
        m_state = 0;
        ui->btnConnect->setText("DISCONNECTING");
        ui->btnConnect->setText("CONNECT");
        ui->btnConnect->setStyleSheet("QPushButton{background:#FACA7F;border-color:transparent;color:#000000;border-radius: 10px;}");
        QPixmap upPixmap(":/img/images/icon_upload.png");
        ui->lblUpLogo->setPixmap(upPixmap);
        ui->lblUpLogo->setScaledContents(true);
        QPixmap downPixmap(":/img/images/icon_download.png");
        ui->lblDownLogo->setPixmap(downPixmap);
        ui->lblDownLogo->setScaledContents(true);
        if(m_statsTimer->isActive()){
            m_statsTimer->stop();
        }
        update();
        updateUI();
    }else if(opcState == OpenConnectConnection::CONNECTED){
        m_state = 2;
        ui->btnConnect->setText("DISCONNECT");
        ui->btnConnect->setStyleSheet("QPushButton{background:#E84E4E;border-color:transparent;color:#FFFFFF;border-radius: 10px;}");
        QPixmap upPixmap(":/img/images/icon_upload_yellow.png");
        ui->lblUpLogo->setPixmap(upPixmap);
        ui->lblUpLogo->setScaledContents(true);
        QPixmap downPixmap(":/img/images/icon_download_yellow.png");
        ui->lblDownLogo->setPixmap(downPixmap);
        ui->lblDownLogo->setScaledContents(true);
        m_statsTimer->start(1000);
        update();
        updateUI();
    }
}

void HomeView::updateStats(uint64_t tx, uint64_t rx)
{
    ui->lblDownSpeed->setText(normalizeByteSize(rx));
    ui->lblUpSpeed->setText(normalizeByteSize(tx));
    ui->lblOne->setText(QTime::fromMSecsSinceStartOfDay(sessionTimer.elapsed()).toString("hh:mm:ss"));
}

QString HomeView::normalizeByteSize(uint64_t bytes)
{
    const unsigned unit = 1024; // TODO: add support for SI units? (optional)
    if (bytes < unit) {
        return QString("%1 B").arg(QString::number(bytes));
    }
    const int exp = static_cast<int>(std::log(bytes) / std::log(unit));
    static const char suffixChar[] = "KMGTPE";
    return QString("%1 %2B").arg(QString::number(bytes / std::pow(unit, exp), 'f', 1)).arg(suffixChar[exp - 1]);
}

void HomeView::onStatsTimeout()
{
    CommonData::getVPNConnection()->requestStats();
}

void HomeView::on_btnLocation_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->btnLocation->setIcon(QIcon(":img/images/icon_location_black.png"));
    ui->btnLocation->setStyleSheet("QPushButton{background:#FACA7F;border-radius: 10px;color:#000000;}");
    ui->btnProfile->setIcon(QIcon(":img/images/icon_profile_round.png"));
    ui->btnProfile->setStyleSheet("QPushButton{background:transparent;border-radius: 10px;color:#818083;border: 1px solid #36353a;}");
}

void HomeView::on_btnProfile_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
    ui->btnLocation->setIcon(QIcon(":img/images/icon_location.png"));
    ui->btnLocation->setStyleSheet("QPushButton{background:transparent;border-radius: 10px;color:#818083;border: 1px solid #36353a;}");
    ui->btnProfile->setIcon(QIcon(":img/images/icon_profile_round_black.png"));
    ui->btnProfile->setStyleSheet("QPushButton{background:#FACA7F;border-radius: 10px;color:#000000;}");
}

void HomeView::on_btnConnect_clicked()
{
    connectVPN();
}

void HomeView::connectVPN()
{
    qDebug() << "Connect Button Pressed";
    updateUI();
    if(m_state == 0){
        QJsonObject selectedServer = CommonData::getServerByIPID(LocalDB().getActiveServerID());
        QString server = selectedServer.value("ip").toString();
        QString config = selectedServer.value("config").toString();
        int type = selectedServer.value("type").toInt();
        if(server.contains("8.8.8.8")){
            QMessageBox alert;
            alert.setText("You are using free version of OctoVault VPN.\n\nBuy now to unlock all server");
            alert.setStandardButtons(QMessageBox::Ok);
            auto action = alert.exec();
            if(action == QMessageBox::Ok){
                //emit openPremiumPage();
            }
        }else{
            CommonData::getVPNConnection()->setServer(std::make_shared<OpenConnectServer>(server));
            CommonData::getVPNConnection()->setType(type);
            CommonData::getVPNConnection()->setOpenConfig(config, server);
            auto connectResult = CommonData::getVPNConnection()->connect();
            qDebug() << "Connect Result : "+ QString::number(connectResult);
        }
    }else{
        CommonData::getVPNConnection()->disconnect();
    }
}

void HomeView::updateUI()
{
    QJsonObject selectedServer = CommonData::getServerByIPID(LocalDB().getActiveServerID());
    QPixmap pixmap(CommonData().getFlagImage(selectedServer.value("countryCode").toString().toInt()));
    ui->lblServerFlag->setPixmap(pixmap);
    ui->lblServerFlag->setScaledContents(true);
    ui->lblServerName->setText(selectedServer.value("ipName").toString()+" "+selectedServer.value("countryName").toString());

    updateMapView();

    if(m_state == 2){
        // Connected
        sessionTimer.start();
        auto response = NetworkManager().getPublicIP();
        qDebug() << response;
        ui->lblThree->setText(response[1]);
    }else if(m_state == 0){
        // Disconnected
        sessionTimer.invalidate();
        QJsonObject recentServer = CommonData::getServerByIPID(LocalDB().getRecentServerID());
        ui->lblThree->setText(recentServer.value("ipName").toString()+" "+recentServer.value("countryName").toString());
        auto response = NetworkManager().getPublicIP();
        qDebug() << response;
        ui->lblOne->setText(response[1]);
    }
}

void HomeView::goToSubscriptionPage()
{
    //ui->stackedWidget->setCurrentIndex(2);
}

void HomeView::goToSettingsPage()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void HomeView::goToDevicePage()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void HomeView::goToReferPage()
{
    ui->stackedWidget->setCurrentIndex(8);
}

void HomeView::goToSupportPage()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void HomeView::goToAboutPage()
{
    ui->stackedWidget->setCurrentIndex(7);
}

void HomeView::goToProfilePage()
{
    ui->stackedWidget->setCurrentIndex(9);
}

void HomeView::goToReferBalancePage()
{
    ui->stackedWidget->setCurrentIndex(10);
}

void HomeView::goToReferWithdrawPage()
{
    ui->stackedWidget->setCurrentIndex(11);
}

void HomeView::goToLoginPage()
{
    emit openLoginPage();
}

void HomeView::updateMapView()
{
    // Get Selected Server
    QJsonObject selectedServer = CommonData::getServerByIPID(LocalDB().getActiveServerID());

    // Setup Map
    ui->quickWidget->rootContext()->setContextProperty("marker_model", &marker_model);
    ui->quickWidget->setSource(QUrl("qrc:/mapview.qml"));

    // Update Coordinates
    auto rootObject = ui->quickWidget->rootObject();
    auto map = rootObject->findChild<QQuickItem*>("map");
    auto coordinates = map->property("center").value<QGeoCoordinate>();
    coordinates.setLatitude(selectedServer.value("lat").toString().toDouble());
    coordinates.setLongitude(selectedServer.value("lng").toString().toDouble());
    map->setProperty("center", QVariant::fromValue<QGeoCoordinate>(coordinates));

    // Set Marker
    marker_model.setMaxMarkers(1);
    marker_model.moveMarker(QGeoCoordinate(selectedServer.value("lat").toString().toDouble(), selectedServer.value("lng").toString().toDouble()));
}

