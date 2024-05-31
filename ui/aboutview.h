#ifndef ABOUTVIEW_H
#define ABOUTVIEW_H

#include <QWidget>

namespace Ui {
class AboutView;
}

class AboutView : public QWidget
{
    Q_OBJECT

public:
    explicit AboutView(QWidget *parent = nullptr);
    ~AboutView();

signals:
    void openProfilePage();
private:
    Ui::AboutView *ui;

private slots:
    void on_btnBack_clicked();
    void on_btnFb_clicked();
    void on_btnInsta_clicked();
    void on_btnYoutube_clicked();
    void on_btnLinkedIn_clicked();
    void on_btnTwitter_clicked();
    void on_btnReddit_clicked();
    void on_btnTerms_clicked();
};

#endif // ABOUTVIEW_H
