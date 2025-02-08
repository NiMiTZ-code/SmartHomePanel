#include "newdevicewindow.h"
#include "ui_newdevicewindow.h"

newdevicewindow::newdevicewindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::newdevicewindow)
{
    ui->setupUi(this);
}

newdevicewindow::~newdevicewindow()
{
    delete ui;
}

QString newdevicewindow::getDeviceName(){
    return ui->deviceNameLnEdit->text();
}

QString newdevicewindow::getDeviceIP(){
    return ui->deviceIPLnEdit->text();
}
int newdevicewindow::getDeviceType(){
    return ui->deviceTypecBox->currentIndex();
}
