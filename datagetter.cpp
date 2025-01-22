#include "datagetter.h"

//private functions
bool DataGetter::validAPIAnswer()
{
    return false;
}

void DataGetter::readJson(QByteArray& array)
{
    QJsonDocument jDoc = QJsonDocument::fromJson(array);
    QJsonObject jMainObject = jDoc.object();

    QJsonObject location = jMainObject["location"].toObject();

    values["name"] = location["name"].toString();
    values["time"] = location["localtime"].toString();

    QJsonObject current = jMainObject["current"].toObject();
    values["temperature"] = QString::number(current["temperature"].toInt());
    values["weathericons"] = current["weather_icons"].toArray().first().toString();
    values["weatherdescription"] = current["weather_descriptions"].toArray().first().toString();
    values["windspeed"] = QString::number(current["wind_speed"].toInt());
    values["winddir"] = current["wind_dir"].toString();
    values["feelslike"] = QString::number(current["feelslike"].toInt());

}

void DataGetter::writeJson(QByteArray &array)
{
    //save all data to .json file
    QString appDir = QCoreApplication::applicationDirPath();
    QString filePath = QDir(appDir).filePath("data.json");

    QFile writeFile(filePath);
    if(!writeFile.open(QIODevice::WriteOnly))
    {
        qDebug() << "Error::cant open file for writing";
    }
    writeFile.write(array);

    writeFile.close();

}

void DataGetter::saveWeatherPicture(QByteArray& array)
{

    QString appDir = QCoreApplication::applicationDirPath();
    // get name of file from url
    QString fileName = values["weathericons"].split("/").last();

    QString filePath = QDir(appDir).filePath(fileName);

    QFile imageFile(filePath);
    values["weathericon"] = filePath;

    if(!imageFile.open(QIODevice::WriteOnly))
    {
        qDebug() << "Error saving image file\n";
    }
    imageFile.write(array);
    imageFile.close();

    emit gotData(true);
}

// pricate slots
void DataGetter::handleReply(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray array = reply->readAll();
        writeJson(array);
        // read data from API Json file
        readJson(array);
    }
    else{
        qDebug() << "Error while loading data";
    }
    reply->deleteLater();
    disconnect(manager, &QNetworkAccessManager::finished, this, &DataGetter::handleReply);
    connect(manager, &QNetworkAccessManager::finished, this, &DataGetter::handlePicture);
    emit getPicture(values["weathericons"]);

}

//saves picture from API to exe dir
void DataGetter::handlePicture(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray array = reply->readAll();
        saveWeatherPicture(array);
    }
    else{
        qDebug() << "Error while loading pic";
    }
    reply->deleteLater();
    disconnect(manager, &QNetworkAccessManager::finished, this, &DataGetter::handlePicture);
    connect(manager, &QNetworkAccessManager::finished, this, &DataGetter::handleReply);
}

void DataGetter::requestPicture(QString url_)
{
    QUrl url(url_);
    QNetworkRequest request(url);

    QNetworkReply* reply = manager->get(request);

}

//public functions
DataGetter::DataGetter(QObject *parent)
    : QObject{parent}
{
    picRequested = false;

    manager = new QNetworkAccessManager(this);

    connect(this, &DataGetter::getPicture, this, &DataGetter::requestPicture);

    connect(manager, &QNetworkAccessManager::finished, this, &DataGetter::handleReply);

}

void DataGetter::requestInfo(QString location)
{

    values.clear();
    // clear all saved values before next request
    if(location.isEmpty())
    {
        emit gotData(true);
        return;
    }

    currentLocation = location;
    QString sUrl = "INPUTYOURAPIKEYHERE&query=" + location;
    QUrl url(sUrl);

    QNetworkRequest request(url);

    QNetworkReply* reply = manager->get(request);

}

QString DataGetter::getValue(QString key)
{
    if(values.contains(key))
    {
        return values.value(key);
    }
    return "None";
}
