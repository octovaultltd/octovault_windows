#include "serverview.h"
#include "ui_serverview.h"
#include "utils/localdb.h"
#include <QDebug>
#include <QMessageBox>

#define IDENTITY_ROLE Qt::UserRole + 1

ServerView::ServerView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerView)
{
    ui->setupUi(this);

    // Remove Default Frame On LineEdit Widget
    ui->editSearch->setAttribute(Qt::WA_MacShowFocusRect, 0);

    // Listener For Search Text Change
    connect(ui->editSearch, &QLineEdit::textChanged, this, &ServerView::searchQueryUpdated);
    // Listener For TreeWidget Click Event
    connect(ui->treeWidget, &QTreeWidget::clicked, this, &ServerView::onTreeWidgetClicked);

    insertTreeData();
}

ServerView::~ServerView()
{
    delete ui;
}

void ServerView::searchQueryUpdated(){
    insertTreeData();
}

void ServerView::insertTreeData(){
    ui->treeWidget->clear();
    QJsonArray mainArray = getParsedServers();

    if(LocalDB::getSelectedServerFilterTag() == "FAVORITES" || LocalDB::getSelectedServerFilterTag() == "LAST USED" || LocalDB::getSelectedServerFilterTag() == "HIGH SPEED" || LocalDB::getSelectedServerFilterTag() == "STREAMING" || LocalDB::getSelectedServerFilterTag() == "AD BLOCKER"){
        for(int i = 0; i <mainArray.size(); i ++){
            QJsonObject server = mainArray.at(i).toObject();
            QTreeWidgetItem* parent = nullptr;
            parent = new QTreeWidgetItem(ui->treeWidget);
            parent->setData(0, IDENTITY_ROLE, 1);
            auto parentWidget = new TreeChildView(server, ui->treeWidget);
            ui->treeWidget->setItemWidget(parent, 0, parentWidget);
        }
    }else{
        for(int i = 0; i <mainArray.size(); i ++){
            QJsonObject country = mainArray.at(i).toObject();
            QTreeWidgetItem* parent = nullptr;
            parent = new QTreeWidgetItem(ui->treeWidget);
            parent->setData(0, IDENTITY_ROLE, 0);
            parent->setExpanded(country.value("isExpanded").toBool());
            auto parentWidget = new TreeParentView(country, ui->treeWidget);
            ui->treeWidget->setItemWidget(parent, 0, parentWidget);
            QJsonArray servers = country.value("servers").toArray();
            for(int j = 0; j < servers.size(); j ++){
                QJsonObject server = servers.at(j).toObject();
                QTreeWidgetItem* child = nullptr;
                child = new QTreeWidgetItem(parent);
                child->setData(0, IDENTITY_ROLE, 1);
                auto childWidget = new TreeChildView(server, ui->treeWidget);
                ui->treeWidget->setItemWidget(child, 0, childWidget);
            }
        }
    }
}

