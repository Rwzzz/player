#include "audio.h"
#include <QDebug>
Audio::Audio(QObject *parent) : QObject(parent)
{

    m_file = NULL;
    QAudioDeviceInfo device = QAudioDeviceInfo::defaultInputDevice();
    QAudioFormat m_format;
    m_format.setSampleRate(16000);
    m_format.setChannelCount(1);
    m_format.setSampleSize(16);
    m_format.setCodec("audio/pcm");
    if(!device.isFormatSupported(m_format))
    {
        m_format = device.nearestFormat(m_format);

    }
    m_audio = new QAudioInput(device,m_format,this);
    m_file = new QFile;
    connect(m_audio,SIGNAL(stateChanged(QAudio::State)),this,SLOT(slot_changeState(QAudio::State)));

}

void Audio::slot_changeState(QAudio::State sta)
{
    if(sta == QAudio::StoppedState)
         m_file->close();
    qDebug() << "void Audio::slot_changeState(QAudio::State sta)***********";
}

void Audio::StartAudio(QString filename)
{
    m_file = new QFile;
    m_file->setFileName(filename);
    bool o_state = m_file->open(QIODevice::WriteOnly);
    if(!o_state)
    {

        return;
    }
    m_audio->start(m_file);

}

QAudioInput* Audio::getAudio()
{
    return m_audio;
}
void Audio::StopAudio()
{
        m_audio->stop();
}
