#ifndef DATAGETTER_H
#define DATAGETTER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

#include <QMap>

#include <QFile>
#include <QDir>
#include <QCoreApplication>

#include <QString>
#include <QDebug>

class DataGetter : public QObject
{
    Q_OBJECT

private:

    QNetworkAccessManager* manager;
    QString currentLocation;

    bool validAPIAnswer();
    void readJson(QByteArray& array);
    void writeJson(QByteArray& array);
    void saveWeatherPicture(QByteArray& array);

    QMap<QString, QString> values;

    bool picRequested;

public:
    explicit DataGetter(QObject *parent = nullptr);

    void requestInfo(QString location);

    //getters
    QString getValue(QString key);

private slots:

    void handleReply(QNetworkReply* reply);
    void handlePicture(QNetworkReply* reply);

    void requestPicture(QString url_);

signals:

    void gotData(bool);
    void getPicture(QString);

};

#endif // DATAGETTER_H
