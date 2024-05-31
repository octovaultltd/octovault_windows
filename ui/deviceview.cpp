#include "deviceview.h"
#include "ui_deviceview.h"
#include "utils/networkmanager.h"
#include <QTimer>

#define IDENTITY_ROLE Qt::UserRole + 1

DeviceView::DeviceView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceView)
{
    ui->setupUi(this);

    // Initialize Spinner
    movie = new QMovie(":/img/images/spinner.gif");
    ui->lblSpinner->setMovie(movie);
}

DeviceView::~DeviceView()
{
    delete ui;
}

void DeviceView::on_btnBack_clicked()
{
    emit openProfilePage();
}

void DeviceView::getDeviceData()
{
    // Show Spinner
    ui->lblSpinner->show();
    movie->start();

    // Make API Call
    auto response = NetworkManager().callDeviceInfoAPI();
    qDebug() << response;

    // Hide Spinner
    movie->stop();
    ui->lblSpinner->hide();

    // Parse Response
    if(response[0] == "1"){
        insertTreeData();
    }else{
        QMessageBox alert;
        alert.setText(response[1]);
        alert.setStandardButtons(QMessageBox::Ok);
        alert.exec();
    }
}

void DeviceView::insertTreeData()
{
    ui->treeWidget->clear();
    QString deviceText = LocalDB().getDeviceInfo();
    QJsonDocument doc = QJsonDocument::fromJson(deviceText.toUtf8());
    QJsonArray mainArray = doc.array();
    for(int i = 0; i <mainArray.size(); i ++){
        QTreeWidgetItem* parent = nullptr;
        parent = new QTreeWidgetItem(ui->treeWidget);
        parent->setData(0, IDENTITY_ROLE, 0);
        auto parentWidget = new TreeDeviceView(mainArray, i, ui->treeWidget);
        ui->treeWidget->setItemWidget(parent, 0, parentWidget);
    }
}

void DeviceView::showEvent(QShowEvent *)
{
    QTimer::singleShot(0, this, &DeviceView::getDeviceData);
}

