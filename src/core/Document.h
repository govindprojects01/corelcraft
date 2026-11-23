#pragma once
#include <QGraphicsScene>
#include <QSizeF>
class Document final{
public:
 explicit Document(QObject *parent=nullptr);
 QGraphicsScene *scene() noexcept{return &m_scene;}
 const QSizeF &pageSize() const noexcept{return m_pageSize;}
 void setPageSize(const QSizeF &size);
private:
 QGraphicsScene m_scene;
 QSizeF m_pageSize{794.0,1123.0};
};
