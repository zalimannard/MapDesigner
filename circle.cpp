#include <QPainter>
#include <QtMath>

#include "circle.h"

Circle::Circle(const Point &firstPoint, const QString &name, const QString &description)
    : LayerItem(firstPoint, name, description)
{

}

qreal Circle::radius(const Map &map) const
{
    Point thirdPoint(points_.at(0).getX(), points_.at(1).getY());
    qreal distanceX = map.distance(points_.at(1), thirdPoint);
    qreal distanceY = map.distance(points_.at(0), thirdPoint);
    return (distanceX + distanceY) / 2;
}

qreal Circle::perimeter(const Map &map) const
{
    Point thirdPoint(points_.at(0).getX(), points_.at(1).getY());
    qreal distanceX = map.distance(points_.at(1), thirdPoint);
    qreal distanceY = map.distance(points_.at(0), thirdPoint);

    return 2 * M_PI *
            qSqrt(((qPow(distanceX / 2, 2)) + qPow(distanceY / 2, 2)) / 2);
}

qreal Circle::area(const Map &map) const
{
    Point thirdPoint(points_.at(0).getX(), points_.at(1).getY());
    qreal distanceX = map.distance(points_.at(1), thirdPoint);
    qreal distanceY = map.distance(points_.at(0), thirdPoint);

    return M_PI * distanceX / 2 * distanceY / 2;
}

QString Circle::report(const Map &map) const
{
    QString reportText = LayerItem::report(map);
    reportText.append("\nСредний радиус: " + QString::number(round(radius(map) / 10) / 100) + "км");

    return reportText;
}

bool Circle::isHealthy() const
{
    return (points_.size() == 2);
}

bool Circle::isMaximumPoint() const
{
    return (points_.size() == 2);
}

void Circle::draw(QPixmap &pixmap) const
{
    if (isHealthy())
    {
        QPainter *painter = new QPainter(&pixmap);
        QPen pen;
        pen.setColor(getStyle().getLineColor());
        pen.setWidth(getStyle().getLineWidth());
        painter->setPen(pen);
        QBrush brush;
        brush.setColor(getStyle().getLineColor());
        painter->setBrush(brush);
        painter->drawEllipse(points_.at(0).getX(), points_.at(0).getY(),
                             points_.at(1).getX() - points_.at(0).getX(),
                             points_.at(1).getY() - points_.at(0).getY());
        delete painter;
    }
}

LayerItem* Circle::clone() const
{
    return new Circle(*this);
}

