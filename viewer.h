#ifndef VIEWER_H
#define VIEWER_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QScrollBar>
#include <QLabel>
#include <QScrollArea>
#include <QGraphicsSceneWheelEvent>
#include "project.h"
#include "myscrollarea.h"

class Viewer : public QMainWindow
{
    Q_OBJECT

public:
    Viewer(QWidget *parent = nullptr);
    ~Viewer();

private:
    Project *project_ = nullptr;
    QString projectDirPath_ = "";

    void createActions();
    void createMenus();
    void updateActions();
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
    void repaint();

    QLabel *imageLabel;
    MyScrollArea *scrollArea;
    qreal scaleFactor_ = 1.0;

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

private slots:

    void mousePressEvent(QMouseEvent *event);
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
