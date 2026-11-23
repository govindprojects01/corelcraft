#include "MainWindow.h"
#include "CanvasView.h"
#include "core/Document.h"
#include "io/SvgIO.h"
#include "io/PdfIO.h"
#include "io/CdrIO.h"
#include <QAction>
#include <QAbstractGraphicsShapeItem>
#include <QColorDialog>
#include <QDockWidget>
#include <QFileDialog>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QInputDialog>
#include <QLineEdit>
#include <QListWidget>
#include <QMessageBox>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QToolBar>
#include <QStatusBar>
MainWindow::MainWindow(QWidget*parent):QMainWindow(parent),m_document(new Document(this)){
 setWindowTitle("CorelCraft — Vector Graphics");resize(1280,820);
 m_view=new CanvasView(m_document->scene(),this);setCentralWidget(m_view);buildInterface();
 m_view->fitInView(m_document->scene()->sceneRect(),Qt::KeepAspectRatio);
 connect(m_document->scene(),&QGraphicsScene::selectionChanged,this,&MainWindow::refreshObjects);
}
void MainWindow::buildInterface(){
 setStyleSheet(R"(
 QMainWindow,QDockWidget,QListWidget{background:#17191d;color:#eeeeee}
 QToolBar{background:#202329;border:0;spacing:5px;padding:6px}
 QToolButton{color:#eeeeee;background:#30343b;padding:7px 10px;border-radius:4px}
 QToolButton:hover{background:#4779e8}
 QDockWidget::title{background:#252a32;padding:7px}
 QStatusBar{background:#202329;color:#c9cdd4}
 )");
 auto*bar=addToolBar("Tools");bar->setMovable(false);
 const auto add=[bar,this](const QString&label,auto slot){auto*a=bar->addAction(label);connect(a,&QAction::triggered,this,slot);};
 add("Select",[this]{m_view->setDragMode(QGraphicsView::RubberBandDrag);});
 add("Rectangle",&MainWindow::addRectangle);add("Ellipse",&MainWindow::addEllipse);
 add("Text",&MainWindow::addText);add("Colour",&MainWindow::chooseColor);
 add("Delete",&MainWindow::deleteSelected);bar->addSeparator();
 add("Import SVG",&MainWindow::importSvg);add("Export SVG",&MainWindow::exportSvg);
 add("Export PDF",&MainWindow::exportPdf);add("CDR status",&MainWindow::showCdrStatus);
 m_objects=new QListWidget(this);auto*dock=new QDockWidget("Objects",this);
 dock->setWidget(m_objects);dock->setMinimumWidth(190);addDockWidget(Qt::RightDockWidgetArea,dock);
 statusBar()->showMessage("Ready | Drag to select/move | Mouse wheel to zoom");
}
void MainWindow::addShape(QGraphicsItem*item,const QString&kind){
 item->setData(0,kind);item->setFlag(QGraphicsItem::ItemIsSelectable,true);item->setFlag(QGraphicsItem::ItemIsMovable,true);
 if(auto*shape=dynamic_cast<QAbstractGraphicsShapeItem*>(item)){shape->setPen(QPen(m_currentColor,2));shape->setBrush(QBrush(Qt::NoBrush));}
 m_document->scene()->addItem(item);item->setSelected(true);refreshObjects();
}
void MainWindow::addRectangle(){auto*i=new QGraphicsRectItem(0,0,180,110);i->setPos(120,140);addShape(i,"Rectangle");}
void MainWindow::addEllipse(){auto*i=new QGraphicsEllipseItem(0,0,150,150);i->setPos(360,180);addShape(i,"Ellipse");}
void MainWindow::addText(){
 bool ok=false;auto value=QInputDialog::getText(this,"Add text","Text:",QLineEdit::Normal,"CorelCraft",&ok);
 if(!ok||value.isEmpty())return;auto*i=new QGraphicsTextItem(value);i->setDefaultTextColor(m_currentColor);
 i->setFont(QFont("Arial",30));i->setPos(150,360);i->setData(0,"Text");
 i->setFlag(QGraphicsItem::ItemIsSelectable,true);i->setFlag(QGraphicsItem::ItemIsMovable,true);
 m_document->scene()->addItem(i);i->setSelected(true);refreshObjects();
}
void MainWindow::chooseColor(){
 auto c=QColorDialog::getColor(m_currentColor,this);if(!c.isValid())return;m_currentColor=c;
 for(auto*i:m_document->scene()->selectedItems()){
  if(auto*t=dynamic_cast<QGraphicsTextItem*>(i))t->setDefaultTextColor(c);
  else if(auto*s=dynamic_cast<QAbstractGraphicsShapeItem*>(i))s->setPen(QPen(c,2));
 }
}
void MainWindow::deleteSelected(){
 const auto selected=m_document->scene()->selectedItems();
 for(auto*i:selected)if(i->data(0).toString()!="page"){m_document->scene()->removeItem(i);delete i;}
 refreshObjects();
}
void MainWindow::importSvg(){
 auto p=QFileDialog::getOpenFileName(this,"Import SVG",{},"SVG (*.svg)");if(p.isEmpty())return;QString e;
 if(!SvgIO::importFile(m_document->scene(),p,&e))QMessageBox::warning(this,"SVG import",e);
 else statusBar()->showMessage("SVG imported as a single object; sub-shapes are not editable yet.");refreshObjects();
}
void MainWindow::exportSvg(){
 auto p=QFileDialog::getSaveFileName(this,"Export SVG","design.svg","SVG (*.svg)");if(p.isEmpty())return;QString e;
 if(!SvgIO::exportScene(m_document->scene(),p,&e))QMessageBox::critical(this,"SVG export",e);else statusBar()->showMessage("SVG exported.");
}
void MainWindow::exportPdf(){
 auto p=QFileDialog::getSaveFileName(this,"Export PDF","design.pdf","PDF (*.pdf)");if(p.isEmpty())return;QString e;
 if(!PdfIO::exportScene(m_document->scene(),p,&e))QMessageBox::critical(this,"PDF export",e);else statusBar()->showMessage("PDF exported.");
}
void MainWindow::showCdrStatus(){QString e;CdrIO::importFile({},&e);QMessageBox::information(this,"CDR compatibility",e);}
void MainWindow::refreshObjects(){
 m_objects->clear();for(auto*i:m_document->scene()->items()){auto label=i->data(0).toString();if(!label.isEmpty()&&label!="page")m_objects->addItem(label);}
}
