#include "localmusic.h"
#include "mywidget.h"
#include "ui_mywidget.h"
#include <QPainter>
#include <QPixmap>
#include <QSlider>
#include <QIcon>
#include <QFileDialog>
#include <QDebug>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    m_audio = new Audio;
    m_speech = new Speech;
    isStart = false;
    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->loveMenu->setContextMenuPolicy(Qt::CustomContextMenu);
    /*主页面的一些设置*/
    this->setWindowTitle("RwzPlayer");
    this->setWindowIcon(QIcon(":/image/image/dialog-music.png"));
    resize(1200,800);

    this->setWindowFlags(Qt::FramelessWindowHint);//把窗口设置成没框架的
    this->setAttribute(Qt::WA_TranslucentBackground,true);//背景透明
    /*播放列表模式隐藏，点击按钮后弹出*/
    ui->listWidget_PlayList->hide();
    /*StackWidget窗口启动时需要隐藏（显示主界面）*/
    ui->stackedWidget->hide();
    ui->loveMenu->setFrameShape(QFrame::NoFrame);
    ui->list_palyhistory->setFrameShape(QFrame::NoFrame);

    /*Local右键菜单项*/
    play = new QAction("播放");
    stop = new QAction("暂停");
    del = new QAction("删除");
    addLove = new QAction("添加至我喜欢");
    /*Love右键菜单项*/
    L_play = new QAction("播放");
    L_stop = new QAction("暂停");
    L_del = new QAction("删除");

    /*播放器播放列表的初始化*/
    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist;
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    player->setPlaylist(playlist);
    /*音量控制的槽函数*/
    connect(player, &QMediaPlayer::volumeChanged, ui->Slider_Voice, &QSlider::setValue);
    player->setVolume(50);

    //连接槽与信号
    /*移动滑块控制播放进度*/
    connect(ui->Slider_PlayTime, &QAbstractSlider::valueChanged, this, &MyWidget::setPosition);
    /*Player已经播放的时长来调整滑头的位置*/
    connect(player, &QMediaPlayer::positionChanged, this, &MyWidget::updatePosition);
    /*根据Media的时长设置滑块的范围以及单位*/
    connect(player, &QMediaPlayer::durationChanged, this, &MyWidget::updateDuration);
    connect(player,&QMediaPlayer::currentMediaChanged,this,&MyWidget::slot_mediaChange);
    connect(player,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(slot_state_change(QMediaPlayer::State)));
    //connect(player,SIGNAL(audioAvailableChanged(bool)),this,SLOT(slotAvailableChange(bool)));

    connect(L_play,SIGNAL(triggered(bool)),this,SLOT(slot_Lplay_triggered(bool)));
    connect(L_stop,SIGNAL(triggered(bool)),this,SLOT(slot_Lstop_triggered(bool)));
    connect(L_del,SIGNAL(triggered(bool)),this,SLOT(slot_Ldel_triggered(bool)));




    connect(play,SIGNAL(triggered(bool)),this,SLOT(slot_play_triggered(bool)));
    connect(stop,SIGNAL(triggered(bool)),this,SLOT(slot_stop_triggered(bool)));
    connect(addLove,SIGNAL(triggered(bool)),this,SLOT(slot_addLove_triggered(bool)));
    connect(del,SIGNAL(triggered(bool)),this,SLOT(slot_del_triggered(bool)));


    connect(m_audio->getAudio(), SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));
    QTimer::singleShot(5000, this, SLOT(stopRecording()));
    m_audio->StartAudio("D:\\2.pcm");
}


MyWidget::~MyWidget()
{
    delete ui;
}

//void MyWidget::slotAvailableChange(bool state)
//{
//    if(state)
//        player->play();

//}


