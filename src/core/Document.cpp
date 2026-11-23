#include "Document.h"
#include <QBrush>
#include <QColor>
#include <QPen>
Document::Document(QObject *parent):m_scene(parent){
 m_scene.setSceneRect(0,0,m_pageSize.width(),m_pageSize.height());
 auto *page=m_scene.addRect(0,0,m_pageSize.width(),m_pageSize.height(),QPen(QColor("#c8c8c8"),1),QBrush(Qt::white));
 page->setZValue(-10000); page->setFlag(QGraphicsItem::ItemIsSelectable,false);
 page->setFlag(QGraphicsItem::ItemIsMovable,false); page->setData(0,"page");
}
void Document::setPageSize(const QSizeF &size){
 if(size.isEmpty())return; m_pageSize=size; m_scene.setSceneRect(0,0,size.width(),size.height());
}
