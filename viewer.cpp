#include <QMenuBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QVector>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QDebug>
#include <QDrag>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGroupBox>

#include "viewer.h"
#include "project.h"
#include "circle.h"
#include "polyline.h"
#include "polygon.h"
#include "rectangle.h"

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
    createToolbar();

    setWindowTitle(tr("Map Designer"));
    resize(1280, 720);

    QString projectFilePath = "/home/zalimannard/Projects/MapDesignerTest/Example.mdp";
    QString projectName = projectFilePath.split("/").last().split(".").first();
    QString projectDirPath = projectFilePath.remove(projectFilePath.lastIndexOf("/"), projectFilePath.split("/").last().length() + 1);
    project_ = new Project(projectName);
    project_->open(projectDirPath);
    updateActions();
    updateToolbar();
    repaint();
    if (project_->isMapExist())
    {
        createLayerDock();
    }
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
    layersAct->setChecked(true);
    connect(layersAct, SIGNAL(triggered()), this, SLOT(layers()));

    toolsAct = new QAction(tr("&Инструменты"), this);
    toolsAct->setShortcut(tr("Ctrl+T"));
    toolsAct->setCheckable(true);
    toolsAct->setChecked(true);
    connect(toolsAct, SIGNAL(triggered()), this, SLOT(tools()));


    aboutProgramAct = new QAction(tr("&О программе"), this);
    aboutProgramAct->setShortcut(tr("Ctrl+A"));
    connect(aboutProgramAct, SIGNAL(triggered()), this, SLOT(aboutProgram()));

    updateActions();
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

void Viewer::createToolbar()
{
    toolBar = new ToolBar(project_);
    addToolBar(Qt::LeftToolBarArea, toolBar);
    toolBar->setVisible(true);
}

void Viewer::createLayerDock()
{
    layerDock = new LayerDock(project_);
    addDockWidget(Qt::RightDockWidgetArea, layerDock);
    layerDock->setVisible(true);
}

void Viewer::updateActions()
{

}

void Viewer::updateToolbar()
{
    toolBar->setVisible(toolsAct->isChecked());
}

void Viewer::repaint()
{
    if (isProjectExist())
    {
        if (getProject()->isMapExist())
        {
            QPixmap pixmap;
            getProject()->draw(pixmap);

            imageLabel->setPixmap(pixmap);
            imageLabel->resize(pixmap.width() * scaleFactor_, pixmap.height() * scaleFactor_);
        }
    }
}

void Viewer::endPainting()
{
    if (!layerItem->isHealthy())
    {
        getProject()->layerAt(layerDock->getCurrentTopLevelIndex())->remove(layerDock->getCurrentSecondLevelIndex());
    }
    layerDock->update();
}

Project* Viewer::getProject()
{
    return project_;
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
                getProject()->setPath(projectDirPath);
                getProject()->save();
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
    updateActions();
    updateToolbar();
    repaint();
}

void Viewer::openProject()
{
    QString projectFilePath = QFileDialog::getOpenFileName(
                this, tr("Открыть проект"), QDir::currentPath(), tr("Файл проекта (*.mdp)"));
    QString projectName = projectFilePath.split("/").last().split(".").first();
    QString projectDirPath = projectFilePath.remove(projectFilePath.lastIndexOf("/"), projectFilePath.split("/").last().length() + 1);
    project_ = new Project(projectName);
    project_->open(projectDirPath);
    updateActions();
    updateToolbar();
    repaint();
    if (project_->isMapExist())
    {
        createLayerDock();
    }
}

void Viewer::saveProject()
{
    getProject()->save();
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
                getProject()->setName(projectName);
                getProject()->setPath(projectDirPath);
                getProject()->save();
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
}

void Viewer::selectMap()
{
    if (isProjectExist())
    {
        QString mapPath = QFileDialog::getOpenFileName(
                    this, tr("Выбрать карту"), QDir::currentPath(), tr("Image (*.jpg *.png *.gif)"));
        project_->setMap(mapPath);

        createLayerDock();
        updateActions();
        repaint();
    }
}

void Viewer::exit()
{
    close();
}

void Viewer::zoomIn()
{
    scaleFactor_ *= 1.2;
    repaint();
}

void Viewer::zoomOut()
{
    scaleFactor_ /= 1.2;
    repaint();
}

void Viewer::normalSize()
{
    scaleFactor_ = 1;
    repaint();
}

void Viewer::fitSize()
{
    QImage image(getProject()->getMap()->getPathToImage());
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
    updateActions();
}

void Viewer::tools()
{
    updateActions();
}

void Viewer::aboutProgram()
{
    QMessageBox::about(this, tr("О MapDesigner"),
            tr("<p>Ура программа работает</p>"));
}

Point Viewer::getMousePointOnImage(QMouseEvent *event)
{
    return Point((event->pos().x() - scrollArea->geometry().x() - imageLabel->pos().x()) / scaleFactor_,
                 (event->pos().y() - scrollArea->geometry().y() - imageLabel->pos().y()) / scaleFactor_);
}

void Viewer::messageNoLayerSelected()
{
    QMessageBox::warning(this, tr("Предупреждение"),
            tr("<p>Не выбран слой!</p>"));
}

