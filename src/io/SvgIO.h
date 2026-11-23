#pragma once
#include <QString>
class QGraphicsScene;
namespace SvgIO{
 bool exportScene(QGraphicsScene*,const QString&,QString*error=nullptr);
 bool importFile(QGraphicsScene*,const QString&,QString*error=nullptr);
}
