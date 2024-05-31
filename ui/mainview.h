#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>
#include "vpn/openconnectconnection.h"

namespace Ui {
class MainView;
}

class MainView : public QWidget
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = nullptr);
    ~MainView();

private slots:
    void onStatusChanged(int state);

public slots:
    void goToLoginPage();
    void goToSignUpPage();
    void goToForgetPage();
    void goToResetPage();
    void goToEmailVerifyPage();
    void goToResetVerifyPage();
    void goToHomePage();
    void goToIntroPageOne();
    void goToIntroPageTwo();
    void goToIntroPageThree();
    void goToIntroPageFour();

private:
    void loadTray();

private:
    Ui::MainView *ui;
    QSystemTrayIcon* systemTray;
    QAction* trayAction;
    int m_state;
    bool shouldQuit;

};

#endif // MAINVIEW_H
