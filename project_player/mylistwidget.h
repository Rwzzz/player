#ifndef MYLISTWIDGET_H
#define MYLISTWIDGET_H

#include <QObject>
#include <QListWidget>
#include <QIcon>
#include "musiclist.h"
class MyListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit MyListWidget(QWidget *parent = 0);
    void addtoListWidget();
    void SetIcon(QIcon &);
    void clear();

    Musiclist list;

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
signals:

private:
    QListWidgetItem *item;
    QIcon icon;
};

#endif // MYLISTWIDGET_H
