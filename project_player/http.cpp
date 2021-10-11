#include "http.h"

Http::Http(QObject *parent) : QObject(parent)
{

}

bool Http::post_sync(QString url, QMap<QString, QString> header, QByteArray requestData, QByteArray &replyData)
{
    QNetworkAccessManager manager;
    QNetworkRequest request;

    request.setUrl(QUrl(url));
    QMapIterator<QString,QString> it(header);
    while(it.hasNext())
    {
        it.next();
        request.setRawHeader(it.key().toLatin1(),it.value().toLatin1());
    }

    QNetworkReply *reply = manager.post(request,requestData);

    QEventLoop l;
    connect(reply,&QNetworkReply::finished,&l,&QEventLoop::quit);
    l.exec();

    if(reply!=nullptr && reply->error() == QNetworkReply::NoError)
    {
        replyData = reply->readAll();
        qDebug() << replyData;
        qDebug() << "121213125634361";
        return true;
    }else{
        qDebug() << "****************qdqad1";
        qDebug() <<  reply->error();
        qDebug() <<  reply->url().toString();
        return false;
    }

}
