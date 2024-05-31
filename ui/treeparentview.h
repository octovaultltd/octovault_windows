#ifndef TREEPARENTVIEW_H
#define TREEPARENTVIEW_H

#include <QWidget>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

namespace Ui {
class TreeParentView;
}

class TreeParentView : public QWidget
{
    Q_OBJECT

public:
    explicit TreeParentView(QJsonObject data, QWidget *parent = nullptr);
    ~TreeParentView();

public:
    void setExpanded(bool expanded);

private:
    Ui::TreeParentView *ui;
    QJsonObject data;
};

#endif // TREEPARENTVIEW_H
