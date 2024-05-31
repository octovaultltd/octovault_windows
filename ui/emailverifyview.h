#ifndef EMAILVERIFYVIEW_H
#define EMAILVERIFYVIEW_H

#include <QWidget>
#include <QMovie>
#include <QMessageBox>

namespace Ui {
class EmailVerifyView;
}

class EmailVerifyView : public QWidget
{
    Q_OBJECT

public:
    explicit EmailVerifyView(QWidget *parent = nullptr);
    ~EmailVerifyView();

signals:
    void openLoginPage();
    void openSignUpPage();

private slots:
    void on_btnVerify_clicked();
    void on_btnCancel_clicked();

    void on_btnChangeLogo_clicked();

    void on_btnResend_clicked();

private:
    Ui::EmailVerifyView *ui;
    QMovie *movie;
    int logoState;
};

#endif // EMAILVERIFYVIEW_H
