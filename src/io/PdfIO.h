#pragma once
#include <QString>
class QGraphicsScene;
namespace PdfIO{bool exportScene(QGraphicsScene*,const QString&,QString*error=nullptr);}
