#ifndef PREMIUMVIEW_H
#define PREMIUMVIEW_H

#include <QWidget>

namespace Ui {
class PremiumView;
}

class PremiumView : public QWidget
{
    Q_OBJECT

public:
    explicit PremiumView(QWidget *parent = nullptr);
    ~PremiumView();

signals:
    void openProfilePage();

private slots:
    void on_btnBack_clicked();

private:
    Ui::PremiumView *ui;
};

#endif // PREMIUMVIEW_H
