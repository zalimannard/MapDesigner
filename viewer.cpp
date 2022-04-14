#include <QMenuBar>

#include "viewer.h"

Viewer::Viewer(QWidget *parent)
    : QMainWindow(parent)
{
    createActions();
    createMenus();
}

Viewer::~Viewer()
{
}

void Viewer::createActions()
{
    createProjectAct = new QAction(tr("&Создать проект"), this);
    openProjectAct = new QAction(tr("&Открыть проект"), this);
    saveProjectAct = new QAction(tr("&Сохранить проект"), this);
    exitAct = new QAction(tr("&Выйти"), this);

    createTableAct = new QAction(tr("&Создать таблицу"), this);
    openTableAct = new QAction(tr("&Открыть таблицу"), this);
    deleteTableAct = new QAction(tr("&Удалить таблицу"), this);
    requestAct = new QAction(tr("&Запрос"), this);

    layersAct = new QAction(tr("&Слои"), this);
    toolsAct = new QAction(tr("&Инструменты"), this);

    aboutProgramAct = new QAction(tr("&О программе"), this);
}

void Viewer::createMenus()
{
    fileMenu = new QMenu(tr("&Файл"), this);
    fileMenu->addAction(createProjectAct);
    fileMenu->addAction(openProjectAct);
    fileMenu->addAction(saveProjectAct);
    fileMenu->addAction(exitAct);

    tablesMenu = new QMenu(tr("&Таблица"), this);
    tablesMenu->addAction(createTableAct);
    tablesMenu->addAction(openTableAct);
    tablesMenu->addAction(deleteTableAct);
    tablesMenu->addAction(requestAct);


    windowMenu = new QMenu(tr("&Окно"), this);
    windowMenu->addAction(layersAct);
    windowMenu->addAction(toolsAct);


    helpMenu = new QMenu(tr("&Помощь"), this);
    helpMenu->addAction(aboutProgramAct);



    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(tablesMenu);
    menuBar()->addMenu(windowMenu);
    menuBar()->addMenu(helpMenu);
}


//#include <QMenuBar>

//#include "viewer.h"

//Viewer::Viewer(QWidget *parent)
//    : QMainWindow(parent)
//{
//    createActions();
//    createMenus();
//}

//Viewer::~Viewer()
//{
//}

//void Viewer::createActions()
//{
//    createTableAct = new QAction(tr("&Создать таблицу"), this);
//    openTableAct = new QAction(tr("&Открыть таблицу"), this);
//    deleteTableAct = new QAction(tr("&Удалить таблицу"), this);
//    requestAct = new QAction(tr("&Запрос"), this);
//}

//void Viewer::createMenus()
//{
////    fileMenu = new QMenu(tr("&Файл"), this);
////    fileMenu->addAction(createProjectAct);
////    fileMenu->addAction(openProjectAct);
////    fileMenu->addAction(saveProjectAct);
////    fileMenu->addAction(exitAct);

//    tablesMenu = new QMenu(tr("&Таблица"), this);
//    tablesMenu->addAction(createTableAct);
//    tablesMenu->addAction(openTableAct);
//    tablesMenu->addAction(deleteTableAct);
//    tablesMenu->addAction(requestAct);

////    windowMenu = new QMenu(tr("&Окно"), this);
////    windowMenu->addAction(layersAct);
////    windowMenu->addAction(toolsAct);

////    helpMenu = new QMenu(tr("&Помощь"), this);
////    helpMenu->addAction(aboutProgramAct);


//    menuBar()->addMenu(fileMenu);
//    menuBar()->addMenu(tablesMenu);
//    menuBar()->addMenu(windowMenu);
//    menuBar()->addMenu(helpMenu);
//}
