#ifndef MAP_H
#define MAP_H

#include <QString>
#include <QVector>
#include <QPair>

#include "displayedobject.h"

class Map : public DisplayedObject
{
public:
    Map(QString pathToImage);
    QString getPathToImage();
    void addPoint(double pixel, double coordinateX, double coordinateY);

    void removePoint(qint64 index);

private:
    QString pathToImage;
    QVector<QPair<double, double> > pixelAndCoordinates;
};

#endif // MAP_H
