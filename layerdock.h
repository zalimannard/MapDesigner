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
    Project* project_;
    QTreeWidget *tree_ = new QTreeWidget();

    void updateContent();

};

#endif // LAYERDOCK_H