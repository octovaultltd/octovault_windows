#ifndef RESETVERIFYVIEW_H
#define RESETVERIFYVIEW_H

#include <QWidget>
#include <QMovie>
#include <QMessageBox>

namespace Ui {
class ResetVerifyView;
}

class ResetVerifyView : public QWidget
{
    Q_OBJECT

public:
    explicit ResetVerifyView(QWidget *parent = nullptr);
    ~ResetVerifyView();

private slots:
    void on_btnVerify_clicked();
    void on_btnBack_clicked();

    void on_btnChangeLogo_clicked();

    void on_btnResend_clicked();

signals:
    void openResetPage();
    void openForgetPage();

private:
    Ui::ResetVerifyView *ui;
    QMovie *movie;
    int logoState;
};

#endif // RESETVERIFYVIEW_H