void MyWidget::stopRecording()
{
    m_audio->StopAudio();
}
void MyWidget::handleStateChanged(QAudio::State sta)
{
    switch(sta)
    {
    case QAudio::StoppedState:
        if (m_audio->getAudio()->error() != QAudio::NoError) {
              // Error handling
          } else {
              // Finished recording
            QString result = m_speech->SpeechIdentify("D:\\2.pcm");
            if(result == "")
            {
                qDebug() << "1111";
            }else{
                int res = result.indexOf("娜娜");
                ui->Label_speech->setText(result);
                if(res != -1 || isStart)
                {
                    if(isStart && res == -1)
                        deal_speech_ide(result);
                    else
                        isStart = true;
                }
            }

            /*再次开启录音*/
            QTimer::singleShot(5000, this, SLOT(stopRecording()));
            m_audio->StartAudio("D:\\2.pcm");

          }
        break;
    case QAudio::ActiveState:
        break;
    default:
        break;


    }
}
void MyWidget::deal_speech_ide(QString &str)
{
    qDebug() << str;
    if(str.indexOf("暂停") != -1)
         player->pause();
    else if((str.indexOf("开始") != -1) || (str.indexOf("播放") != -1))
         player->play();
    else if((str.indexOf("下一") != -1) ||(str.indexOf("切歌") != -1) )
        this->on_btn_Next_pressed();
    else if((str.indexOf("上一") != -1))
        this->on_btn_Pre_pressed();
    else if((str.indexOf("词") != -1))
        this->on_btn_Lrc_pressed();
/**/else if((str.indexOf("音") != -1))
    {


        if((str.indexOf("大") != -1))
        {
            int value = player->volume();
            if((value+20) >= 100)
                this->on_Slider_Voice_valueChanged(100);
            else{
                this->on_Slider_Voice_valueChanged(value+20);
            }
        }else if((str.indexOf("小") != -1))
        {
            int value = player->volume();
            if((value-20) <= 0)
                this->on_Slider_Voice_valueChanged(0);
            else{
                this->on_Slider_Voice_valueChanged(value-20);
            }
        }else{
            this->on_btn_Voice_pressed();
        }
/**/}else if((str.indexOf("退出") != -1))
        isStart = false;
    //else if((str.indexOf("放一首") != -1))




}
void MyWidget::slot_state_change(QMediaPlayer::State state)
{
    switch(state)
    {
        case QMediaPlayer::PlayingState:
            ui->btn_Play->setStyleSheet(
            "QPushButton"
            "{"
            " border-image:url(:/image/image/btn_pause.png);"
            "}"
            );
            break;
        case QMediaPlayer::StoppedState:
            break;
        case QMediaPlayer::PausedState:
            ui->btn_Play->setStyleSheet(
            "QPushButton"
            "{"
            " border-image:url(:/image/image/btn_play.png);"
            "}"
            );
            break;
        default:
            break;

    }

}
void MyWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {

        //move(event->globalPos() );
        /*鼠标点之间的的相对距离 来移动整个窗口*/
        move(this->frameGeometry().topLeft()+event->globalPos()-p);
        /*替换最新时刻的坐标*/
        p = event->globalPos();
    }

}



void MyWidget::mousePressEvent(QMouseEvent *event)
{

    if(event->button() == Qt::LeftButton)
    {
        /*当前点击坐标-窗口左上角坐标 */
        //p = event->globalPos() - this->frameGeometry().topLeft();
        //保存按下时的坐标
        p = event->globalPos();
    }


}

/*将歌单列表添加到播放列表*/
void MyWidget::add_musiclist_to_playlist(Musiclist &m,QMediaPlaylist *ml)
{

    ml->clear();
    QVector<Music>::iterator it= m.vr.begin();
    for(; it != m.vr.end();it++)
    {
       ml->addMedia(QUrl(it->getUrl()));
    }

}

