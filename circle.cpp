#include <QPainter>
#include <QtMath>

#include "circle.h"

Circle::Circle(const Point &firstPoint, const QString &name, const QString &description)
    : LayerItem(firstPoint, name, description)
{

}

qreal Circle::radius(const Map &map) const
{
    Point firstYSecondX(points_.at(0).getY(), points_.at(1).getX());
    Point firstXSecondY(points_.at(0).getX(), points_.at(1).getY());
    qreal distanceX = map.distance(points_.at(0), firstYSecondX);
    qreal distanceY = map.distance(points_.at(0), firstXSecondY);
    return qSqrt(qPow(distanceX, 2) + qPow(distanceY, 2));
}

qreal Circle::perimeter(const Map &map) const
{
    if (isHealthy())
    {
        return radius(map) * M_PI * 2;
    }
    else
    {
        return 0.0;
    }
}

qreal Circle::square(const Map &map) const
{
    if (isHealthy())
    {
        return qPow(radius(map), 2) * M_PI;
    }
    else
    {
        return 0.0;
    }
}

QStringList Circle::report(const Map &map) const
{
    QStringList reportText = LayerItem::report(map);
    reportText.append("Радиус: " + QString::number(radius(map)));

    return reportText;
}

bool Circle::isHealthy() const
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

