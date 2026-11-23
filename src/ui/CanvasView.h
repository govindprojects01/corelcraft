#pragma once
#include <QGraphicsView>
class QWheelEvent;
class CanvasView final:public QGraphicsView{
 Q_OBJECT
public:
 explicit CanvasView(QGraphicsScene *scene,QWidget *parent=nullptr);
protected:void wheelEvent(QWheelEvent *event)override;
};
