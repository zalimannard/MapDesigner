#ifndef MAPLABEL_H
#define MAPLABEL_H

#include <QLabel>

#include "project.h"

class MapLabel : public QLabel
{
    Q_OBJECT
public:
    MapLabel();

    void repaint(Project* project);

    qreal getScaleFactor();
    void setScaleFactor(qreal value);

private:
    qreal scaleFactor_ = 1.0;

};

#endif // MAPLABEL_H
