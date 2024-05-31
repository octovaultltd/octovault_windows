#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <QWidget>
#include <QMovie>
#include <QMessageBox>

namespace Ui {
class LoginView;
}

class LoginView : public QWidget
{
    Q_OBJECT

public:
    explicit LoginView(QWidget *parent = nullptr);
    ~LoginView();

signals:
    void openSignUpPage();
    void openForgetPage();
    void openHomePage();
    void openEmailVerifyPage();

private slots:
    void on_btnSignUp_clicked();
    void on_btnForget_clicked();
    void on_btnLogin_clicked();
    void on_btnShowHide_clicked();

    void on_btnChangeLogo_clicked();

public slots:
    void resetCredentials();

private:
    Ui::LoginView *ui;
    bool isPassVisible;
    QMovie *movie;
    int logoState;
};

#endif // LOGINVIEW_H
