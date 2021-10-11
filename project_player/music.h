#ifndef MUSIC_H
#define MUSIC_H
#include <QString>
#include <QListWidget>
class Music
{

public:
    Music();
    ~Music();

    void setName(QString name);
    QString& getName();

    void setUrl(QString url);
    QString& getUrl();

    void setDuration(qint64 duration);
    qint64 getDuration();

    bool operator==(Music &a)
    {
        if(a.name == this->name)
            return true;
        return false;
    }


    //歌曲名称
    QString name;
    //歌曲所在目录的Url
    QString Url;
    //时长
    qint64 duration;



};

#endif // MUSIC_H
