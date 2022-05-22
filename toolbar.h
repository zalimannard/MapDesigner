#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>

#include "project.h"

enum CursorType
{
    DEFAULT,
    MOVE_MAP,
    MOVE_OBJECT,
    POLYLINE,
    CIRCLE,
    RECTANGLE,
    POLYGON,
    TEXT,
    INFECTION,
    BINDING,
    EARTH_POINT,
    WIND
};

class ToolBar : public QToolBar
{
    Q_OBJECT
public:
    ToolBar(Project* project);

    void update();

    CursorType getCursorType();

    QAction *defaultCursorAct;
    QAction *moveMapCursorAct;
    QAction *moveObjectCursorAct;
    QAction *polylineCursorAct;
    QAction *circleCursorAct;
    QAction *rectangleCursorAct;
    QAction *polygonCursorAct;
    QAction *textCursorAct;
    QAction *infectionCursorAct;
    QAction *bindingCursorAct;
    QAction *earthPointAct;
    QAction *styleChooserAct;
    QAction *windDirectionAct;

    void setCursorType(CursorType value);

private slots:
    void setCursorDefault();
    void setCursorMoveMap();
    void setCursorMoveObject();
    void setCursorPolyline();
    void setCursorCircle();
    void setCursorRectangle();
    void setCursorPolygon();
    void setCursorText();
    void setCursorInfection();
    void setCursorBinding();
    void setCursorEarthPoint();
    void setCursorStyleChooser();
    void setCursorWindDirection();

private:
    Project* project_;
    CursorType cursorType_;

    bool isProjectExist();
    Project* getProject();
    void setProject(Project* value);
};

#endif // TOOLBAR_H