QJsonArray ServerView::getParsedServers(){
    QString searchQuery = ui->editSearch->text().toLower();
    QString bundles = LocalDB().getIPBundle();
    QJsonDocument doc = QJsonDocument::fromJson(bundles.toUtf8());
    QJsonArray serverArray = doc.array();
    QJsonArray mainArray;
    QJsonArray highSpeedArray;
    QJsonArray adBlockArray;
    QJsonArray favouriteArray;
    QJsonArray streamingArray;
    QJsonArray countryArray;
    QJsonArray lastUsedArray;
    for(int i = 0; i <serverArray.size(); i ++){
        QJsonObject server = serverArray.at(i).toObject();
        if(server.value("platform").toString() == "all" || server.value("platform").toString() == "ios"){
            if(searchQuery.isEmpty()){
                if(server.value("is_fast_server").toInt() == 1){
                    highSpeedArray.append(server);
                }
                if(server.value("is_adblocker").toInt() == 1){
                    adBlockArray.append(server);
                }
                if(LocalDB().isFavServer(server.value("ip_id").toInt())){
                    favouriteArray.append(server);
                }
                if(server.value("is_online_stream").toInt() == 1){
                    streamingArray.append(server);
                }
                if(server.value("ip_id").toInt() == LocalDB::getRecentServerID()){
                    lastUsedArray.append(server);
                }
                if(!countryArray.contains(server.value("countryCode").toString())){
                    countryArray.append(server.value("countryCode").toString());
                }
            }else{
                QString countryName = server.value("countryName").toString().toLower();
                QString ipName = server.value("ipName").toString().toLower();
                if(countryName.contains(searchQuery) || ipName.contains(searchQuery)){
                    if(server.value("is_fast_server").toInt() == 1){
                        highSpeedArray.append(server);
                    }
                    if(server.value("is_adblocker").toInt() == 1){
                        adBlockArray.append(server);
                    }
                    if(LocalDB().isFavServer(server.value("ip_id").toInt())){
                        favouriteArray.append(server);
                    }
                    if(server.value("is_online_stream").toInt() == 1){
                        streamingArray.append(server);
                    }
                    if(server.value("ip_id").toInt() == LocalDB::getRecentServerID()){
                        lastUsedArray.append(server);
                    }
                    if(!countryArray.contains(server.value("countryCode").toString())){
                        countryArray.append(server.value("countryCode").toString());
                    }
                }
            }
        }
    }
    if(highSpeedArray.size() > 0){
        QJsonObject object;
        object.insert("countryName", "High Speed Server");
        object.insert("countryImage", ":/img/images/icon_high_speed_server.png");
        object.insert("servers", highSpeedArray);
        object.insert("isExpanded", checkExpended(highSpeedArray));
        mainArray.append(object);
    }
    if(adBlockArray.size() > 0){
        QJsonObject object;
        object.insert("countryName", "Ad Blocker Server");
        object.insert("countryImage", ":/img/images/icon_ad_block_server.png");
        object.insert("servers", adBlockArray);
        object.insert("isExpanded", checkExpended(adBlockArray));
        mainArray.append(object);
    }
    if(streamingArray.size() > 0){
        QJsonObject object;
        object.insert("countryName", "Streaming Server");
        object.insert("countryImage", ":/img/images/icon_streaming_server.png");
        object.insert("servers", streamingArray);
        object.insert("isExpanded", checkExpended(streamingArray));
        mainArray.append(object);
    }
    for(int i = 0; i < countryArray.size(); i ++){
        QString code = countryArray.at(i).toString();
        QJsonArray cityArray;
        for(int j = 0; j < serverArray.size(); j ++){
            QJsonObject server = serverArray.at(j).toObject();
            if((server.value("platform").toString() == "all" || server.value("platform").toString() == "ios") && server.value("countryCode").toString() == code){
                if(searchQuery.isEmpty()){
                    cityArray.append(server);
                }else{
                    QString countryName = server.value("countryName").toString().toLower();
                    QString ipName = server.value("ipName").toString().toLower();
                    if(countryName.contains(searchQuery) || ipName.contains(searchQuery)){
                        cityArray.append(server);
                    }
                }
            }
        }
        if(cityArray.size() > 0){
            QJsonObject object;
            QJsonObject server = cityArray.at(0).toObject();
            object.insert("countryName", server.value("countryName").toString());
            object.insert("countryImage", CommonData().getFlagImage(server.value("countryCode").toString().toInt()));
            object.insert("servers", cityArray);
            object.insert("isExpanded", checkExpended(cityArray));
            mainArray.append(object);
        }
    }
    if(LocalDB::getSelectedServerFilterTag() == "FAVORITES"){
        return favouriteArray;
    }else if(LocalDB::getSelectedServerFilterTag() == "LAST USED"){
        return lastUsedArray;
    }else if(LocalDB::getSelectedServerFilterTag() == "HIGH SPEED"){
        return highSpeedArray;
    }else if(LocalDB::getSelectedServerFilterTag() == "STREAMING"){
        return streamingArray;
    }else if(LocalDB::getSelectedServerFilterTag() == "AD BLOCKER"){
        return adBlockArray;
    }else{
        return mainArray;
    }
}

