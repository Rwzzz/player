#include "mylistwidget.h"
#include <QListWidgetItem>
#include <QDebug>
MyListWidget::MyListWidget(QWidget *parent) : QListWidget(parent)
{

}

void MyListWidget::mouseDoubleClickEvent(QMouseEvent *event)
{


}

void MyListWidget::mouseReleaseEvent(QMouseEvent *event)
{

}

void MyListWidget::mouseMoveEvent(QMouseEvent *event)
{


}


void MyListWidget::addtoListWidget()
{
   QVector<Music>::iterator it = list.vr.begin();

   for(;it != list.vr.end();it++)
   {
      qDebug() << it->getName();
      item = new QListWidgetItem(icon,it->getName());
      this->addItem(item);
   }


}

void MyListWidget::SetIcon(QIcon &i)
{
    icon = i;
}

void MyListWidget::clear()
{

}


