#ifndef VIEWER_H
#define VIEWER_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include "project.h"

class Viewer : public QMainWindow
{
    Q_OBJECT

public:
    Viewer(QWidget *parent = nullptr);
    ~Viewer();

private:
    Project *project_ = nullptr;
    QString prejectPath = "";

    void createActions();
    void createMenus();

    QAction *createProjectAct;
    QAction *openProjectAct;
    QAction *saveProjectAct;
    QAction *saveProjectAsAct;
    QAction *selectMapAct;
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

private slots:
    void createProject();
    void openProject();
    void saveProject();
    void saveProjectAs();
    void selectMap();
    void exit();

    void createTable();
    void openTable();
    void deleteTable();
    void request();

    void layers();
    void tools();

    void aboutProgram();
};
#endif // VIEWER_H
