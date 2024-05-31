#ifndef INTROVIEWTHREE_H
#define INTROVIEWTHREE_H

#include <QWidget>

namespace Ui {
class IntroViewThree;
}

class IntroViewThree : public QWidget
{
    Q_OBJECT

public:
    explicit IntroViewThree(QWidget *parent = nullptr);
    ~IntroViewThree();

signals:
    void openIntroPageTwo();
    void openIntroPageFour();

private slots:
    void on_btnNext_clicked();
    void on_btnBack_clicked();

    void on_btnChangeLogo_clicked();

private:
    Ui::IntroViewThree *ui;
    int logoState;
};

#endif // INTROVIEWTHREE_H