/*在ListWIdget添加一行*/
void MyWidget::add_one_music_to_listwidget(Music &m,QListWidget *lw)
{
    QIcon ic;
    if(lw == ui->listWidget)
    {       
        ic = QIcon(":/image/image/systemTrayIcon.png");

    }else if(lw == ui->list_palyhistory)
    {
         ic = QIcon(":/image/image/music.png");
    }else if(lw == ui->listWidget_PlayList)
    {
        ic = QIcon(":/image/image/btn_music (3).png");
    }
    item = new QListWidgetItem(ic,m.getName());
    lw->addItem(item);

}
/*在音乐菜单全部添加到ListWidget中*/
void MyWidget::add_musiclist_to_listwidget(Musiclist &m,QListWidget *lw)
{
    clearlistwidget(lw);
    QVector<Music>::iterator it= m.vr.begin();
    for(; it != m.vr.end();it++)
    {
        add_one_music_to_listwidget(*it,lw);
    }

}
/*ListWidget删除一首歌曲*/
void MyWidget::delete_one_music_in_listwidget(Music &m,QListWidget *lw)
{

    QList<QListWidgetItem *> l = lw->findItems(m.getName(),Qt::MatchFixedString|Qt::MatchCaseSensitive);
    for(int i = 0; i < l.size(); i++)
    {
        item = l.at(i);
        lw->takeItem(lw->row(item));
        delete item;
    }

}
/*清除QListWidget中所有歌曲*/
void MyWidget::clearlistwidget(QListWidget *lw)
{
    int c = lw->count();
    for(int i =c-1 ; i >=0; i--)
    {
        item = lw->item(i);
        item = lw->takeItem(i);
        delete item;
    }
}


void MyWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);

}

void MyWidget::slot_mediaChange(const QMediaContent &m)
{
    if(m.isNull())
        return;
    QString url = m.canonicalUrl().toString();
    QFileInfo info(url);
    Music mc;
    mc.setName(info.baseName());
    mc.setUrl(url);
    Music * c = playhistory.FindMusic(mc.getName());
    if(c)
    {
        delete_one_music_in_listwidget(*c,ui->list_palyhistory);
        playhistory.Delete2Music(*c);
    }
    playhistory.Add2Music(mc);
    add_one_music_to_listwidget(mc,ui->list_palyhistory);
    /*歌词处理*/
    QString mp3FilePath=mc.getUrl();
    mp3FilePath.replace(".mp3",".lrc");
    ui->Widget_lyric->process(mp3FilePath);
}




QString formatTime(qint64 timeMilliSeconds)
{
    qint64 seconds = timeMilliSeconds / 1000;
    const qint64 minutes = seconds / 60;
    seconds -= minutes * 60;
    return QStringLiteral("%1:%2")
        .arg(minutes, 2, 10, QLatin1Char('0'))
        .arg(seconds, 2, 10, QLatin1Char('0'));
}

void MyWidget::updatePosition(qint64 position)
{
    ui->Slider_PlayTime->setValue(static_cast<int>(position));
    ui->Label_PlayingTime->setText(formatTime(position));
    ui->Widget_lyric->show(position);

}

void MyWidget::updateDuration(qint64 duration)
{
    ui->Slider_PlayTime->setRange(0, static_cast<int>(duration));
    ui->Slider_PlayTime->setEnabled(static_cast<int>(duration) > 0);
    ui->Slider_PlayTime->setPageStep(static_cast<int>(duration) / 10);
    ui->Label_TotalTime->setText(formatTime(player->duration()));
}

void MyWidget::setPosition(int position)
{
    /*updatePosition中对Slider使用SetValue也会触发Slider的ValueChanged信号
    * 使用判断是为了忽略这种情况触发的信号
    */
    if (qAbs(player->position() - position) > 60)
        player->setPosition(position);
}


/*播放列表按钮的槽函数*/
void MyWidget::on_btn_PlayList_clicked()
{
    if(ui->listWidget_PlayList->isHidden())
    {
        ui->listWidget_PlayList->show();
    }else{
        ui->listWidget_PlayList->hide();
    }
}

/*StackWidget切换*/
void MyWidget::on_btn_LocalMusic_pressed()
{

    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->show();
}

void MyWidget::on_btn_LoveMusic_pressed()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->stackedWidget->show();
}


void MyWidget::on_btn_playhistory_pressed()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget->show();
}

/**/
void MyWidget::on_btn_Play_pressed()
{

    if(playlist->isEmpty()&&(player->mediaStatus()==QMediaPlayer::NoMedia))
    {
       /*无歌曲播放，不做任何处理*/
    }
    else if(player->state() == QMediaPlayer::PlayingState) /*处于正在播放状态*/
    {
        player->pause();

    }else{
        player->play();

    }

}
void MyWidget::on_btn_Pre_pressed()
{
    playlist->previous();
}
void MyWidget::on_btn_Next_pressed()
{
    playlist->next();
}

