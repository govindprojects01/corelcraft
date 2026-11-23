#pragma once
#include <QMainWindow>
#include <QColor>
class CanvasView;class Document;class QListWidget;class QGraphicsItem;
class MainWindow final:public QMainWindow{
 Q_OBJECT
public:explicit MainWindow(QWidget*parent=nullptr);
private slots:
 void addRectangle();void addEllipse();void addText();void chooseColor();void deleteSelected();
 void importSvg();void exportSvg();void exportPdf();void showCdrStatus();void refreshObjects();
private:
 void buildInterface();void addShape(QGraphicsItem*,const QString&);
 Document*m_document{nullptr};CanvasView*m_view{nullptr};QListWidget*m_objects{nullptr};
 QColor m_currentColor{"#222222"};
};
