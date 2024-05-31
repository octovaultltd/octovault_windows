#ifndef DEVICEVIEW_H
#define DEVICEVIEW_H

#include <QWidget>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <ui/treedeviceview.h>
#include <QMovie>
#include <QMessageBox>

namespace Ui {
class DeviceView;
}

class DeviceView : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceView(QWidget *parent = nullptr);
    ~DeviceView();

signals:
    void openProfilePage();

private slots:
    void on_btnBack_clicked();

private:
    Ui::DeviceView *ui;
    void insertTreeData();
    void getDeviceData();
    QJsonArray getDeviceArray();
    QMovie *movie;

protected:
    void showEvent(QShowEvent *) override;
};

#endif // DEVICEVIEW_H
