#ifndef RESETVIEW_H
#define RESETVIEW_H

#include <QWidget>
#include <QMovie>
#include <QMessageBox>

namespace Ui {
class ResetView;
}

class ResetView : public QWidget
{
    Q_OBJECT

public:
    explicit ResetView(QWidget *parent = nullptr);
    ~ResetView();

private slots:
    void on_btnSave_clicked();

    void on_btnChangeLogo_clicked();

    void on_btnBack_clicked();

    void on_btnSHPass_clicked();

    void on_btnSHPConfirm_clicked();

signals:
    void openLoginPage();
    void openResetVerifyPage();

private:
    Ui::ResetView *ui;
    QMovie *movie;
    int logoState;
    bool isPassVisible;
    bool isConfirmPassVisible;
};

#endif // RESETVIEW_H
