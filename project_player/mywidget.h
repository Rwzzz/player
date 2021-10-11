#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QEvent>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QtSql>
#include <QListWidgetItem>
#include <QMenu>
#include <QAction>
#include "musiclist.h"
#include "audio.h"
#include "speech.h"
#include <QTimer>
namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();
    void openFile();
    void deal_speech_ide(QString &);
    void add_musiclist_to_playlist(Musiclist &,QMediaPlaylist *);
    void add_one_music_to_listwidget(Music &,QListWidget *);
    void add_musiclist_to_listwidget(Musiclist &,QListWidget *);
    void delete_one_music_in_listwidget(Music &,QListWidget *);
    void clearlistwidget(QListWidget *);

protected:

    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

private slots:

    /*UI界面的槽函数*/
    void on_btn_PlayList_clicked();

    void on_btn_LocalMusic_pressed();

    void on_btn_LoveMusic_pressed();

    void on_btn_playhistory_pressed();

    void on_btn_Pre_pressed();

    void on_btn_Play_pressed();

    void on_btn_Next_pressed();

    void on_btn_PlayMode_pressed();

    void on_btn_Lrc_pressed();

    void on_btn_Voice_pressed();

    void on_Slider_Voice_valueChanged(int value);

    void on_btn_quit_clicked();

    void on_btn_minScreen_clicked();

    void on_btn_addLocal_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_listWidget_customContextMenuRequested(const QPoint &pos);

    void on_btn_clearlist_clicked();

    void on_listWidget_PlayList_doubleClicked(const QModelIndex &index);

    //自己写的槽函数
    void slot_play_triggered(bool);/*Local右键播放*/
    void slot_stop_triggered(bool); /*Local右键暂停*/
    void slot_addLove_triggered(bool); /*Local右键添加至最爱*/
    void slot_del_triggered(bool); /*Local右键快捷删除*/

    void slot_Lplay_triggered(bool);/*Love右键播放*/
    void slot_Lstop_triggered(bool); /*Love右键暂停*/
    void slot_Ldel_triggered(bool); /*Love右键快捷删除*/
    void slot_state_change(QMediaPlayer::State state); /*播放状态改变*/
    void on_loveMenu_doubleClicked(const QModelIndex &index);
    void slot_mediaChange(const QMediaContent &);    /*音乐切换*/
    void updatePosition(qint64 position); /*跟踪音乐进度条*/
    void updateDuration(qint64 duration); /*音乐切换后音乐时长的获取*/
    void setPosition(int position);/*滑块移动设置音乐播放的位置*/
    //void slotAvailableChange(bool);
    void stopRecording();
    void handleStateChanged(QAudio::State);

    void on_loveMenu_customContextMenuRequested(const QPoint &pos);

    void on_btn_changeSkin_clicked();

private:
    Ui::MyWidget *ui;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    /*音乐列表*/
    QListWidgetItem *item;
    Musiclist local;
    Musiclist love;
    Musiclist playhistory;
    /*右击菜单*/
    QMenu * m_local;
    QMenu * m_love;
    QMenu * m_history;
    /*本地右键菜单的ACtion*/
    QAction *play;
    QAction *stop;
    QAction *addLove;
    QAction *del;

    /*Love右键菜单*/
    QAction *L_play;
    QAction *L_stop;
    QAction *L_del;

    QPoint p;
    Audio *m_audio;
    Speech *m_speech;
    bool isStart;


    void on_pushButton_clicked();
};


#endif // MYWIDGET_H
