#ifndef LOCALMUSIC_H
#define LOCALMUSIC_H

#include <QWidget>

namespace Ui {
class LocalMusic;
}

class LocalMusic : public QWidget
{
    Q_OBJECT

public:
    explicit LocalMusic(QWidget *parent = 0);
    ~LocalMusic();

signals:
    void signal_clicked();
private slots:
    void on_btn_addLocal_clicked(int index);

    void on_listWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::LocalMusic *ui;

};

#endif // LOCALMUSIC_H
