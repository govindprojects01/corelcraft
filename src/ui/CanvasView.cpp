#include "CanvasView.h"
#include <QPainter>
#include <QWheelEvent>
CanvasView::CanvasView(QGraphicsScene *scene,QWidget *parent):QGraphicsView(scene,parent){
 setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing|QPainter::SmoothPixmapTransform);
 setBackgroundBrush(QColor("#272a30")); setDragMode(QGraphicsView::RubberBandDrag);
 setTransformationAnchor(QGraphicsView::AnchorUnderMouse); setResizeAnchor(QGraphicsView::AnchorViewCenter);
}
void CanvasView::wheelEvent(QWheelEvent *event){
 const qreal factor=event->angleDelta().y()>0?1.15:1.0/1.15; scale(factor,factor);
}
