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
#include <QTimer>

#include "viewer.h"
#include "project.h"
#include "circle.h"
#include "polyline.h"
#include "polygon.h"
#include "rectangle.h"
#include "stylechooser.h"
#include "text.h"
#include "infectionzone.h"

Viewer::Viewer(QWidget *parent)
    : QMainWindow(parent)
{
    imageLabel_ = new MapLabel;
    imageLabel_->setBackgroundRole(QPalette::Base);
    imageLabel_->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel_->setScaledContents(true);

    scrollArea_ = new MyScrollArea;
    scrollArea_->setBackgroundRole(QPalette::Dark);
    scrollArea_->setAlignment(Qt::AlignCenter);
    scrollArea_->setWidget(imageLabel_);
    setCentralWidget(scrollArea_);

    createActions();
    createMenus();
    createToolbar();

    setWindowTitle(tr("Map Designer"));
    resize(1280, 720);

    QString projectFilePath = "/home/zalimannard/Projects/MapDesignerTest/Example.mdp";
    QString projectName = projectFilePath.split("/").last().split(".").first();
    QString projectDirPath = projectFilePath.remove(projectFilePath.lastIndexOf("/"), projectFilePath.split("/").last().length() + 1);
    project_ = new Project(projectName);
    getProject()->open(projectDirPath);
    updateActions();
    updateToolbar();

    imageLabel_->repaint(getProject());

    if (getProject()->isMapExist())
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
    if (toolBar_ == nullptr)
    {
        toolBar_ = new ToolBar(project_);
        addToolBar(Qt::LeftToolBarArea, toolBar_);
        toolBar_->setVisible(true);
    }
}

void Viewer::createLayerDock()
{
    if (layerDock_ == nullptr)
    {
        layerDock_ = new LayerDock(project_, imageLabel_);
        addDockWidget(Qt::RightDockWidgetArea, layerDock_);
        layerDock_->setVisible(true);
    }
}

void Viewer::updateActions()
{

}

void Viewer::updateToolbar()
{
    removeToolBar(toolBar_);
    toolBar_ = new ToolBar(project_);
    addToolBar(Qt::LeftToolBarArea, toolBar_);
    toolBar_->setVisible(toolsAct->isChecked());
}

void Viewer::endPainting()
{
    if (lastLayerItem_ != nullptr)
    {
        if (!lastLayerItem_->isHealthy())
        {
            getProject()->layerAt(layerDock_->getCurrentTopLevelIndex())->remove(layerDock_->getCurrentSecondLevelIndex());
        }
        layerDock_->update();
    }
}

Project* Viewer::getProject()
{
    return project_;
}

MapLabel* Viewer::getImageLabel()
{
    return imageLabel_;
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
    imageLabel_->repaint(getProject());
}

void Viewer::openProject()
{
    QString projectFilePath = QFileDialog::getOpenFileName(
                this, tr("Открыть проект"), QDir::currentPath(), tr("Файл проекта (*.mdp)"));
    QString projectName = projectFilePath.split("/").last().split(".").first();
    QString projectDirPath = projectFilePath.remove(projectFilePath.lastIndexOf("/"), projectFilePath.split("/").last().length() + 1);
    project_ = new Project(projectName);
    getProject()->open(projectDirPath);
    updateActions();
    updateToolbar();
    imageLabel_->repaint(getProject());
    if (getProject()->isMapExist())
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
        getProject()->setMap(mapPath);

        createLayerDock();
        updateActions();
        imageLabel_->repaint(getProject());
    }
}

void Viewer::exit()
{
    close();
}

void Viewer::zoomIn()
{
    imageLabel_->setScaleFactor(imageLabel_->getScaleFactor() * 1.2);
    imageLabel_->repaint(getProject());
}

void Viewer::zoomOut()
{
    imageLabel_->setScaleFactor(imageLabel_->getScaleFactor() / 1.2);
    imageLabel_->repaint(getProject());
}

