#ifndef SUPPORTVIEW_H
#define SUPPORTVIEW_H

#include <QWidget>

namespace Ui {
class SupportView;
}

class SupportView : public QWidget
{
    Q_OBJECT

public:
    explicit SupportView(QWidget *parent = nullptr);
    ~SupportView();

signals:
    void openProfilePage();

private slots:
    void on_btnBack_clicked();

    void on_btnLiveChat_clicked();

    void on_btnEmail_clicked();

    void on_btnFaq_clicked();

private:
    Ui::SupportView *ui;
};

#endif // SUPPORTVIEW_H
