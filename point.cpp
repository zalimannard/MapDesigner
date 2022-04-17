#include <QtMath>

#include "point.h"

Point::Point(const qreal &x, const qreal &y)
{
    setX(x);
    setY(y);
}

qreal Point::getX() const
{
    return x_;
}

void Point::setX(const qreal &value)
{
    x_ = value;
}
qreal Point::getY() const
{
    return y_;
}

void Point::setY(const qreal &value)
{
    y_ = value;
}

