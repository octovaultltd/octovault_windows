#include "toolsview.h"
#include "ui_toolsview.h"

ToolsView::ToolsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolsView)
{
    ui->setupUi(this);
}

ToolsView::~ToolsView()
{
    delete ui;
}

void ToolsView::on_btnBack_clicked()
{
    emit openProfilePage();
}