void MyWidget::on_btn_PlayMode_pressed()
{
    if(playlist->playbackMode()==QMediaPlaylist::Loop){     //随机播放
        ui->btn_PlayMode->setStyleSheet(
        "QPushButton"
        "{"
        " background-image:url(:/image/image/play-random.png);"
        " background-repeat:no-repeat;"
        " background-position:center center;"
        " border:none;"
        "}"
        );

        playlist->setPlaybackMode(QMediaPlaylist::Random);

    }else if(playlist->playbackMode()==QMediaPlaylist::Random){ //单曲循环
        ui->btn_PlayMode->setStyleSheet(
        "QPushButton"
        "{"
        " background-image:url(:/image/image/loop-one.png);"
        " background-repeat:no-repeat;"
        " background-position:center center;"
        " border:none;"
        "}"
        );
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    }else if(playlist->playbackMode()==QMediaPlaylist::CurrentItemInLoop){ //列表循环
        ui->btn_PlayMode->setStyleSheet(
        "QPushButton"
        "{"
        " background-image:url(:/image/image/loop.png);"
        " background-repeat:no-repeat;"
        " background-position:center center;"
        " border:none;"
        "}"
        );

        playlist->setPlaybackMode(QMediaPlaylist::Loop);

    }


}


void MyWidget::on_btn_Lrc_pressed()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->stackedWidget->show();

}

void MyWidget::on_btn_Voice_pressed()
{
    //ui->Slider_Voice->setValue(0);

    player->setVolume(0);

}

void MyWidget::on_Slider_Voice_valueChanged(int value)
{
    player->setVolume(value);
}



void MyWidget::on_btn_quit_clicked()
{
    this->close();
}

void MyWidget::on_btn_minScreen_clicked()
{
    showMinimized();
}

qint64 getAudioTime(const QString &filePath)
{
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        qint64 fileSize = file.size();
        qint64 time = fileSize / (16000.0 * 2.0);
        file.close();
        return time;
    }
    return -1;
}
/****************************************************************************/
/*listwidget为本地音乐菜单*/
void MyWidget::on_btn_addLocal_clicked()
{
    QStringList filePaths =
       QFileDialog::getOpenFileNames(this, tr("Open File"),
                                    "./",
                                    tr("MP3 files (*.mp3);;All files (*.*)"));

    Music m;
    QIcon ic = QIcon(":/image/image/systemTrayIcon.png");
    for(int i = 0; i < filePaths.size();i++)
    {
        QString str = filePaths.at(i);
        QFileInfo info(str);

        m.setName(info.baseName());
        m.setUrl(info.absoluteFilePath());

        /*添加到MusicLIst*/
        if(local.FindMusic(m.getName())) //已经存在则忽略
        {
            continue;
        }
        this->local.Add2Music(m);
        /*添加到ListWidget*/
        add_one_music_to_listwidget(m,ui->listWidget);
        /*在播放，需要添加进Playlist*/
        if(local.GetPlayState())
        {
            playlist->addMedia(QUrl(m.getUrl()));
            add_one_music_to_listwidget(m,ui->listWidget_PlayList);//添加到播放列表显示
        }

    }
}

void MyWidget::on_listWidget_doubleClicked(const QModelIndex &index)
{
    /*本地音乐列表没在playlist中播放*/
    if(!local.GetPlayState())
    {
         add_musiclist_to_playlist(local,playlist);
         add_musiclist_to_listwidget(local,ui->listWidget_PlayList);
         local.SetPlayState(true);
         love.SetPlayState(false);
    }
    int i = index.row();   
    playlist->setCurrentIndex(i);
    player->play();

}


void MyWidget::on_listWidget_customContextMenuRequested(const QPoint &pos)
{

        m_local = new QMenu(ui->listWidget);
        m_local->addAction(this->play);
        m_local->addAction(this->stop);
        m_local->addAction(this->del);
        m_local->addAction(this->addLove);
        m_local->exec(QCursor::pos());
        delete m_local;
}

