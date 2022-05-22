#ifndef LAYERDOCK_H
#define LAYERDOCK_H

#include <QDockWidget>
#include <QTreeWidget>

#include "project.h"

class LayerDock : public QDockWidget
{
    Q_OBJECT
public:
    LayerDock(Project* project);

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
    void moreLayer(Map &map);
    void moveUp();
    void moveDown();

private:
    Project* project_;
    QTreeWidget *tree_ = new QTreeWidget();

    Project* getProject();
    void setProject(Project* value);

};

#endif // LAYERDOCK_H
