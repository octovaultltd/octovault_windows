#include "referbalanceview.h"
#include "ui_referbalanceview.h"
#include <QTimer>
#include <QClipboard>

ReferBalanceView::ReferBalanceView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReferBalanceView)
{
    ui->setupUi(this);

    // Initialize Spinner
    movie = new QMovie(":/img/images/spinner.gif");
    ui->lblSpinner->setMovie(movie);

    // Remove Default Frame
    ui->editRedeem->setAttribute(Qt::WA_MacShowFocusRect, 0);
}

void ReferBalanceView::getReferData()
{
    ui->lblSpinner->show();
    movie->start();

    // Make API Call
    auto response = NetworkManager().getReferInfo();
    qDebug() << response;

    // Hide Spinner
    movie->stop();
    ui->lblSpinner->hide();

    // Parse Response
    if(response[0] == "1"){
        ui->lblRefer->setText(response[1]);
        ui->lblBalance->setText("$"+response[3]);
        int balance = response[3].toInt();
        int matureBalance = response[4].toInt();
        int minWithdrawAmount = response[5].toInt();
        if(balance > 0){
            ui->balanceHolder->setStyleSheet("QWidget{background:#FACA7F;border-radius: 10px;}");
            ui->lblBalance->setStyleSheet("QLabel{color:#000000;border-color:transparent;}");
        }else{
            ui->balanceHolder->setStyleSheet("QWidget{background:transparent;border: 1px solid #36353a;border-radius: 10px;}");
            ui->lblBalance->setStyleSheet("QLabel{color:#818083;border-color:transparent;}");
        }
        if(matureBalance >= minWithdrawAmount){
            withdrawEnabled = true;
            ui->btnWithdraw->setStyleSheet("QPushButton{background:transparent;border: 1px solid #FACA7F;border-radius: 10px;color:#FACA7F;}");
        }else{
            withdrawEnabled = false;
            ui->btnWithdraw->setStyleSheet("QPushButton{background:transparent;border: 1px solid #36353a;border-radius: 10px;color:#818083;}");
        }

        if(response[7] == "1"){
            ui->lblRedeemHeader->setHidden(false);
            ui->redeemHolder->setHidden(false);
            ui->btnApply->setHidden(false);
        }else{
            ui->lblRedeemHeader->setHidden(true);
            ui->redeemHolder->setHidden(true);
            ui->btnApply->setHidden(true);
        }
    }else{
        QMessageBox alert;
        alert.setText(response[1]);
        alert.setStandardButtons(QMessageBox::Ok);
        alert.exec();
    }
}

ReferBalanceView::~ReferBalanceView()
{
    delete ui;
}

void ReferBalanceView::on_btnBack_clicked()
{
    emit openReferPage();
}

void ReferBalanceView::on_btnWithdraw_clicked()
{
    if(withdrawEnabled){
        emit openReferWithdrawPage();
    }
}

void ReferBalanceView::on_btnCopy_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(ui->lblRefer->text());
}

void ReferBalanceView::on_btnShare_clicked()
{

}

void ReferBalanceView::on_btnApply_clicked()
{
    QString redeemCode = ui->editRedeem->text().trimmed();
    ui->lblSpinner->show();
    movie->start();

    // Make API Call
    auto response = NetworkManager().callReferRedeemAPI(redeemCode);
    qDebug() << response;

    // Hide Spinner
    movie->stop();
    ui->lblSpinner->hide();

    // Parse Response
    QMessageBox alert;
    alert.setText(response[1]);
    alert.setStandardButtons(QMessageBox::Ok);
    alert.exec();
}

void ReferBalanceView::showEvent(QShowEvent *)
{
    QTimer::singleShot(0, this, &ReferBalanceView::getReferData);
}

