#ifndef SIGNUPVIEW_H
#define SIGNUPVIEW_H

#include <QWidget>
#include <QMovie>
#include <QMessageBox>

namespace Ui {
class SignUpView;
}

class SignUpView : public QWidget
{
    Q_OBJECT

public:
    explicit SignUpView(QWidget *parent = nullptr);
    ~SignUpView();

signals:
    void openLoginPage();
    void resetLoginCredentials();
    void openEmailVerifyPage();

private slots:
    void on_btnSignUp_clicked();
    void on_btnSignIn_clicked();
    void on_btnSHPass_clicked();
    void on_btnSHPConfirm_clicked();
    bool checkEmailIsValid(QString email);

    void on_btnTerms_clicked();

    void on_btnPrivacy_clicked();

    void on_btnChangeLogo_clicked();

private:
    Ui::SignUpView *ui;
    QMovie *movie;
    bool isPassVisible;
    bool isConfirmPassVisible;
    int logoState;
};

#endif // SIGNUPVIEW_H
