#ifndef REFERVIEW_H
#define REFERVIEW_H

#include <QWidget>

namespace Ui {
class ReferView;
}

class ReferView : public QWidget
{
    Q_OBJECT

public:
    explicit ReferView(QWidget *parent = nullptr);
    ~ReferView();

signals:
    void openProfilePage();
    void openReferBalancePage();

private slots:
    void on_btnBack_clicked();

    void on_btnStart_clicked();

private:
    Ui::ReferView *ui;
};

#endif // REFERVIEW_H
