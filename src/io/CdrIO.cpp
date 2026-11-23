#include "CdrIO.h"
namespace CdrIO{
bool importFile(const QString&path,QString*error){
 Q_UNUSED(path);if(error)*error="CDR import is not implemented yet. A libcdr-based adapter is planned.";return false;
}
bool exportFile(const QString&path,QString*error){
 Q_UNUSED(path);if(error)*error="Native CDR export is not implemented. Use SVG/PDF export for now.";return false;
}
}
