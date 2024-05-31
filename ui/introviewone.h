#ifndef INTROVIEWONE_H
#define INTROVIEWONE_H

#include <QWidget>

namespace Ui {
class IntroViewOne;
}

class IntroViewOne : public QWidget
{
    Q_OBJECT

public:
    explicit IntroViewOne(QWidget *parent = nullptr);
    ~IntroViewOne();

signals:
    void openIntroPageTwo();

private slots:
    void on_btnNext_clicked();

    void on_btnChangeLogo_clicked();

private:
    Ui::IntroViewOne *ui;
    int logoState;
};

#endif // INTROVIEWONE_H
