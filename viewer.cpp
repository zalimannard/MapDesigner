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
    aboutAct = new QAction(tr("&About"), this);
}

void Viewer::createMenus()
 {

     helpMenu = new QMenu(tr("&Help"), this);
     helpMenu->addAction(aboutAct);

     menuBar()->addMenu(helpMenu);
 }
