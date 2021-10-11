#ifndef AUDIO_H
#define AUDIO_H

#include <QObject>
#include <QAudioInput>
#include <QAudioDeviceInfo>
#include <QFile>
/*录音相关*/
class Audio : public QObject
{
    Q_OBJECT
public:
    explicit Audio(QObject *parent = 0);
    /*开始录音*/
    void StartAudio(QString filename);
    /*结束录音*/
    void StopAudio();
    QAudioInput* getAudio();


signals:

public slots:
void slot_changeState(QAudio::State);
private:
    QAudioInput *m_audio;
    QFile *m_file;
};

#endif // AUDIO_H
