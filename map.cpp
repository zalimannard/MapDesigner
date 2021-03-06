#include "map.h"

#include <QtMath>
#include <QPainter>

Map::Map(const QString &pathToImage) :
    ImageObject(Point(0.0, 0.0), "Карта", "")
{
    pathToImage_ = pathToImage;
    wind_ = new Wind(Point(0.0, 0.0));
}

QString Map::getPathToImage() const
{
    return pathToImage_;
}

qreal earthToMinuteEarth(qreal value)
{
    return qFloor(value) * 60 + (value - qFloor(value)) * 100;
}

qreal minuteEarthToEarth(qreal value)
{
    return qFloor(value / 60) + (((value / 60) - qFloor(value / 60)) * 60) / 100;
}

void Map::addPoint(const Point &imagePoint, const Point &earthPoint)
{
    Point earthMinutePoint(earthToMinuteEarth(earthPoint.getX()),
                           earthToMinuteEarth(earthPoint.getY()));

    QPair<Point, Point> newPair(imagePoint, earthMinutePoint);
    if (points_.size() > 1)
    {
        points_.removeFirst();
    }
    points_.append(newPair);
}

Point Map::imagePointToEarthPoint(const Point &imagePoint) const
{
    if (points_.size() == 2)
    {
        qreal longitudeMinutePerPixel = qAbs(points_.at(0).second.getX() - points_.at(1).second.getX()) /
                qAbs(points_.at(0).first.getX() - points_.at(1).first.getX());
        qreal latitudeMinutePerPixel = qAbs(points_.at(0).second.getY() - points_.at(1).second.getY()) /
                qAbs(points_.at(0).first.getY() - points_.at(1).first.getY());

        qreal longitudeMinutePoint = (imagePoint.getX() - points_.at(0).first.getX()) *
                longitudeMinutePerPixel + points_.at(0).second.getX();
        qreal latitudeMinutePoint = - (imagePoint.getY() - points_.at(0).first.getY()) *
                latitudeMinutePerPixel + points_.at(0).second.getY();

        return Point(minuteEarthToEarth(longitudeMinutePoint),
                     minuteEarthToEarth(latitudeMinutePoint));
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

qreal Map::getMeterPerPixelX() const
{
    if (points_.size() > 1)
    {
        Point thirdPoint(points_.at(0).first.getX(), points_.at(1).first.getY());
        return distance(thirdPoint, points_.at(1).first) / qAbs(thirdPoint.getX() - points_.at(1).first.getX());
    }
    return 0;
}

qreal Map::getMeterPerPixelY() const
{
    if (points_.size() > 1)
    {
        Point thirdPoint(points_.at(0).first.getX(), points_.at(1).first.getY());
        return distance(thirdPoint, points_.at(0).first) / qAbs(thirdPoint.getY() - points_.at(0).first.getY());
    }
    return 0;
}

Wind* Map::getWind()
{
    return wind_;
}

void Map::setWind(Wind &value)
{
    wind_ = &value;
}

void Map::draw(QPixmap &pixmap) const
{
    QImage image(getPathToImage());
    pixmap = QPixmap::fromImage(image);
    wind_->draw(pixmap);

    QPainter *painter = new QPainter(&pixmap);
    QPen pen;
    pen.setColor(QColor(24, 26, 30, 240));
    pen.setWidth(36);
    painter->setPen(pen);
    QBrush brush;
    brush.setColor(QColor(24, 26, 30, 240));
    painter->setBrush(brush);
    for (QPair<Point, Point> mapPairPoint : points_)
    {
        painter->drawLine(mapPairPoint.first.getX() + 6,
                          mapPairPoint.first.getY() - 28,
                          mapPairPoint.first.getX() + 32,
                          mapPairPoint.first.getY() - 28);
    }

    pen.setColor(QColor(236, 130, 130, 200));
    pen.setWidth(6);
    painter->setPen(pen);
    brush.setColor(QColor(236, 130, 130, 200));
    painter->setBrush(brush);
    for (QPair<Point, Point> mapPairPoint : points_)
    {
        painter->drawEllipse(mapPairPoint.first.getX() - 3,
                             mapPairPoint.first.getY() - 3, 4, 4);
        painter->drawText(mapPairPoint.first.getX() - 6,
                          mapPairPoint.first.getY() - 30,
                          QString("Д: ") +
                          QString::number(minuteEarthToEarth(mapPairPoint.second.getX())));
        painter->drawText(mapPairPoint.first.getX() - 6,
                          mapPairPoint.first.getY() - 14,
                          QString("Ш: ") +
                          QString::number(minuteEarthToEarth(mapPairPoint.second.getY())));
    }
    delete painter;
}
