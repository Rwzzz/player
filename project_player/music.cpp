#include "music.h"
#include <QString>
#include <QDebug>
Music::Music()
{

}
Music::~Music()
{

}
QString& Music::getName()
{

    return name;

}


void Music::setName(QString name)
{

    this->name = name;
}

void Music::setDuration(qint64 duration)
{
    this->duration = duration;

}

void Music::setUrl(QString url)
{
    this->Url = url;
}

QString& Music::getUrl()
{

    return Url;
}

qint64 Music::getDuration()
{

    return duration;

}
