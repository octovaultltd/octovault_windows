#ifndef TOOLSVIEW_H
#define TOOLSVIEW_H

#include <QWidget>

namespace Ui {
class ToolsView;
}

class ToolsView : public QWidget
{
    Q_OBJECT

public:
    explicit ToolsView(QWidget *parent = nullptr);
    ~ToolsView();

signals:
    void openProfilePage();

private:
    Ui::ToolsView *ui;

private slots:
    void on_btnBack_clicked();
};

#endif // TOOLSVIEW_H
