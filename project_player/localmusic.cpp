#include "localmusic.h"
#include "ui_localmusic.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QListWidgetItem>
LocalMusic::LocalMusic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LocalMusic)
{
    ui->setupUi(this);
}

LocalMusic::~LocalMusic()
{
    delete ui;
}



void LocalMusic::on_btn_addLocal_clicked()
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
        qDebug()<<info.baseName();
        qDebug()<<info.absoluteFilePath();
        m.setName(info.baseName());
        m.setUrl(info.absoluteFilePath());
        ui->listWidget->SetIcon(ic);
        ui->listWidget->list.Add2Music(m);

       // ui->listWidget->SetIcon(ic);
        //ui->listWidget->addItem(QListWidgetItem(ic,m.getName()));
    }

}

void LocalMusic::on_listWidget_doubleClicked(const QModelIndex &index)
{
    /*获取当前行*/
    int i = index.column();
    emit signal_clicked(i);


}
