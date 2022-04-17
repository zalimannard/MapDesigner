#include <QMenuBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QVector>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QDebug>
#include <QDrag>

#include "viewer.h"
#include "project.h"

Viewer::Viewer(QWidget *parent)
    : QMainWindow(parent)
{
    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea = new MyScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setAlignment(Qt::AlignCenter);
    scrollArea->setWidget(imageLabel);
    setCentralWidget(scrollArea);

    createActions();
    createMenus();

    setWindowTitle(tr("Map Designer"));
    resize(1280, 720);
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


    zoomInAct = new QAction(tr("&Приблизить"), this);
    zoomInAct->setShortcut(tr("Ctrl++"));
    connect(zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));

    zoomOutAct = new QAction(tr("&Отдалить"), this);
    zoomOutAct->setShortcut(tr("Ctrl+-"));
    connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));

    normalSizeAct = new QAction(tr("&Нормальный размер"), this);
    normalSizeAct->setShortcut(tr("Ctrl+="));
    connect(normalSizeAct, SIGNAL(triggered()), this, SLOT(normalSize()));

    fitSizeAct = new QAction(tr("&Вместить"), this);
    fitSizeAct->setShortcut(tr("Ctrl+_"));
    connect(fitSizeAct, SIGNAL(triggered()), this, SLOT(fitSize()));


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
    fileMenu->addAction(saveProjectAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(selectMapAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = new QMenu(tr("&Правка"), this);
    editMenu->addAction(zoomInAct);
    editMenu->addAction(zoomOutAct);
    editMenu->addAction(normalSizeAct);
    editMenu->addAction(fitSizeAct);

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
    menuBar()->addMenu(editMenu);
    menuBar()->addMenu(tablesMenu);
    menuBar()->addMenu(windowMenu);
    menuBar()->addMenu(helpMenu);
}

void Viewer::repaint()
{
    if (project_ != nullptr)
    {
        if (project_->isMapExist())
        {
            QImage image(project_->getMap().getPathToImage());
            QPixmap pixmap(QPixmap::fromImage(image));

            imageLabel->setPixmap(pixmap);
            imageLabel->resize(image.width() * scaleFactor_, image.height() * scaleFactor_);
        }
    }
}

void Viewer::createProject()
{
    QString projectDirPath = QFileDialog::getExistingDirectory(0, "Создание проекта", "");
    if (!projectDirPath.isEmpty())
    {
        if (QDir(projectDirPath).entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries).count() == 0)
        {
            QString projectName = QInputDialog::getText(
                                  this,
                                  QString::fromUtf8("Введите название проекта"),
                                  QString::fromUtf8("Название проекта:"),
                                  QLineEdit::Normal);
            if (!projectName.isEmpty())
            {
                project_ = new Project(projectName);
                projectDirPath_ = projectDirPath;
                project_->save(projectDirPath_);
            }
            else
            {
                QMessageBox::critical(this, "Имя проекта не введено",
                                      "<b>Имя проекта не введено</b>");
            }
        }
        else
        {
            QMessageBox::critical(this, "Директория не пуста",
                                  "<p><b>Директория не пуста</b></p>"
                                  "<p>Выберите другую или очистите эту</p>");
        }
    }
    repaint();
}

void Viewer::openProject()
{
    QString projectFilePath = QFileDialog::getOpenFileName(
                this, tr("Открыть проект"), QDir::currentPath(), tr("Файл проекта (*.mdp)"));
    QString projectName = projectFilePath.split("/").last().split(".").first();
    QString projectDirPath = projectFilePath.remove(projectFilePath.lastIndexOf("/"), projectFilePath.split("/").last().length() + 1);
    project_ = new Project(projectName);
    projectDirPath_ = projectDirPath;
    project_->open(projectDirPath_);
    repaint();
}

void Viewer::saveProject()
{
    project_->save(projectDirPath_);
    repaint();
}

void Viewer::saveProjectAs()
{
    QString projectDirPath = QFileDialog::getExistingDirectory(0, "Создание проекта", "");
    if (!projectDirPath.isEmpty())
    {
        if (QDir(projectDirPath).entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries).count() == 0)
        {
            QString projectName = QInputDialog::getText(
                                  this,
                                  QString::fromUtf8("Введите название проекта"),
                                  QString::fromUtf8("Название проекта:"),
                                  QLineEdit::Normal);
            if (!projectName.isEmpty())
            {
                projectDirPath_ = projectDirPath;
                project_->save(projectDirPath_);
            }
            else
            {
                QMessageBox::warning(this, "Имя проекта не введено",
                                     "<b>Имя проекта не введено</b>");
            }
        }
        else
        {
            QMessageBox::critical(this, "Директория не пуста",
                                  "<p><b>Директория не пуста</b></p>"
                                  "<p>Выберите другую или очистите эту</p>");
        }
    }
    repaint();
}

void Viewer::selectMap()
{
    QString mapPath = QFileDialog::getOpenFileName(
                this, tr("Выбрать карту"), QDir::currentPath(), tr("Image (*.jpg *.png *.gif)"));
    project_->setMap(mapPath);

    repaint();
}

void Viewer::exit()
{
    close();
}

void Viewer::zoomIn()
{
    scaleFactor_ *= 1.1;
    repaint();
}

void Viewer::zoomOut()
{
    scaleFactor_ /= 1.1;
    repaint();
}

void Viewer::normalSize()
{
    scaleFactor_ = 1;
    repaint();
}

void Viewer::fitSize()
{
    QImage image(project_->getMap().getPathToImage());
    scaleFactor_ = qMin((qreal)scrollArea->height() / image.height(), (qreal)scrollArea->width() / image.width());
    repaint();
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

void Viewer::mousePressEvent(QMouseEvent *event)
{
    switch (event->button()) {
//        case Qt::LeftButton:
//        {
//        QMessageBox::warning(this, "Имя проекта не введено",
//                             "<b>Имя проекта не введено</b>");
//            break;
//        }
//        case Qt::RightButton:
//        {
//        QMessageBox::warning(this, "Имя проекта не введено",
//                             "<b>Имя проекта не введено</b>");
//            break;
//        }
        case Qt::MiddleButton:
        {
            break;
        }
        default:
        {
            break;
        }
    }

    repaint();
}

void Viewer::wheelEvent(QWheelEvent *event)
{
    QPoint numDegrees = event->angleDelta() / 8;

    if (numDegrees.y() > 0)
    {
        zoomIn();
    }
    else
    {
        zoomOut();
    }
}
