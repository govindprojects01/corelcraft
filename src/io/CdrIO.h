#pragma once
#include <QString>
namespace CdrIO{
 bool importFile(const QString&,QString*error=nullptr);
 bool exportFile(const QString&,QString*error=nullptr);
}
