#include "rgblampwidget.h"
#include "ui_RGBLampWidget.h"
#include <QColorDialog>

RGBLampWidget::RGBLampWidget(RGBLamp* lamp, QWidget* parent)
    : DeviceWidget(lamp, parent), ui(new Ui::RGBLampWidget)
{
    ui->setupUi(this);
    connect(ui->colorPickerButton, &QPushButton::clicked,
            this, &RGBLampWidget::on_colorPickerButton_clicked);
    connect(ui->brightnessSlider, &QSlider::valueChanged,
            this, &RGBLampWidget::on_brightnessSlider_valueChanged);
    connect(ui->toggleButton, &QPushButton::clicked,
            this, &RGBLampWidget::on_toggleButton_clicked);

    ui->brightnessSlider->setRange(0, 255);

    updateUI();
}

RGBLampWidget::~RGBLampWidget()
{
    delete ui;
}

void RGBLampWidget::updateUI()
{
    ui->statusLabel->setText(QString("Status: %1")
                             .arg(m_lamp()->getStatus() == DeviceStatus::ON ? "ON" : "OFF"));
}

void RGBLampWidget::on_colorPickerButton_clicked()
{
    QColor color = QColorDialog::getColor(m_lamp()->getColor(), this);
    if (color.isValid()) {
        m_lamp()->mixColors(color.red(), color.green(), color.blue());
        m_lamp()->chngColor();
        m_lamp()->sendCommand();
        updateUI();
    }

}


void RGBLampWidget::on_brightnessSlider_valueChanged(int value)
{
    m_lamp()->setBrightness(value);
    m_lamp()->chngBrightness();
    m_lamp()->sendCommand();
    updateUI();
}


void RGBLampWidget::on_toggleButton_clicked()
{
    m_lamp()->toggle();
    updateUI();
}

