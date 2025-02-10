#ifndef NEWDEVICEWINDOW_H
#define NEWDEVICEWINDOW_H

#include <QDialog>

namespace Ui {
class newdevicewindow;
}

class newdevicewindow : public QDialog
{
    Q_OBJECT

public:
    explicit newdevicewindow(QWidget *parent = nullptr);
    ~newdevicewindow();
    QString getDeviceName();
    QString getDeviceIP();
    int getDeviceType();

private:
    Ui::newdevicewindow *ui;

};

#endif // NEWDEVICEWINDOW_H
