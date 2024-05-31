#ifndef SPLASHVIEW_H
#define SPLASHVIEW_H

#include <QWidget>
#include <QMovie>
#include <QTimer>
#include <QMessageBox>
#include <utils/networkmanager.h>

namespace Ui {
class SplashView;
}

class SplashView : public QWidget
{
    Q_OBJECT

public:
    explicit SplashView(QWidget *parent = nullptr);
    ~SplashView();

signals:
    void openHomePage();
    void openIntroPageOne();
    void openIntroPageFour();

private:
    void getFirestoreData();
    void showAlert(QString msg);

private:
    Ui::SplashView *ui;
    QMovie *movie;

protected:
    void showEvent(QShowEvent *) override;
};

#endif // SPLASHVIEW_H
