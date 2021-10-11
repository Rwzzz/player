#include "speech.h"

Speech::Speech(QObject *parent) : QObject(parent)
{

}


QString Speech::SpeechIdentify(QString filename)
{
    QString tokenUrl = QString(token_url).arg(client_id).arg(client_secret);
    QMap<QString,QString> header;
    QString access_token;
    header.insert(QString("Content-Type"),QString("audio/pcm;rate=16000"));
    QByteArray request;
    QByteArray reply;
    /*获取token*/
    bool isOk = m_http.post_sync(tokenUrl,header,request,reply);
    if(isOk)
    {
        QString key = "access_token";
        access_token = getJsonValue(reply,key);
        qDebug() << access_token;
    }else{
        return "";

    }
    reply.clear();
    QString identifyUrl = QString(baidu_sp_identify_url).arg(QHostInfo::localHostName()).arg(access_token);
    QFile file;
    file.setFileName(filename);
    isOk = file.open(QIODevice::ReadOnly);
    if(isOk)
    {
        request = file.readAll();
        file.close();
    }else{

        file.close();
        return "";
    }
    /*语音识别*/
    isOk = m_http.post_sync(identifyUrl,header,request,reply);
    if(isOk)
    {
        QString err = "err_msg";
        QString err_msg = getJsonValue(reply,err);
        qDebug() << err_msg;
        if(err_msg != "success.")
        {
            qDebug() << "识别失败";
        }else{
            QString key = "result";
            QString result = getJsonValue(reply,key);
            qDebug() << result;
            return result;
        }


    }else{


    }
    return "";
}

QString Speech::getJsonValue(QByteArray arr, QString key)
{
    QJsonParseError parseRrror;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(arr,&parseRrror);
    if(parseRrror.error == QJsonParseError::NoError)
    {
        if(jsonDoc.isObject())
        {
            QJsonObject jsonobject = jsonDoc.object();
            if(jsonobject.contains(key))
            {
                QJsonValue jsonVal = jsonobject.value(key);
                if(jsonVal.isString())
                {
                    return jsonVal.toString();
                }else if(jsonVal.isArray())
                {

                    return jsonVal.toArray().at(0).toString();
                }
            }
        }

    }
}
