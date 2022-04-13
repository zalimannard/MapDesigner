#include <QtMath>

#include "point.h"

Point::Point(const qreal &latitude, const qreal &longitude)
{
    latitude_ = latitude;
    longitude_ = longitude;
}

qreal Point::distance(const Point &other) const
{
    qreal earthRadius = 6371009; // In meters
    qreal phi1 = qDegreesToRadians(this->getLatitude());
    qreal phi2 = qDegreesToRadians(other.getLatitude());
    qreal lambda1 = qDegreesToRadians(this->getLatitude());
    qreal lambda2 = qDegreesToRadians(other.getLongitude());
    return 2 * earthRadius * qAsin(qSqrt(
            (qPow(qSin((phi2 - phi1) / 2), 2)) +
                qCos(phi1) * qCos(phi2) *
                qPow(qSin((lambda2 - lambda1) / 2), 2)));
}

bool Point::isNorth(const Point &other) const
{
    return latitude_ > other.getLatitude();
}

bool Point::isEast(const Point &other) const
{
    return this->longitude_ > other.getLongitude();
}

bool Point::isSouth(const Point &other) const
{
    return latitude_ < other.getLatitude();
}

bool Point::isWest(const Point &other) const
{
    return latitude_ < other.getLatitude();
}

qreal Point::getLatitude() const
{
    return latitude_;
}

void Point::setLatitude(const qreal &value)
{
    latitude_ = value;
}

qreal Point::getLongitude() const
{
    return longitude_;
}

void Point::setLongitude(const qreal &value)
{
    longitude_ = value;
}
