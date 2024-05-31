#ifndef ACCOUNTVIEW_H
#define ACCOUNTVIEW_H

#include <QWidget>

namespace Ui {
class AccountView;
}

class AccountView : public QWidget
{
    Q_OBJECT

public:
    explicit AccountView(QWidget *parent = nullptr);
    ~AccountView();

signals:
    void openProfilePage();

private slots:
    void on_btnBack_clicked();

private:
    Ui::AccountView *ui;
};

#endif // ACCOUNTVIEW_H
