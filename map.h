#ifndef MAP_H
#define MAP_H

#include <QString>
#include <QVector>
#include <QPair>
#include "point.h"

#include "displayedobject.h"

class Map : public DisplayedObject
{
public:
    Map(QString pathToImage);
    QString getPathToImage();
    void setMainPoint(Point imagePoint, Point mapPoint);

private:
    Point *mainPointImage_;
    Point *mainPointMap_;
    qreal latitudePerPixel_ = 0.0;
    qreal longitudePerPixel_ = 0.0;
    QString pathToImage_;
};

#endif // MAP_H
