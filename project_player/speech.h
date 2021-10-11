#ifndef SPEECH_H
#define SPEECH_H

#include <QObject>
#include "http.h"
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonArray>
#include <QHostInfo>
#include <QFile>
/*获取相关*/
const QString token_url = "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=%1&client_secret=%2";
const QString client_id ="cR1WfnVzVPyc4oqbmlbBsSR8" ;
const QString client_secret = "kKZ1il1QSyTZdnNGYmMx763y5HHpEQhW";
const QString baidu_sp_identify_url = "http://vop.baidu.com/server_api?dev_pid=1537&cuid=%1&token=%2";

/*语音识别相关*/
class Speech : public QObject
{
    Q_OBJECT
public:
    explicit Speech(QObject *parent = 0);
    QString SpeechIdentify(QString filename);
    /*通过key 获取value*/
    QString getJsonValue(QByteArray , QString key);
signals:

public slots:

private:
        Http m_http;
};

#endif // SPEECH_H
