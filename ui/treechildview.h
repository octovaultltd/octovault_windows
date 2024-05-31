#ifndef TREECHILDVIEW_H
#define TREECHILDVIEW_H

#include <QWidget>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QMouseEvent>

namespace Ui {
class TreeChildView;
}

class TreeChildView : public QWidget
{
    Q_OBJECT

public:
    explicit TreeChildView(QJsonObject data, QWidget *parent = nullptr);
    ~TreeChildView();
    void toggleFavourite();
    void toggleSelected();

private:
    Ui::TreeChildView *ui;
    QJsonObject data;

public:
    bool eventFilter(QObject *watched, QEvent *event) override;
    QJsonObject getBundleData();

protected:
    void paintEvent(QPaintEvent *) override;
};

#endif // TREECHILDVIEW_H
