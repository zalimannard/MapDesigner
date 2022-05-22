#include "toolbar.h"

#include "stylechooser.h"

ToolBar::ToolBar(Project* project)
{
    setProject(project);
    setCursorType(CursorType::DEFAULT);

    defaultCursorAct = new QAction(QIcon::fromTheme("pointer"), tr("Обычный курсор"), this);
    connect(defaultCursorAct, SIGNAL(triggered()), this, SLOT(setCursorDefault()));

    moveMapCursorAct = new QAction(QIcon::fromTheme("transform-browse"), tr("Перемещение по карте"), this);
    connect(moveMapCursorAct, SIGNAL(triggered()), this, SLOT(setCursorMoveMap()));

    moveObjectCursorAct = new QAction(QIcon::fromTheme("object-move"), tr("Перемещение объекта"), this);
    connect(moveObjectCursorAct, SIGNAL(triggered()), this, SLOT(setCursorMoveObject()));

    polylineCursorAct = new QAction(QIcon::fromTheme("path-mode-polyline"), tr("Рисовать ломаную"), this);
    connect(polylineCursorAct, SIGNAL(triggered()), this, SLOT(setCursorPolyline()));

    circleCursorAct = new QAction(QIcon::fromTheme("draw-circle"), tr("Рисовать окружность"), this);
    connect(circleCursorAct, SIGNAL(triggered()), this, SLOT(setCursorCircle()));

    rectangleCursorAct = new QAction(QIcon::fromTheme("draw-rectangle"), tr("Рисовать прямоугольник"), this);
    connect(rectangleCursorAct, SIGNAL(triggered()), this, SLOT(setCursorRectangle()));

    polygonCursorAct = new QAction(QIcon::fromTheme("draw-polygon"), tr("Рисовать полигон"), this);
    connect(polygonCursorAct, SIGNAL(triggered()), this, SLOT(setCursorPolygon()));

    textCursorAct = new QAction(QIcon::fromTheme("edit-select-text"), tr("Добавить текст"), this);
    connect(textCursorAct, SIGNAL(triggered()), this, SLOT(setCursorText()));

    infectionCursorAct = new QAction(QIcon::fromTheme("im-gadugadu"), tr("Добавить зону заражения"), this);
    connect(infectionCursorAct, SIGNAL(triggered()), this, SLOT(setCursorInfection()));

    bindingCursorAct = new QAction(QIcon::fromTheme("office-chart-scatter"), tr("Привязать карту"), this);
    connect(bindingCursorAct, SIGNAL(triggered()), this, SLOT(setCursorBinding()));

    earthPointAct = new QAction(QIcon::fromTheme("edit-paste-in-place"), tr("Узнать координату"), this);
    connect(earthPointAct, SIGNAL(triggered()), this, SLOT(setCursorEarthPoint()));

    styleChooserAct = new QAction(QIcon::fromTheme("color-management"), tr("Редактировать текущий стиль"), this);
    connect(styleChooserAct, SIGNAL(triggered()), this, SLOT(setCursorStyleChooser()));

    setMovable(true);
    setEnabled(true);
    addAction(defaultCursorAct);
    addAction(moveMapCursorAct);
    addAction(moveObjectCursorAct);
    addAction(polylineCursorAct);
    addAction(circleCursorAct);
    addAction(rectangleCursorAct);
    addAction(polygonCursorAct);
    addAction(textCursorAct);
    addAction(infectionCursorAct);
    addAction(bindingCursorAct);
    addAction(earthPointAct);
    addAction(styleChooserAct);
}

bool ToolBar::isProjectExist()
{
    return getProject() == nullptr;
}

void ToolBar::update()
{
    if (isProjectExist())
    {
        if (project_->isMapExist())
        {
            defaultCursorAct->setVisible(true);
            moveMapCursorAct->setVisible(true);
            moveObjectCursorAct->setVisible(true);
            polylineCursorAct->setVisible(true);
            circleCursorAct->setVisible(true);
            rectangleCursorAct->setVisible(true);
            polygonCursorAct->setVisible(true);
            textCursorAct->setVisible(true);
            infectionCursorAct->setVisible(true);
            bindingCursorAct->setVisible(true);
            earthPointAct->setVisible(true);
        }
        else
        {
            defaultCursorAct->setVisible(true);
            moveMapCursorAct->setVisible(false);
            moveObjectCursorAct->setVisible(false);
            polylineCursorAct->setVisible(false);
            circleCursorAct->setVisible(false);
            rectangleCursorAct->setVisible(false);
            polygonCursorAct->setVisible(false);
            textCursorAct->setVisible(false);
            infectionCursorAct->setVisible(false);
            bindingCursorAct->setVisible(false);
            earthPointAct->setVisible(false);
        }
    }
    else
    {
        defaultCursorAct->setVisible(true);
        moveMapCursorAct->setVisible(false);
        moveObjectCursorAct->setVisible(false);
        polylineCursorAct->setVisible(false);
        circleCursorAct->setVisible(false);
        rectangleCursorAct->setVisible(false);
        polygonCursorAct->setVisible(false);
        textCursorAct->setVisible(false);
        infectionCursorAct->setVisible(false);
        bindingCursorAct->setVisible(false);
        earthPointAct->setVisible(false);
    }
}

CursorType ToolBar::getCursorType()
{
    return cursorType_;
}

void ToolBar::setCursorType(CursorType value)
{
    cursorType_ = value;
}

void ToolBar::setCursorDefault()
{
    setCursorType(CursorType::DEFAULT);
}

void ToolBar::setCursorMoveMap()
{
    setCursorType(CursorType::MOVE_MAP);
}

void ToolBar::setCursorMoveObject()
{
    setCursorType(CursorType::MOVE_OBJECT);
}

void ToolBar::setCursorPolyline()
{
    setCursorType(CursorType::POLYLINE);
}

void ToolBar::setCursorCircle()
{
    setCursorType(CursorType::CIRCLE);
}

void ToolBar::setCursorRectangle()
{
    setCursorType(CursorType::RECTANGLE);
}

void ToolBar::setCursorPolygon()
{
    setCursorType(CursorType::POLYGON);
}

void ToolBar::setCursorText()
{
    setCursorType(CursorType::TEXT);
}

void ToolBar::setCursorInfection()
{
    setCursorType(CursorType::INFECTION);
}

void ToolBar::setCursorBinding()
{
    setCursorType(CursorType::BINDING);
}

void ToolBar::setCursorEarthPoint()
{
    setCursorType(CursorType::EARTH_POINT);
}

void ToolBar::setCursorStyleChooser()
{
    StyleChooser* styleChooser = new StyleChooser(getProject()->getStyle());
}

Project* ToolBar::getProject()
{
    return project_;
}

void ToolBar::setProject(Project* value)
{
    project_ = value;
}
