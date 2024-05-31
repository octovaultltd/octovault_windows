#ifndef INTROVIEWFOUR_H
#define INTROVIEWFOUR_H

#include <QWidget>

namespace Ui {
class IntroViewFour;
}

class IntroViewFour : public QWidget
{
    Q_OBJECT

public:
    explicit IntroViewFour(QWidget *parent = nullptr);
    ~IntroViewFour();

signals:
    void openSignUpPage();
    void openLoginPage();

private slots:
    void on_btnSignUp_clicked();
    void on_btnLogin_clicked();

    void on_btnChangeLogo_clicked();

private:
    Ui::IntroViewFour *ui;
    int logoState;
};

#endif // INTROVIEWFOUR_H
