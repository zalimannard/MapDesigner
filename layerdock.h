#ifndef LAYERDOCK_H
#define LAYERDOCK_H

#include <QDockWidget>
#include <QTreeWidget>

#include "maplabel.h"
#include "project.h"

class LayerDock : public QDockWidget
{
    Q_OBJECT
public:
    LayerDock(QSqlDatabase* db, Project* project, MapLabel* imageLabel);

    void update();

    bool isProjectExist();
    bool isAnySelected();
    bool isLayerSelected();
    bool isObjectSelected();
    qint64 getCurrentTopLevelIndex();
    qint64 getCurrentSecondLevelIndex();

public slots:
    void addLayer();
    void deleteLayer();
    void toggleVisibleLayer();
    void renameLayer();
    void moreLayer();
    void moveUp();
    void moveDown();

private:
    QSqlDatabase db_;
    Project* project_;
    MapLabel* imageLabel_;
    QTreeWidget *tree_ = new QTreeWidget();

    Project* getProject();
    void setProject(Project* value);
    MapLabel* getImageLabel();
    void setImageLabel(MapLabel* value);
    QSqlQuery *query;

};

#endif // LAYERDOCK_H
