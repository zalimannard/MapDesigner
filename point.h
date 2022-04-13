#ifndef POINT_H
#define POINT_H

#include <QtGlobal>

class Point
{
public:
    Point(const qreal &latitude, const qreal &longitude);

    qreal distance(const Point &other) const;
    bool isNorth(const Point &other) const;
    bool isEast(const Point &other) const;
    bool isSouth(const Point &other) const;
    bool isWest(const Point &other) const;

    qreal getLatitude() const;
    void setLatitude(const qreal &value);
    qreal getLongitude() const;
    void setLongitude(const qreal &value);

private:
    qreal latitude_;
    qreal longitude_;
};

#endif // POINT_H
