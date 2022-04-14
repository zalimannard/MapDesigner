#ifndef VIEWER_H
#define VIEWER_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>

class Viewer : public QMainWindow
{
    Q_OBJECT

public:
    Viewer(QWidget *parent = nullptr);
    ~Viewer();

private:
    void createActions();
    void createMenus();

    QAction *createProjectAct;
    QAction *openProjectAct;
    QAction *saveProjectAct;
    QAction *exitAct;

    QAction *createTableAct;
    QAction *openTableAct;
    QAction *deleteTableAct;
    QAction *requestAct;

    QAction *layersAct;
    QAction *toolsAct;

    QAction *aboutProgramAct;


    QMenu *fileMenu;
    QMenu *tablesMenu;
    QMenu *windowMenu;
    QMenu *helpMenu;
};
#endif // VIEWER_H
