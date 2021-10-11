#ifndef MUSICLIST_H
#define MUSICLIST_H

#include <QObject>
#include <QMediaPlaylist>

#include "music.h"
class Musiclist : public QObject
{
    Q_OBJECT
public:
    explicit Musiclist(QObject *parent = 0);

    void Add2Music(Music &);
    Music* FindMusic(QString &name);
    void Delete2Music(Music &);
    void ClearList();

    void SetName(QString &);
    QString GetName();

    void SetPlayState(bool );
    bool GetPlayState();

    qint16 size(); /*获取音乐的数量*/
    QVector <Music> vr; /*存放音乐*/
private:
    QString name;
    bool isPlaying;


public slots:
};

#endif // MUSICLIST_H