void Viewer::mousePressEvent(QMouseEvent *event)
{
    if (this->isProjectExist())
    {
        if (project_->isMapExist())
        {
            switch (event->button())
            {
                case Qt::LeftButton:
                {
                    qint64 currentTopLevelIndex = layerDock->getCurrentTopLevelIndex();

                    switch (toolBar->getCursorType())
                    {
                        case CursorType::DEFAULT:
                            break;
                        case CursorType::MOVE_MAP:
                            break;
                        case CursorType::MOVE_OBJECT:
                            break;
                        case CursorType::POLYLINE:
                        {
                            if (layerDock->isAnySelected())
                            {
                                if (drawingMode_)
                                {
                                    lastPoint_ = layerItem->appendPoint(getMousePointOnImage(event));
                                }
                                else
                                {
                                    Polyline* polyline = new Polyline(getMousePointOnImage(event));
                                    polyline->setStyle(currentStyle);
                                    layerItem = getProject()->layerAt(currentTopLevelIndex)->push(polyline);
                                    drawingMode_ = true;
                                }
                            }
                            else
                            {
                                messageNoLayerSelected();
                            }
                            break;
                        }
                        case CursorType::CIRCLE:
                        {
                            if (layerDock->isAnySelected())
                            {
                                if (drawingMode_)
                                {
                                    lastPoint_ = layerItem->appendPoint(getMousePointOnImage(event));
                                }
                                else
                                {
                                    Circle* circle = new Circle(getMousePointOnImage(event));
                                    circle->setStyle(currentStyle);
                                    layerItem = getProject()->layerAt(currentTopLevelIndex)->push(circle);
                                    drawingMode_ = true;
                                }
                            }
                            else
                            {
                                messageNoLayerSelected();
                            }
                            break;
                        }
                        case CursorType::RECTANGLE:
                        {
                            if (layerDock->isAnySelected())
                            {
                                if (drawingMode_)
                                {
                                    lastPoint_ = layerItem->appendPoint(getMousePointOnImage(event));
                                }
                                else
                                {
                                    Rectangle* rectangle = new Rectangle(getMousePointOnImage(event));
                                    rectangle->setStyle(currentStyle);
                                    layerItem = getProject()->layerAt(currentTopLevelIndex)->push(rectangle);
                                    drawingMode_ = true;
                                }
                            }
                            else
                            {
                                messageNoLayerSelected();
                            }
                            break;
                        }
                        case CursorType::POLYGON:
                        {
                            if (layerDock->isAnySelected())
                            {
                                if (drawingMode_)
                                {
                                    lastPoint_ = layerItem->appendPoint(getMousePointOnImage(event));
                                }
                                else
                                {
                                    Polygon* polygon = new Polygon(getMousePointOnImage(event));
                                    polygon->setStyle(currentStyle);
                                    layerItem = getProject()->layerAt(currentTopLevelIndex)->push(polygon);
                                    drawingMode_ = true;
                                }
                            }
                            else
                            {
                                messageNoLayerSelected();
                            }
                            break;
                        }
                        case CursorType::TEXT:
                        {
                            break;
                        }
                        case CursorType::INFECTION:
                        {
                            break;
                        }
                        case CursorType::BINDING:
                        {
                            qreal longitude = QInputDialog::getDouble(0,
                                                                    "Ввод",
                                                                    "Долгота:",
                                                                    QLineEdit::Normal);
                            qreal latitude = QInputDialog::getDouble(0,
                                                                    "Ввод",
                                                                    "Широта:",
                                                                    QLineEdit::Normal);
                            getProject()->getMap()->addPoint(getMousePointOnImage(event), Point(longitude, latitude));
                        }
                            break;
                        case CursorType::EARTH_POINT:
                        {
                            Point earthPoint = getProject()->getMap()->imagePointToEarthPoint(getMousePointOnImage(event));

                            QMessageBox message;
                            message.setText("Координаты точки:");
                            message.setInformativeText("Долгота: " + QString::number(earthPoint.getX()) + "\n" +
                                                       "Широта:  " + QString::number(earthPoint.getY()));
                            message.exec();
                        }
                        default:
                            break;
                    }
                    break;
                }
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
    }
}

void Viewer::mouseDoubleClickEvent(QMouseEvent *event)
{
    drawingMode_ = false;
    if (lastPoint_ != nullptr)
    {
        endPainting();
    }
    lastPoint_ = nullptr;
    repaint();
}

void Viewer::mouseMoveEvent(QMouseEvent *event)
{
    if (lastPoint_ != nullptr)
    {
        Point point = getMousePointOnImage(event);
        lastPoint_->setX(point.getX());
        lastPoint_->setY(point.getY());
    }
    repaint();
}

void Viewer::mouseReleaseEvent(QMouseEvent *event)
{
    if (drawingMode_)
    {
        if (layerItem->isMaximumPoint())
        {
            drawingMode_ = false;
            lastPoint_ = nullptr;
            endPainting();
        }
    }
    repaint();
}

void Viewer::wheelEvent(QWheelEvent *event)
{
    if (this->isProjectExist())
    {
        if (project_->isMapExist())
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
    }
}

bool Viewer::isProjectExist()
{
    return project_ != nullptr;
}