bool ServerView::checkExpended(QJsonArray list){
    int ipID = LocalDB().getActiveServerID();
    for(int i = 0; i < list.size(); i ++){
        QJsonObject server = list.at(i).toObject();
        int tempIpID = server.value("ip_id").toInt();
        if(ipID == tempIpID){
            return true;
        }
    }
    return false;
}

void ServerView::onTreeWidgetClicked(const QModelIndex &index){
    if(index.data(IDENTITY_ROLE).toInt() == 1){
        qDebug() << "Row Clicked";
        auto item = ui->treeWidget->currentItem();
        auto itemWidget = dynamic_cast<TreeChildView*>(ui->treeWidget->itemWidget(item, 0));
        QJsonObject data = itemWidget->getBundleData();
        int ipID = data.value("ip_id").toInt();
        LocalDB().setActiveServerID(ipID);
        emit connectVPNFromServerPage();
        insertTreeData();
    }else{
        qDebug() << "Section Clicked";
        auto item = ui->treeWidget->currentItem();
        auto itemWidget = dynamic_cast<TreeParentView*>(ui->treeWidget->itemWidget(item, 0));
        if(ui->treeWidget->isExpanded(index)){
            itemWidget->setExpanded(false);
            ui->treeWidget->collapse(index);
        }else{
            ui->treeWidget->expand(index);
            itemWidget->setExpanded(true);
        }
    }
}

void ServerView::on_btnAll_clicked()
{
    LocalDB::setSelectedServerFiltertag("ALL");
    updateServerFilterTags();
}

void ServerView::on_btnFav_clicked()
{
    LocalDB::setSelectedServerFiltertag("FAVORITES");
    updateServerFilterTags();
}

void ServerView::on_btnLastUsed_clicked()
{
    LocalDB::setSelectedServerFiltertag("LAST USED");
    updateServerFilterTags();
}

void ServerView::on_btnHighSpeed_clicked()
{
    LocalDB::setSelectedServerFiltertag("HIGH SPEED");
    updateServerFilterTags();
}

void ServerView::on_btnStreaming_clicked()
{
    LocalDB::setSelectedServerFiltertag("STREAMING");
    updateServerFilterTags();
}

void ServerView::on_btnAdBlocker_clicked()
{
    LocalDB::setSelectedServerFiltertag("AD BLOCKER");
    updateServerFilterTags();
}

