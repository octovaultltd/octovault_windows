#ifndef INTROVIEWTWO_H
#define INTROVIEWTWO_H

#include <QWidget>

namespace Ui {
class IntroViewTwo;
}

class IntroViewTwo : public QWidget
{
    Q_OBJECT

public:
    explicit IntroViewTwo(QWidget *parent = nullptr);
    ~IntroViewTwo();

signals:
    void openIntroPageOne();
    void openIntroPageThree();

private slots:
    void on_btnBack_clicked();

    void on_btnNext_clicked();

    void on_btnChangeLogo_clicked();

private:
    Ui::IntroViewTwo *ui;
    int logoState;
};

#endif // INTROVIEWTWO_H
