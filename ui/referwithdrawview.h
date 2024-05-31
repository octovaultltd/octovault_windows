#ifndef REFERWITHDRAWVIEW_H
#define REFERWITHDRAWVIEW_H

#include <QWidget>

namespace Ui {
class ReferWithdrawView;
}

class ReferWithdrawView : public QWidget
{
    Q_OBJECT

public:
    explicit ReferWithdrawView(QWidget *parent = nullptr);
    ~ReferWithdrawView();

private slots:
    void on_btnBack_clicked();

signals:
    void openReferBalancePage();

private:
    Ui::ReferWithdrawView *ui;
};

#endif // REFERWITHDRAWVIEW_H
