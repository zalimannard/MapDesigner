#include <QtMath>

#include "map.h"

Map::Map(const QString &pathToImage) : ImageObject("Карта", "")
{
    this->pathToImage_ = pathToImage;
}

QString Map::getPathToImage() const
{
    return this->pathToImage_;
}

qreal earthToMinuteEarth(qreal value)
{
    return qFloor(value) * 60 + (value - qFloor(value)) * 100;
}

qreal minuteEarthToEarth(qreal value)
{
    return qFloor(value / 60) + (value - qFloor(value / 60) * 60) / 100;
}

void Map::addPoint(const Point &imagePoint, const Point &earthPoint)
{
    Point earthMinutePoint(earthToMinuteEarth(earthPoint.getX()),
                           earthToMinuteEarth(earthPoint.getY()));

    QPair<Point, Point> newPair(imagePoint, earthPoint);
    if (this->points_.size() > 1)
    {
        this->points_.removeFirst();
    }
    this->points_.append(newPair);
}

Point Map::imagePointToEarthPoint(const Point &imagePoint) const
{
    if (points_.size() == 2)
    {
        qreal latitudeMinutePerPixel = qAbs(this->points_.at(0).second.getX() - this->points_.at(1).second.getX()) /
                qAbs(this->points_.at(0).first.getX() - this->points_.at(1).first.getX());
        qreal longitudeMinutePerPixel = qAbs(this->points_.at(0).second.getY() - this->points_.at(1).second.getY()) /
                qAbs(this->points_.at(0).first.getY() - this->points_.at(1).first.getY());

        qreal latitudeMinutePoint = (imagePoint.getX() - points_.at(0).first.getX()) *
                latitudeMinutePerPixel + points_.at(0).second.getX();
        qreal longitudeMinutePoint = (imagePoint.getY() - points_.at(0).first.getY()) *
                longitudeMinutePerPixel + points_.at(0).second.getY();

        return Point(minuteEarthToEarth(latitudeMinutePoint),
                     minuteEarthToEarth(longitudeMinutePoint));
    }
    else
    {
        return Point(0, 0);
    }
}

qreal Map::distance(const Point &imagePointFirst, const Point &imagePointSecond) const
{
    Point firstEarthPoint = imagePointToEarthPoint(imagePointFirst);
    Point secondEarthPoint = imagePointToEarthPoint(imagePointSecond);

    qreal earthRadius = 6371009; // In meters
    qreal phi1 = qDegreesToRadians(firstEarthPoint.getX());
    qreal phi2 = qDegreesToRadians(secondEarthPoint.getX());
    qreal lambda1 = qDegreesToRadians(firstEarthPoint.getY());
    qreal lambda2 = qDegreesToRadians(secondEarthPoint.getY());
    return 2 * earthRadius * qAsin(qSqrt(
            (qPow(qSin((phi2 - phi1) / 2), 2)) +
                qCos(phi1) * qCos(phi2) *
                qPow(qSin((lambda2 - lambda1) / 2), 2)));
}

void Map::draw(QPixmap &pixmap) const
{
    QImage image(this->getPathToImage());
    pixmap = QPixmap::fromImage(image);
}
