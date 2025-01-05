#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), networkManager(new QNetworkAccessManager(this)),
    lastIconCode(""), isRequestInProgress(false)  // Initialize flags
{
    ui->setupUi(this);

    // Timer to update the time every second
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::zegar);
    timer->start(1000);

    // Timer to update the weather every 60 seconds (1 minute)
    weatherTimer = new QTimer(this);
    connect(weatherTimer, &QTimer::timeout, this, &MainWindow::fetchWeatherData);
    weatherTimer->start(300000);  // Refresh weather every 5 minutes
    fetchWeatherData();  // Initial fetch of weather data

    // Connect the network manager to handle the weather data after it is fetched
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::fetchWeatherData);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::zegar()
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh:mm:ss");
    ui->timeLabel->setText(time_text);
}

void MainWindow::fetchWeatherData()
{
    // Prevent fetching weather if a request is in progress
    if (isRequestInProgress) {
        return;
    }

    isRequestInProgress = true;  // Mark that the request is in progress

    QString apiKey = "d1ae366f3a0eff9cf7500da05d365082"; // tu jest moj api key
    QString city = "Katowice";

    // Construct the API URL
    QString url = QString("http://api.openweathermap.org/data/2.5/weather?q=%1&appid=%2&units=metric")
                      .arg(city)
                      .arg(apiKey);

    qDebug() << "Constructed URL:" << url; // Debug output to verify the URL

    // Validate the URL
    QUrl apiUrl(url);
    if (!apiUrl.isValid()) {
        qDebug() << "Invalid URL:" << apiUrl.errorString();
        isRequestInProgress = false;  // Reset flag
        return;
    }

    // Send the GET request
    QNetworkRequest request(apiUrl);
    QNetworkReply *reply = networkManager->get(request);

    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            // Parse the JSON response
            QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
            QJsonObject jsonObj = jsonDoc.object();

            // Extract data
            double temperature = jsonObj["main"].toObject()["temp"].toDouble();
            double humidity = jsonObj["main"].toObject()["humidity"].toDouble();
            double pressure = jsonObj["main"].toObject()["pressure"].toDouble();
            QString weatherCondition = jsonObj["weather"].toArray().isEmpty() ? "" : jsonObj["weather"].toArray()[0].toObject()["description"].toString();

            // Safely access icon code
            QString iconCode = "";
            QJsonArray weatherArray = jsonObj["weather"].toArray();
            if (!weatherArray.isEmpty()) {
                QJsonObject weatherObj = weatherArray.at(0).toObject();
                iconCode = weatherObj["icon"].toString();
            }

            // Check if the icon code has changed before requesting the icon again
            if (iconCode != lastIconCode) {
                lastIconCode = iconCode;  // Update the last icon code
                fetchWeatherIcon(iconCode);  // Fetch the new icon

                // Update the labels with the weather data
                ui->temperatureLabel->setText(QString::number(temperature, 'f', 0) + "°C");
                ui->humidityLabel->setText(QString::number(humidity, 'f', 0) + "%");
                ui->pressureLabel->setText(QString::number(pressure, 'f', 0) + "hPa");
            }

        } else {
            qDebug() << "Error fetching weather data:" << reply->errorString();
        }

        // Clean up the weather reply object and reset flag
        isRequestInProgress = false;  // Reset flag
        reply->deleteLater();
    });
}

void MainWindow::fetchWeatherIcon(const QString &iconCode)
{
    // Construct the URL for the weather icon
    QString iconUrl = QString("https://openweathermap.org/img/wn/%1@2x.png").arg(iconCode);
    qDebug() << "Icon URL: " << iconUrl;  // Debug to ensure the URL is correct

    // Send the GET request to fetch the icon image
    QNetworkRequest iconRequest((QUrl(iconUrl)));
    QNetworkReply *iconReply = networkManager->get(iconRequest);

    connect(iconReply, &QNetworkReply::finished, [this, iconReply]() {
        if (iconReply->error() == QNetworkReply::NoError) {
            QByteArray iconData = iconReply->readAll();
            qDebug() << "Icon data size:" << iconData.size();  // Debug: check if data is received

            QImage iconImage;
            if (iconImage.loadFromData(iconData)) {
                qDebug() << "Icon image loaded successfully!";
                ui->weatherIconLabel->setPixmap(QPixmap::fromImage(iconImage));  // Set the icon image on the QLabel
            } else {
                qDebug() << "Failed to load icon image!";
            }
        } else {
            qDebug() << "Error fetching icon:" << iconReply->errorString();
        }

        // Clean up the icon reply
        iconReply->deleteLater();
    });
}
