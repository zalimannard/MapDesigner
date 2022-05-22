#ifndef VIEWER_H
#define VIEWER_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QScrollBar>
#include <QLabel>
#include <QScrollArea>
#include <QGraphicsSceneWheelEvent>
#include <QToolBar>
#include <QDockWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include "project.h"
#include "myscrollarea.h"
#include "polyline.h"
#include "layerdock.h"
#include "toolbar.h"
#include "maplabel.h"

class Viewer : public QMainWindow
{
    Q_OBJECT

public:
    Viewer(QWidget *parent = nullptr);
    ~Viewer();

private:
    bool drawingMode_ = false;
    bool windMode_ = false;
    Point* lastPoint_ = nullptr;
    Project* project_ = nullptr;
    LayerItem* lastLayerItem_ = nullptr;
    CursorType lastCursorType_ = CursorType::DEFAULT;
    Style currentStyle_;

    void createActions();
    void createMenus();
    void createToolbar();
    void createLayerDock();
    void updateActions();
    void updateToolbar();
    void updateLayerDock();

    void scaleImage(qreal factor);
    void adjustScrollBar(QScrollBar *scrollBar, qreal factor);
    ToolBar *toolBar_ = nullptr;
    LayerDock *layerDock_ = nullptr;

    Point getMousePointOnImage(QMouseEvent *event);
    void endPainting();

    Project* getProject();
    MapLabel* getImageLabel();

    MapLabel *imageLabel_;
    MyScrollArea *scrollArea_;

    QAction *createProjectAct;
    QAction *openProjectAct;
    QAction *saveProjectAct;
    QAction *saveProjectAsAct;
    QAction *selectMapAct;
    QAction *exitAct;

    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitSizeAct;

    QAction *createTableAct;
    QAction *openTableAct;
    QAction *deleteTableAct;
    QAction *requestAct;

    QAction *layersAct;
    QAction *toolsAct;

    QAction *aboutProgramAct;


    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *tablesMenu;
    QMenu *windowMenu;
    QMenu *helpMenu;

    bool isProjectExist();

    void messageNoLayerSelected();

private slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

    void createProject();
    void openProject();
    void saveProject();
    void saveProjectAs();
    void selectMap();
    void exit();

    void zoomIn();
    void zoomOut();
    void fitSize();
    void normalSize();

    void createTable();
    void openTable();
    void deleteTable();
    void request();

    void layers();
    void tools();

    void aboutProgram();

};
#endif // VIEWER_H
