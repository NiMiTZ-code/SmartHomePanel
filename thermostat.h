#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include "sensor.h"
class Thermostat : public Sensor
{
    Q_OBJECT
private:
    float temperatureSetting;
    float temperatureReading;

    void performAction();
public:
    explicit Thermostat(QObject *parent = nullptr);

    void readValue() override; //to fire network command of temperature retrieval
    void setTemperatureSetting(float temp);
    void setTemperatureReading(float temp);

    float getTemperatureReading(){
        return temperatureReading;
    }
    float getTemperatureSetting(){
        return temperatureSetting;
    }
    void chngTempSetting();

    void sendCommand() override;
public slots:
    void handleResponse(const QByteArray& response) override;
signals:
    void temperatureChanged(float newTemperature);
    void temperatureSettingChanged(float newTemperatureSetting); //send to actuator like heater or AC
    void temperatureReadingChanged(float newTemperatureReading);
    void temperatureError(const QString& errorMessage);

};

#endif // THERMOSTAT_H
