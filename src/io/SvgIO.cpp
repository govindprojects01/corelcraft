#include "SvgIO.h"
#include <QGraphicsScene>
#include <QGraphicsSvgItem>
#include <QSvgGenerator>
#include <QSvgRenderer>
#include <QPainter>
#include <memory>
namespace SvgIO{
namespace{
class RendererHolder final:public QObject{
public:RendererHolder(std::shared_ptr<QSvgRenderer>r,QObject*p):QObject(p),renderer(std::move(r)){}
 std::shared_ptr<QSvgRenderer>renderer;
};
}
bool exportScene(QGraphicsScene*scene,const QString&path,QString*error){
 if(!scene){if(error)*error="No document scene.";return false;}
 QSvgGenerator gen;gen.setFileName(path);gen.setSize(scene->sceneRect().size().toSize());
 gen.setViewBox(scene->sceneRect());gen.setTitle("CorelCraft artwork");QPainter painter;
 if(!painter.begin(&gen)){if(error)*error="Could not start SVG export.";return false;}
 scene->render(&painter,scene->sceneRect(),scene->sceneRect());painter.end();return true;
}
bool importFile(QGraphicsScene*scene,const QString&path,QString*error){
 if(!scene){if(error)*error="No document scene.";return false;}
 auto renderer=std::make_shared<QSvgRenderer>(path);
 if(!renderer->isValid()){if(error)*error="Invalid or unsupported SVG file.";return false;}
 auto*holder=new RendererHolder(renderer,scene);auto*item=new QGraphicsSvgItem();
 item->setSharedRenderer(holder->renderer.get());item->setPos(40,40);item->setData(0,"SVG");
 item->setFlag(QGraphicsItem::ItemIsSelectable,true);item->setFlag(QGraphicsItem::ItemIsMovable,true);
 scene->addItem(item);return true;
}
}