void ServerView::updateServerFilterTags()
{
    QString filtertag = LocalDB::getSelectedServerFilterTag();
    if(filtertag == "FAVORITES"){
        ui->btnAll->setStyleSheet("QPushButton{border: 1px solid #36353a;border-radius: 10px;color:#818083;}");
        ui->btnFav->setStyleSheet("QPushButton{background:#FACA7F;border-radius: 10px;color:#000000;}");
        ui->btnLastUsed->setStyleSheet("QPushButton{border: 1px solid #36353a;border-radius: 10px;color:#818083;}");
        ui->btnHighSpeed->setStyleSheet("QPushButton{border: 1px solid #36353a;border-radius: 10px;color:#818083;}");
        ui->btnStreaming->setStyleSheet("QPushButton{border: 1px solid #36353a;border-radius: 10px;color:#818083;}");
        ui->btnAdBlocker->setStyleSheet("QPushButton{border: 1px solid #36353a;border-radius: 10px;color:#818083;}");
    }else if(filtertag == "LAST USED"){
        ui->btnAll->setStyleSheet("QPushButton{border: 1px solid #36353a;border-radius: 10px;color:#818083;}");
        ui->btnFav->setStyleSheet("QPushButton{border: 1px solid #36353a;border-radius: 10px;color:#818083;}");
        ui->btnLastUsed->setStyleSheet("QPushButton{background:#FACA7F;border-radius: 10px;color:#000000;}");
        ui->btnHighSpeed->setStyleSheet("QPushButton{border: 1px solid #36353a;border-radius: 10px;color:#818083;}");
        ui->btnStreaming->setStyleSheet("QPushButton{border: 1px solid #36353a;border-radius: 10px;color:#818083;}");
        ui->btnAdBlocker->setStyleSheet("QPushButton{border: 1px solid #36353a;border-radius: 10px;color:#818083;}");
    }else if(filtertag == "HIGH SPEED"){
        ui->btnAll->setStyleSheet("QPushButton{border: 1px solid #36353a;border-radius: 10px;color:#818083;}");
        ui->btnFav->setStyleSheet("QPushButton{border: 1px solid #36353a;border-radius: 10px;color:#818083;}");
        ui->btnLastUsed->setStyleSheet("QPushButton{border: 1px solid #36353a;border-radius: 10px;color:#818083;}");
        ui->btnHighSpeed->setStyleSheet("QPushButton{background:#FACA7F;border-radius: 10px;color:#000000;}");
        ui->btnStreaming->setStyleSheet("QPushButton{border: 1px solid #36353a;border-radius: 10px;color:#818083;}");
        ui->btnAdBlocker->setStyleSheet("QPushButton{border: 1px solid #36353a;border-radius: 10px;color:#818083;}");
    }else if(filtertag == "STREAMING"){
        ui->btnAll->setStyleSheet("QPushButton{border: 1px solid #36353a;border-radius: 10px;color:#818083;}");
        ui->btnFav->setStyleSheet("QPushButton{border: 1px solid #36353a;border-radius: 10px;color:#818083;}");
        ui->btnLastUsed->setStyleSheet("QPushButton{border: 1px solid #36353a;border-radius: 10px;color:#818083;}");
        ui->btnHighSpeed->setStyleSheet("QPushButton{border: 1px solid #36353a;border-radius: 10px;color:#818083;}");
        ui->btnStreaming->setStyleSheet("QPushButton{background:#FACA7F;border-radius: 10px;color:#000000;}");
        ui->btnAdBlocker->setStyleSheet("QPushButton{border: 1px solid #36353a;border-radius: 10px;color:#818083;}");
    }else if(filtertag == "AD BLOCKER"){
        ui->btnAll->setStyleSheet("QPushButton{border: 1px solid #36353a;border-radius: 10px;color:#818083;}");
        ui->btnFav->setStyleSheet("QPushButton{border: 1px solid #36353a;border-radius: 10px;color:#818083;}");
        ui->btnLastUsed->setStyleSheet("QPushButton{border: 1px solid #36353a;border-radius: 10px;color:#818083;}");
        ui->btnHighSpeed->setStyleSheet("QPushButton{border: 1px solid #36353a;border-radius: 10px;color:#818083;}");
        ui->btnStreaming->setStyleSheet("QPushButton{border: 1px solid #36353a;border-radius: 10px;color:#818083;}");
        ui->btnAdBlocker->setStyleSheet("QPushButton{background:#FACA7F;border-radius: 10px;color:#000000;}");
    }else{
        ui->btnAll->setStyleSheet("QPushButton{background:#FACA7F;border-radius: 10px;color:#000000;}");
        ui->btnFav->setStyleSheet("QPushButton{border: 1px solid #36353a;border-radius: 10px;color:#818083;}");
        ui->btnLastUsed->setStyleSheet("QPushButton{border: 1px solid #36353a;border-radius: 10px;color:#818083;}");
        ui->btnHighSpeed->setStyleSheet("QPushButton{border: 1px solid #36353a;border-radius: 10px;color:#818083;}");
        ui->btnStreaming->setStyleSheet("QPushButton{border: 1px solid #36353a;border-radius: 10px;color:#818083;}");
        ui->btnAdBlocker->setStyleSheet("QPushButton{border: 1px solid #36353a;border-radius: 10px;color:#818083;}");
    }

    insertTreeData();
}

