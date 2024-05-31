#ifndef TREEDEVICEVIEW_H
#define TREEDEVICEVIEW_H

#include <QWidget>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

namespace Ui {
class TreeDeviceView;
}

class TreeDeviceView : public QWidget
{
    Q_OBJECT

public:
    explicit TreeDeviceView(QJsonArray mainArray, int index, QWidget *parent = nullptr);
    ~TreeDeviceView();

private:
    Ui::TreeDeviceView *ui;
    QJsonArray mainArray;
    int index;
};

#endif // TREEDEVICEVIEW_H
