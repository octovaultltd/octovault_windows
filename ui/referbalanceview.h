#ifndef REFERBALANCEVIEW_H
#define REFERBALANCEVIEW_H

#include <QWidget>
#include <QMovie>
#include <QMessageBox>
#include "utils/networkmanager.h"
#include <QDebug>

namespace Ui {
class ReferBalanceView;
}

class ReferBalanceView : public QWidget
{
    Q_OBJECT

public:
    explicit ReferBalanceView(QWidget *parent = nullptr);
    ~ReferBalanceView();

private slots:
    void on_btnBack_clicked();

    void on_btnWithdraw_clicked();

    void on_btnCopy_clicked();

    void on_btnShare_clicked();

    void on_btnApply_clicked();

signals:
    void openReferPage();
    void openReferWithdrawPage();

private:
    Ui::ReferBalanceView *ui;
    QMovie *movie;
    void getReferData();
    void updateUI();
    bool withdrawEnabled;

protected:
    void showEvent(QShowEvent *) override;
};

#endif // REFERBALANCEVIEW_H
