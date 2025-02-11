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

void newdevicewindow::on_deviceTypecBox_activated(int index)
{
    if(index == 0){
        ui->thermostatIpLabel->show();
        ui->thermostatNameLabel->show();
        ui->thermostatNameliEd->show();
        ui->thermostatIpLiEd->show();
    } else {
        ui->thermostatNameLabel->hide();
        ui->thermostatIpLabel->hide();
        ui->thermostatNameliEd->hide();
        ui->thermostatIpLiEd->hide();
    }
}

QString newdevicewindow::getThermostatName(){
    return ui->thermostatNameliEd->text();
}

QString newdevicewindow::getThermostatIP(){
    return ui->thermostatIpLiEd->text();
}
