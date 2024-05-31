#ifndef FORGETVIEW_H
#define FORGETVIEW_H

#include <QWidget>
#include <QMovie>
#include <QMessageBox>

namespace Ui {
class ForgetView;
}

class ForgetView : public QWidget
{
    Q_OBJECT

public:
    explicit ForgetView(QWidget *parent = nullptr);
    ~ForgetView();

signals:
    void openLoginPage();
    void openResetVerifyPage();

private slots:
    void on_btnSignIn_clicked();
    void on_btnSubmit_clicked();
    bool checkEmailIsValid(QString email);

    void on_btnChangeLogo_clicked();

private:
    Ui::ForgetView *ui;
    QMovie *movie;
    int logoState;
};

#endif // FORGETVIEW_H
