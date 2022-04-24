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
    createLayerDock();

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


    defaultCursorAct = new QAction(QIcon::fromTheme("pointer"), tr("1"), this);
    connect(defaultCursorAct, SIGNAL(triggered()), this, SLOT(setCursorDefault()));

    moveMapCursorAct = new QAction(QIcon::fromTheme("transform-browse"), tr("2"), this);
    connect(moveMapCursorAct, SIGNAL(triggered()), this, SLOT(setCursorMoveMap()));

    moveObjectCursorAct = new QAction(QIcon::fromTheme("object-move"), tr("3"), this);
    connect(moveObjectCursorAct, SIGNAL(triggered()), this, SLOT(setCursorMoveObject()));

    polylineCursorAct = new QAction(QIcon::fromTheme("format-node-line"), tr("4"), this);
    connect(polylineCursorAct, SIGNAL(triggered()), this, SLOT(setCursorPolyline()));

    polygonCursorAct = new QAction(QIcon::fromTheme("itmages-stop"), tr("5"), this);
    connect(polygonCursorAct, SIGNAL(triggered()), this, SLOT(setCursorPolygon()));

    textCursorAct = new QAction(QIcon::fromTheme("edit-select-text"), tr("6"), this);
    connect(textCursorAct, SIGNAL(triggered()), this, SLOT(setCursorText()));

    bindingCursorAct = new QAction(QIcon::fromTheme("edit-paste-in-place"), tr("7"), this);
    connect(bindingCursorAct, SIGNAL(triggered()), this, SLOT(setCursorBinding()));

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
    toolbar->setMovable(true);
    toolbar->setEnabled(true);
    toolbar->addAction(defaultCursorAct);
    toolbar->addAction(moveMapCursorAct);
    toolbar->addAction(moveObjectCursorAct);
    toolbar->addAction(polylineCursorAct);
    toolbar->addAction(polygonCursorAct);
    toolbar->addAction(textCursorAct);
    toolbar->addAction(bindingCursorAct);
    addToolBar(Qt::LeftToolBarArea, toolbar);
}

void Viewer::createLayerDock()
{

    QPushButton *addLayerBtn = new QPushButton();
    addLayerBtn->setIcon(QIcon::fromTheme("list-add"));
    connect(addLayerBtn, SIGNAL (released()),this, SLOT (addLayer()));

    QPushButton *deleteLayerBtn = new QPushButton();
    deleteLayerBtn->setIcon(QIcon::fromTheme("trash-empty"));
    connect(deleteLayerBtn, SIGNAL (released()),this, SLOT (deleteLayer()));

    QPushButton *toggleVisibleBtn = new QPushButton();
    toggleVisibleBtn->setIcon(QIcon::fromTheme("visibility"));
    connect(toggleVisibleBtn, SIGNAL (released()),this, SLOT (toggleVisibleLayer()));

    QPushButton *renameBtn = new QPushButton();
    renameBtn->setIcon(QIcon::fromTheme("edit-select-text"));
    connect(renameBtn, SIGNAL (released()),this, SLOT (renameLayer()));

    QPushButton *moreBtn = new QPushButton();
    moreBtn->setIcon(QIcon::fromTheme("view-more-horizontal"));
    connect(moreBtn, SIGNAL (released()),this, SLOT (moreLayer()));

    QHBoxLayout *layerTools = new QHBoxLayout();
    layerTools->setAlignment(Qt::AlignRight);
    layerTools->addWidget(addLayerBtn);
    layerTools->addWidget(deleteLayerBtn);
    layerTools->addWidget(toggleVisibleBtn);
    layerTools->addWidget(renameBtn);
    layerTools->addWidget(moreBtn);

    tree->setColumnCount(2);
    tree->setColumnWidth(0, 160);
    tree->setHeaderLabels(QStringList() << "Название" << "");

    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->addWidget(tree);
    vbox->addLayout(layerTools);

    QGroupBox *vboxGroup = new QGroupBox();
    vboxGroup->setLayout(vbox);

    dock->setMinimumWidth(280);
    dock->setMinimumHeight(100);
    dock->setWidget(vboxGroup);

    addDockWidget(Qt::RightDockWidgetArea, dock);
}

void Viewer::updateActions()
{
    toolbar->setVisible(toolsAct->isChecked());
    dock->setVisible(layersAct->isChecked());
    if (isProjectExist())
    {
        if (project_->isMapExist())
        {
//            if(project_->getMap().isBinded())
//            {
                defaultCursorAct->setVisible(true);
                moveMapCursorAct->setVisible(true);
                moveObjectCursorAct->setVisible(true);
                polylineCursorAct->setVisible(true);
                polygonCursorAct->setVisible(true);
                textCursorAct->setVisible(true);
                bindingCursorAct->setVisible(true);
//            }
//            else
//            {
//                defaultCursorAct->setVisible(true);
//                moveMapCursorAct->setVisible(true);
//                moveObjectCursorAct->setVisible(false);
//                polylineCursorAct->setVisible(false);
//                polygonCursorAct->setVisible(false);
//                textCursorAct->setVisible(false);
//                bindingCursorAct->setVisible(true);
//            }
        }
        else
        {
            defaultCursorAct->setVisible(true);
            moveMapCursorAct->setVisible(true);
            moveObjectCursorAct->setVisible(false);
            polylineCursorAct->setVisible(false);
            polygonCursorAct->setVisible(false);
            textCursorAct->setVisible(false);
            bindingCursorAct->setVisible(false);
        }
    }
    else
    {
        defaultCursorAct->setVisible(true);
        moveMapCursorAct->setVisible(false);
        moveObjectCursorAct->setVisible(false);
        polylineCursorAct->setVisible(false);
        polygonCursorAct->setVisible(false);
        textCursorAct->setVisible(false);
        bindingCursorAct->setVisible(false);
    }
}

