#include "musiclist.h"

Musiclist::Musiclist(QObject *parent) : QObject(parent)
{
    isPlaying = false;
}


void Musiclist::Add2Music(Music &m)
{
    vr << m;

}

void Musiclist::Delete2Music(Music &m)
{
    for(auto it = vr.begin();it != vr.end(); it++)
    {
        if(m == *it)
        {
            vr.erase(it);
            return;
        }

    }
    return ;

}
Music * Musiclist::FindMusic(QString &name)
{
    for(QVector<Music>::iterator it = vr.begin();it != vr.end(); it++)
    {
        if(name == it->getName())
        {
            return it;
        }

    }
    return NULL;

}


void Musiclist::SetName(QString &name)
{
    this->name = name;
}
QString Musiclist::GetName()
{
    return name;
}

void Musiclist::SetPlayState(bool s)
{
    isPlaying = s;
}
bool Musiclist::GetPlayState()
{
    return isPlaying;
}
void Musiclist::ClearList()
{
    if(vr.isEmpty())
        return;
    QVector<Music>::iterator it = vr.begin();
    QVector<Music>::iterator it1 = vr.end();
    vr.erase(it,it1);


}

 qint16 Musiclist::size()
 {
     return vr.size();
 }

