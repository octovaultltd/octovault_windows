#ifndef PROFILEVIEW_H
#define PROFILEVIEW_H

#include <QWidget>

namespace Ui {
class ProfileView;
}

class ProfileView : public QWidget
{
    Q_OBJECT

public:
    explicit ProfileView(QWidget *parent = nullptr);
    ~ProfileView();

signals:
    void openSubscriptionPage();
    void openSettingsPage();
    void openDevicePage();
    void openReferPage();
    void openSupportPage();
    void openAboutPage();
    void openLoginPage();

private slots:
    void on_btnSubscription_clicked();

    void on_btnSettings_clicked();

    void on_btnDevice_clicked();

    void on_btnRefer_clicked();

    void on_btnSupport_clicked();

    void on_btnAbout_clicked();

    void on_btnLogout_clicked();

private:
    Ui::ProfileView *ui;
    void updateView();

protected:
    void showEvent(QShowEvent *) override;
};

#endif // PROFILEVIEW_H