/*右键菜单play触发 Action的槽函数*/
void MyWidget::slot_play_triggered(bool i)
{
    int row = ui->listWidget->currentRow();

    if(local.GetPlayState())
    {
        int index = playlist->currentIndex();
        if(index == row)
        {
            player->play();
            return;
        }

        playlist->setCurrentIndex(row);


    }else{
        add_musiclist_to_playlist(local,playlist);
        add_musiclist_to_listwidget(local,ui->listWidget_PlayList);
    }

    local.SetPlayState(true);
    love.SetPlayState(false);
    player->play();


}
/*右键菜单stop触发 Action的槽函数*/
void MyWidget::slot_stop_triggered(bool i)
{

    if(local.GetPlayState())
    {
        player->pause();


    }

}

void MyWidget::slot_addLove_triggered(bool i)
{
    QIcon ic = QIcon(":/image/image/like.png");
    item = new QListWidgetItem(*ui->listWidget->currentItem());
    item->setIcon(ic);
    QString name = item->text();
    for(auto it = local.vr.begin();it != local.vr.end();it++)
    {
        if(it->name == name)
        {
            love.Add2Music(*it);
        }
    }
    ui->loveMenu->addItem(item);

}

void MyWidget::slot_del_triggered(bool i)
{
    int row = ui->listWidget->currentRow();
    int line = playlist->currentIndex();
    item = ui->listWidget->takeItem(row);;
    QString st = item->text();
    Music *m = local.FindMusic(st);
    if(local.GetPlayState())
    {
        if(row == line)
        {
            playlist->next();

        }

        playlist->removeMedia(row);
        if(m!=NULL)
            delete_one_music_in_listwidget(*m,ui->listWidget_PlayList);
        player->play();
    }


    if(m!=NULL)
        local.Delete2Music(*m);
    delete item;


}
/**************************************************************************/

void MyWidget::on_loveMenu_doubleClicked(const QModelIndex &index)
{
    playlist->clear();
    int i = index.row();
    add_musiclist_to_playlist(love,playlist);
    add_musiclist_to_listwidget(love,ui->listWidget_PlayList);
    playlist->setCurrentIndex(i);
    local.SetPlayState(false);
    love.SetPlayState(true);
    player->play();

}
void MyWidget::on_loveMenu_customContextMenuRequested(const QPoint &pos)
{
    m_love = new QMenu(ui->loveMenu);
    m_love->addAction(this->L_play);
    m_love->addAction(this->L_stop);
    m_love->addAction(this->L_del);
    m_love->exec(QCursor::pos());
    delete m_love;
}


/*右键菜单play触发 Action的槽函数*/
void MyWidget::slot_Lplay_triggered(bool i)
{
    int row = ui->loveMenu->currentRow();
    if(love.GetPlayState())
    {
        int index = playlist->currentIndex();
        if(index == row)
            return;
        playlist->setCurrentIndex(row);

    }else{
        add_musiclist_to_playlist(love,playlist);
        add_musiclist_to_listwidget(love,ui->listWidget_PlayList);
    }
    love.SetPlayState(true);
    local.SetPlayState(false);
    player->play();

}
/*右键菜单stop触发 Action的槽函数*/
void MyWidget::slot_Lstop_triggered(bool i)
{
    if(love.GetPlayState())
    {
        player->pause();

    }

}


void MyWidget::slot_Ldel_triggered(bool i)
{
    int row = ui->loveMenu->currentRow();
    int line = playlist->currentIndex();
    item = ui->loveMenu->takeItem(row);;
    QString st = item->text();
    Music *m = local.FindMusic(st);

    if(love.GetPlayState())
    {
        if(row == line)
        {
            playlist->setCurrentIndex(playlist->nextIndex());
            player->play();
        }
        playlist->removeMedia(row);
        if(m!=NULL)
            delete_one_music_in_listwidget(*m,ui->listWidget_PlayList);
        player->play();
    }
    if(m!=NULL)
        love.Delete2Music(*m);

    delete item;


}









void MyWidget::on_listWidget_PlayList_doubleClicked(const QModelIndex &index)
{
    int i = index.row();
    playlist->setCurrentIndex(i);
}



void MyWidget::on_btn_clearlist_clicked()
{
    if(playhistory.vr.isEmpty())
        return;

    playhistory.ClearList();
    clearlistwidget(ui->list_palyhistory);
}




void MyWidget::on_btn_changeSkin_clicked()
{

}
