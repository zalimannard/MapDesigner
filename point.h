#ifndef POINT_H
#define POINT_H

#include <QtGlobal>

class Point
{
public:
    Point(const qreal &x, const qreal &y);

    qreal getX() const;
    void setX(const qreal &value);
    qreal getY() const;
    void setY(const qreal &value);

private:
    qreal x_;
    qreal y_;
};

#endif // POINT_H
