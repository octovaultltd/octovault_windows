#ifndef HOMEVIEW_H
#define HOMEVIEW_H

#include <QWidget>
#include <QTimer>
#include <QElapsedTimer>
#include <QQmlContext>
#include "vpn/openconnectconnection.h"
#include "utils/markermodel.h"

namespace Ui {
class HomeView;
}

class HomeView : public QWidget
{
    Q_OBJECT

public:
    explicit HomeView(QWidget *parent = nullptr);
    ~HomeView();

signals:
    void openLoginPage();

public slots:
    void goToSubscriptionPage();
    void goToSettingsPage();
    void goToDevicePage();
    void goToReferPage();
    void goToSupportPage();
    void goToAboutPage();
    void goToLoginPage();
    void goToProfilePage();
    void goToReferBalancePage();
    void goToReferWithdrawPage();

private:
    Ui::HomeView *ui;
    int m_state;
    QTimer* m_statsTimer;
    QElapsedTimer sessionTimer;
    MarkerModel marker_model;
    void connectVPN();
    void updateUI();
    void updateMapView();

private slots:
    void onStatusChanged(OpenConnectConnection::Status status);
    void updateStats(uint64_t tx, uint64_t rx);
    QString normalizeByteSize(uint64_t bytes);
    void onStatsTimeout();
    void on_btnLocation_clicked();
    void on_btnProfile_clicked();
    void on_btnConnect_clicked();
};

#endif // HOMEVIEW_H