void Viewer::normalSize()
{
    imageLabel_->setScaleFactor(1);
    imageLabel_->repaint(getProject());
}

void Viewer::fitSize()
{
    QImage image(getProject()->getMap()->getPathToImage());
    imageLabel_->setScaleFactor(qMin((qreal)scrollArea_->height() / image.height(),
                                    (qreal)scrollArea_->width() / image.width()));
    imageLabel_->repaint(getProject());
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
    return Point((event->pos().x() - scrollArea_->geometry().x() - imageLabel_->pos().x()) / imageLabel_->getScaleFactor(),
                 (event->pos().y() - scrollArea_->geometry().y() - imageLabel_->pos().y()) / imageLabel_->getScaleFactor());
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
        if (getProject()->isMapExist())
        {
            switch (event->button())
            {
                case Qt::LeftButton:
                {
                    qint64 currentTopLevelIndex = layerDock_->getCurrentTopLevelIndex();

                    if (lastCursorType_ != toolBar_->getCursorType())
                    {
                        drawingMode_ = false;
                        endPainting();
                    }

                    if (windMode_)
                    {
                        lastPoint_ = getProject()->getMap()->getWind()->appendPoint(getMousePointOnImage(event));
                    }
                    else if (drawingMode_)
                    {
                        lastPoint_ = lastLayerItem_->appendPoint(getMousePointOnImage(event));
                    }
                    else
                    {
                        switch (toolBar_->getCursorType())
                        {
                            case CursorType::DEFAULT:
                                break;
                            case CursorType::MOVE_MAP:
                                break;
                            case CursorType::MOVE_OBJECT:
                                break;
                            case CursorType::POLYLINE:
                            {
                                if (layerDock_->isAnySelected())
                                {
                                    Polyline* polyline = new Polyline(getMousePointOnImage(event));
                                    polyline->setStyle(*getProject()->getStyle());
                                    lastLayerItem_ = getProject()->layerAt(currentTopLevelIndex)->push(polyline);
                                    drawingMode_ = true;
                                }
                                else
                                {
                                    messageNoLayerSelected();
                                }
                                break;
                            }
                            case CursorType::CIRCLE:
                            {
                                if (layerDock_->isAnySelected())
                                {
                                    Circle* circle = new Circle(getMousePointOnImage(event));
                                    circle->setStyle(*getProject()->getStyle());
                                    lastLayerItem_ = getProject()->layerAt(currentTopLevelIndex)->push(circle);
                                    drawingMode_ = true;
                                }
                                else
                                {
                                    messageNoLayerSelected();
                                }
                                break;
                            }
                            case CursorType::RECTANGLE:
                            {
                                if (layerDock_->isAnySelected())
                                {
                                    Rectangle* rectangle = new Rectangle(getMousePointOnImage(event));
                                    rectangle->setStyle(*getProject()->getStyle());
                                    lastLayerItem_ = getProject()->layerAt(currentTopLevelIndex)->push(rectangle);
                                    drawingMode_ = true;
                                }
                                else
                                {
                                    messageNoLayerSelected();
                                }
                                break;
                            }
                            case CursorType::POLYGON:
                            {
                                if (layerDock_->isAnySelected())
                                {
                                    Polygon* polygon = new Polygon(getMousePointOnImage(event));
                                    polygon->setStyle(*getProject()->getStyle());
                                    lastLayerItem_ = getProject()->layerAt(currentTopLevelIndex)->push(polygon);
                                    drawingMode_ = true;
                                }
                                else
                                {
                                    messageNoLayerSelected();
                                }
                                break;
                            }
                            case CursorType::TEXT:
                            {
                                if (layerDock_->isAnySelected())
                                {
                                    Text* text = new Text(getMousePointOnImage(event));
                                    text->setStyle(*getProject()->getStyle());
                                    lastLayerItem_ = getProject()->layerAt(currentTopLevelIndex)->push(text);
                                    drawingMode_ = true;
                                }
                                else
                                {
                                    messageNoLayerSelected();
                                }
                                break;
                            }
                            case CursorType::INFECTION:
                            {
                                if (layerDock_->isAnySelected())
                                {
                                    qreal weight = QInputDialog::getDouble(0,
                                                                           "Сколько вещества выброшено?",
                                                                           "Масса(т): ",
                                                                           0, 0, 10000000, 2);
                                    qreal time = QInputDialog::getDouble(0,
                                                                           "Сколько прошло с аварии?",
                                                                           "Время(ч): ",
                                                                           0, 0, 10000000, 2);
                                    InfectionZone* infectionZone = new InfectionZone(getMousePointOnImage(event), getProject()->getMap(), time, weight);
                                    infectionZone->setStyle(*getProject()->getStyle());
                                    getProject()->layerAt(currentTopLevelIndex)->push(infectionZone);
                                }
                                else
                                {
                                    messageNoLayerSelected();
                                }
                                break;
                            }
                            case CursorType::BINDING:
                            {
                                qreal longitude = QInputDialog::getDouble(0,
                                                                        "Ввод",
                                                                        "Долгота:",
                                                                        QLineEdit::Normal, 0, 360, 4);
                                qreal latitude = QInputDialog::getDouble(0,
                                                                        "Ввод",
                                                                        "Широта:",
                                                                        QLineEdit::Normal, 0, 360, 4);
                                getProject()->getMap()->addPoint(getMousePointOnImage(event), Point(longitude, latitude));
                                break;
                            }
                            case CursorType::EARTH_POINT:
                            {
                                Point earthPoint = getProject()->getMap()->imagePointToEarthPoint(getMousePointOnImage(event));

                                QMessageBox message;
                                message.setText("Координаты точки:");
                                message.setInformativeText("Долгота: " + QString::number(earthPoint.getX()) + "\n" +
                                                           "Широта:  " + QString::number(earthPoint.getY()));
                                message.exec();
                                break;
                            }
                            case CursorType::WIND:
                            {
                                Wind* wind = new Wind(getMousePointOnImage(event));
                                wind->setStyle(*getProject()->getStyle());
                                getProject()->getMap()->setWind(*wind);
                                getProject()->getMap()->getWind()->setApplied(false);
                                windMode_ = true;
                                break;
                            }
                            default:
                                break;
                        }
                        lastCursorType_ = toolBar_->getCursorType();
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
            imageLabel_->repaint(getProject());
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
    imageLabel_->repaint(getProject());
}

void Viewer::mouseMoveEvent(QMouseEvent *event)
{
    if (lastPoint_ != nullptr)
    {
        Point point = getMousePointOnImage(event);
        lastPoint_->setX(point.getX());
        lastPoint_->setY(point.getY());
    }
    imageLabel_->repaint(getProject());
}

void Viewer::mouseReleaseEvent(QMouseEvent *event)
{
    if (windMode_)
    {
        if (getProject()->getMap()->getWind()->isMaximumPoint())
        {
            windMode_ = false;
            lastPoint_ = nullptr;
            endPainting();
            toolBar_->setCursorType(CursorType::DEFAULT);
            getProject()->getMap()->getWind()->setApplied(true);
            qreal windSpeed = QInputDialog::getDouble(this,
                                                      QString::fromUtf8("Введите скорость ветра"),
                                                      QString::fromUtf8("Скорость ветра"),
                                                      0, 0, 1000, 2);
            getProject()->getMap()->getWind()->setSpeed(windSpeed);
        }
    }
    else if (drawingMode_)
    {
        if (lastLayerItem_->isMaximumPoint())
        {
            drawingMode_ = false;
            lastPoint_ = nullptr;
            endPainting();
        }
    }
    imageLabel_->repaint(getProject());
}

void Viewer::wheelEvent(QWheelEvent *event)
{
    if (this->isProjectExist())
    {
        if (getProject()->isMapExist())
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
