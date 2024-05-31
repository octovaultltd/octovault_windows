#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include <QWidget>
#include <QMovie>
#include <QMessageBox>

namespace Ui {
class SettingsView;
}

class SettingsView : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsView(QWidget *parent = nullptr);
    ~SettingsView();

signals:
    void openProfilePage();
    void openLoginPage();

private slots:
    void on_btnBack_clicked();
    void on_btnDelete_clicked();

private:
    Ui::SettingsView *ui;
    QMovie *movie;
};

#endif // SETTINGSVIEW_H
