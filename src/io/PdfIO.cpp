#include "PdfIO.h"
#include <QGraphicsScene>
#include <QPdfWriter>
#include <QPainter>
#include <QPageSize>
namespace PdfIO{
bool exportScene(QGraphicsScene*scene,const QString&path,QString*error){
 if(!scene){if(error)*error="No document scene.";return false;}
 QPdfWriter writer(path);writer.setTitle("CorelCraft artwork");writer.setCreator("CorelCraft");
 writer.setPageSize(QPageSize(QPageSize::A4));writer.setResolution(300);QPainter painter;
 if(!painter.begin(&writer)){if(error)*error="Could not start PDF export.";return false;}
 scene->render(&painter,QRectF(0,0,writer.width(),writer.height()),scene->sceneRect());
 painter.end();return true;
}
}
