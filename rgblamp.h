#ifndef RGBLAMP_H
#define RGBLAMP_H

#include "lamp.h"
#include <QColor>

class RGBLamp : public Lamp
{
private:
    uint8_t m_brightness;
    uint8_t m_color_R;
    uint8_t m_color_G;
    uint8_t m_color_B;
    QColor m_mixedColor;

public:
    explicit RGBLamp(QObject *parent = nullptr);
    void setBrightness();
    void setColorR(uint8_t val);
    void setColorG(uint8_t val);
    void setColorB(uint8_t val);
    void mixColors(uint8_t R, uint8_t G, uint8_t B);

};

#endif // RGBLAMP_H
