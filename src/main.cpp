#include <QApplication>
#include "ui/MainWindow.h"
int main(int argc,char *argv[]){
 QApplication app(argc,argv);
 QApplication::setApplicationName("CorelCraft");
 QApplication::setOrganizationName("CorelCraft Project");
 MainWindow window; window.show(); return app.exec();
}