void Viewer::updateToolbar()
{

}

void Viewer::updateLayerDock()
{

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

bool Viewer::isProjectExist()
{
    return project_ != nullptr;
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
    updateLayerDock();
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
    updateLayerDock();
    repaint();
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
    QString mapPath = QFileDialog::getOpenFileName(
                this, tr("Выбрать карту"), QDir::currentPath(), tr("Image (*.jpg *.png *.gif)"));
    project_->setMap(mapPath);

    updateActions();
    repaint();
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
    QImage image(getProject()->getMap());
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
            tr("<p>Ура программа</p>"));
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
                    switch (cursorType_)
                    {
                    case CursorType::DEFAULT:
                        break;
                    case CursorType::MOVE_MAP:
                        break;
                    case CursorType::MOVE_OBJECT:
                        break;
                    case CursorType::POLYLINE:
                        break;
                    case CursorType::POLYGON:
                        break;
                    case CursorType::TEXT:
                        break;
                    case CursorType::BINDING:
                        break;
                    default:
                        break;
                    }
                    qint64 a = scrollArea->horizontalScrollBar()->value();
                    a = imageLabel->pos().x();
                    imageLabel->pos().setX(111);
//                    QMessageBox::about(this, tr("О MapDesigner"),
//                                       QString::number(cursorType_));
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


void Viewer::setCursorType(CursorType type)
{
    cursorType_ = type;
}

void Viewer::addLayer()
{
    Layer newLayer("Без названия");
    getProject()->pushLayer(newLayer);

    QTreeWidgetItem *item = new QTreeWidgetItem(1);
    QTreeWidgetItem *item2 = new QTreeWidgetItem(1);
    item2->setText(0, "aoeu");
    QTreeWidgetItem *item3 = new QTreeWidgetItem(1);
    item3->setText(0, "snth");
    item->setText(0, "Телебоба" + QString::number(tree->topLevelItemCount()));
    item->addChild(item2);
    item->addChild(item3);
    tree->addTopLevelItem(item);

}

void Viewer::deleteLayer()
{
    if (tree->currentIndex().parent().row() == -1)
    {
        getProject()->removeLayer(tree->currentIndex().row());
        delete tree->takeTopLevelItem(tree->currentIndex().row());
    }
    else
    {
//        project_->layers.at(tree->currentIndex().parent().row())->object.remove(tree->currentIndex().row());
        tree->currentItem()->parent()->removeChild(tree->currentItem());
    }
}

void Viewer::toggleVisibleLayer()
{
    if (tree->currentIndex().parent().row() == -1)
    {
        qint64 currentTopLevelIndex = tree->currentIndex().row();
        bool currentVisible = getProject()->layerAt(currentTopLevelIndex).isVisible();
        getProject()->layerAt(currentTopLevelIndex).setVisible(!currentVisible);
        currentVisible = !currentVisible;
        if (currentVisible)
        {
            tree->topLevelItem(currentTopLevelIndex)->setText(1, "");
        }
        else
        {
            tree->topLevelItem(currentTopLevelIndex)->setText(1, "Скрыт");
        }
    }
    else
    {
        qint64 currentTopLevelIndex = tree->currentIndex().parent().row();
        qint64 currentSecondLevelIndex = tree->currentIndex().row();
//        bool currentVisible = project_->layers.at(currentTopLevelIndex)->object.at(currentSecondLevelIndex).isVisible();
////        project_->layers.at(currentTopLevelIndex)->object.at(currentSecondLevelIndex).setVisible(!currentVisible);
//        currentVisible = !currentVisible;

//        if (currentVisible)
//        {
//            tree->topLevelItem(currentTopLevelIndex)->takeChild(currentSecondLevelIndex)->setText(1, "");
//        }
//        else
//        {
//            tree->topLevelItem(currentTopLevelIndex)->takeChild(currentSecondLevelIndex)->setText(1, "Скрыт");
//        }
    }
}

void Viewer::renameLayer()
{
    QString newName = QInputDialog::getText(this,
                                 QString::fromUtf8("Введите название"),
                                 QString::fromUtf8("Новое название:"),
                                 QLineEdit::Normal);
    if (tree->currentIndex().parent().row() == -1)
    {
        qint64 currentTopLevelIndex = tree->currentIndex().row();
        bool currentVisible = getProject()->layerAt(currentTopLevelIndex).isVisible();
        getProject()->layerAt(currentTopLevelIndex).setName(newName);
        tree->topLevelItem(currentTopLevelIndex)->setText(0, newName);
    }
    else
    {
        qint64 currentTopLevelIndex = tree->currentIndex().parent().row();
        qint64 currentSecondLevelIndex = tree->currentIndex().row();
//        bool currentVisible = project_->layers.at(currentTopLevelIndex)->object.at(currentSecondLevelIndex).isVisible();
//        project_->layers.at(currentTopLevelIndex)->object.at(currentSecondLevelIndex).setVisible(!currentVisible);
    }
}

void Viewer::moreLayer()
{

}
