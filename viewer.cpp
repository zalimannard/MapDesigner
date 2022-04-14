#include <QMenuBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>

#include "viewer.h"
#include "project.h"

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
    createProjectAct->setShortcut(tr("Ctrl+N"));
    connect(createProjectAct, SIGNAL(triggered()), this, SLOT(createProject()));

    openProjectAct = new QAction(tr("&Открыть проект"), this);
    openProjectAct->setShortcut(tr("Ctrl+O"));
    connect(openProjectAct, SIGNAL(triggered()), this, SLOT(openProject()));

    saveProjectAct = new QAction(tr("&Сохранить проект"), this);
    saveProjectAct->setShortcut(tr("Ctrl+S"));
    connect(saveProjectAct, SIGNAL(triggered()), this, SLOT(saveProject()));

    saveProjectAsAct = new QAction(tr("&Сохранить проект как"), this);
    saveProjectAsAct->setShortcut(tr("Ctrl+W"));
    connect(saveProjectAsAct, SIGNAL(triggered()), this, SLOT(saveProjectAs()));

    selectMapAct = new QAction(tr("&Выбрать карту"), this);
    selectMapAct->setShortcut(tr("Ctrl+M"));
    connect(selectMapAct, SIGNAL(triggered()), this, SLOT(selectMap()));

    exitAct = new QAction(tr("&Выйти"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(exit()));


    createTableAct = new QAction(tr("&Создать таблицу"), this);
    createTableAct->setShortcut(tr("Ctrl+E"));
    connect(createTableAct, SIGNAL(triggered()), this, SLOT(createTable()));

    openTableAct = new QAction(tr("&Открыть таблицу"), this);
    openTableAct->setShortcut(tr("Ctrl+P"));
    connect(openTableAct, SIGNAL(triggered()), this, SLOT(openTable()));

    deleteTableAct = new QAction(tr("&Удалить таблицу"), this);
    deleteTableAct->setShortcut(tr("Ctrl+D"));
    connect(deleteTableAct, SIGNAL(triggered()), this, SLOT(deleteTable()));

    requestAct = new QAction(tr("&Запрос"), this);
    requestAct->setShortcut(tr("Ctrl+R"));
    connect(requestAct, SIGNAL(triggered()), this, SLOT(request()));


    layersAct = new QAction(tr("&Слои"), this);
    layersAct->setShortcut(tr("Ctrl+L"));
    layersAct->setCheckable(true);
    connect(layersAct, SIGNAL(triggered()), this, SLOT(layers()));

    toolsAct = new QAction(tr("&Инструменты"), this);
    toolsAct->setShortcut(tr("Ctrl+T"));
    toolsAct->setCheckable(true);
    connect(toolsAct, SIGNAL(triggered()), this, SLOT(tools()));


    aboutProgramAct = new QAction(tr("&О программе"), this);
    aboutProgramAct->setShortcut(tr("Ctrl+A"));
    connect(aboutProgramAct, SIGNAL(triggered()), this, SLOT(aboutProgram()));

}

void Viewer::createMenus()
{
    fileMenu = new QMenu(tr("&Файл"), this);
    fileMenu->addAction(createProjectAct);
    fileMenu->addAction(openProjectAct);
    fileMenu->addAction(saveProjectAct);
    fileMenu->addSeparator();
    fileMenu->addAction(selectMapAct);
    fileMenu->addSeparator();
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


void Viewer::createProject()
{
    QString path = QFileDialog::getExistingDirectory(0, "Создание проекта", "");
    if (!path.isEmpty())
    {
        if (QDir(path).entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries).count() == 0)
        {
            QString projectName = QInputDialog::getText(
                                  this,
                                  QString::fromUtf8("Введите название проекта"),
                                  QString::fromUtf8("Название проекта:"),
                                  QLineEdit::Normal);
            if (!projectName.isEmpty())
            {
                project_ = new Project(projectName);
                project_->save(path);
                QMessageBox::warning(this, "Имя проекта не введено",
                                     path + " " + projectName);
            }
            else
            {
                QMessageBox::warning(this, "Имя проекта не введено",
                                     "<p><b>Директория не пуста</b></p>"
                                     "<p>Выберите другую или очистите эту</p>");
            }
        }
        else
        {
            QMessageBox::warning(this, "Директория не пуста",
                                 "<p><b>Директория не пуста</b></p>"
                                 "<p>Выберите другую или очистите эту</p>");
        }
    }
}

void Viewer::openProject()
{

}

void Viewer::saveProject()
{

}

void Viewer::saveProjectAs()
{

}

void Viewer::selectMap()
{

}

void Viewer::exit()
{
    close();
}

void Viewer::createTable()
{

}

void Viewer::openTable()
{

}

void Viewer::deleteTable()
{

}

void Viewer::request()
{

}

void Viewer::layers()
{

}

void Viewer::tools()
{

}

void Viewer::aboutProgram()
{
    QMessageBox::about(this, tr("О MapDesigner"),
            tr("<p>Ура программа</p>"));
}
