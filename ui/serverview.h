#ifndef SERVERVIEW_H
#define SERVERVIEW_H

#include <QWidget>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QHBoxLayout>
#include <QPushButton>
#include <QJsonDocument>
#include <ui/treeparentview.h>
#include <ui/treechildview.h>

namespace Ui {
class ServerView;
}

class ServerView : public QWidget
{
    Q_OBJECT

public:
    explicit ServerView(QWidget *parent = nullptr);
    ~ServerView();

signals:
    void openPremiumPage();
    void connectVPNFromServerPage();

public  slots:
    void searchQueryUpdated();

private:
    Ui::ServerView *ui;
    QJsonArray getParsedServers();
    void insertTreeData();
    void updateServerFilterTags();
    bool checkExpended(QJsonArray list);

private slots:
    void onTreeWidgetClicked(const QModelIndex &index);
    void on_btnAll_clicked();
    void on_btnFav_clicked();
    void on_btnLastUsed_clicked();
    void on_btnHighSpeed_clicked();
    void on_btnStreaming_clicked();
    void on_btnAdBlocker_clicked();
};

#endif // SERVERVIEW_H
