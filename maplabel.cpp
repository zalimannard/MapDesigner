#include "maplabel.h"

MapLabel::MapLabel()
{

}

void MapLabel::repaint(Project* project)
{
    QPixmap pixmap;
    project->draw(pixmap);

    setPixmap(pixmap);
    resize(pixmap.width() * getScaleFactor(), pixmap.height() * getScaleFactor());
}

qreal MapLabel::getScaleFactor()
{
    return scaleFactor_;
}

void MapLabel::setScaleFactor(qreal value)
{
    scaleFactor_ = value;
}
