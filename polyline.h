#ifndef POLYLINE_H
#define POLYLINE_H

#include <QVector>
#include "point.h"

class Polyline
{
public:
    Polyline(const Point &start);

    QVector<Point> points;

    qreal calculateLength() const;
};

#endif // POLYLINE_H
