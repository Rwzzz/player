#ifndef HTTP_H
#define HTTP_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMap>
#include <QDebug>
#include <QEventLoop>

/*speech语音识别过程中进行HTTP操作*/
class Http : public QObject
{
    Q_OBJECT
public:
    explicit Http(QObject *parent = 0);
    bool post_sync(QString url,QMap<QString,QString> header,QByteArray request,QByteArray &reply);
signals:

public slots:
};

#endif // HTTP_H
