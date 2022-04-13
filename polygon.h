#ifndef POLYGON_H
#define POLYGON_H

#include <QVector>
#include "point.h"

class Polygon
{
public:
    Polygon(const Point &start);

    QVector<Point> points;

    qreal calculatePerimeter() const;
    qreal calculateArea() const;

private:
};

#endif // POLYGON_H
