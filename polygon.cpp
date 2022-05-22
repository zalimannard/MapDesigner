#include <QPainter>
#include <QPainterPath>
#include "polygon.h"

Polygon::Polygon(const Point &firstPoint, const QString &name, const QString &description)
    : LayerItem(firstPoint, name, description)
{

}

qreal Polygon::perimeter(const Map &map) const
{
    qreal answer = 0.0;
    for (auto i = 0; i < points_.size(); ++i)
    {
        answer += map.distance(points_.at(i), points_.at((i + 1) % points_.size()));
    }
    return answer;
}

qreal Polygon::area(const Map &map) const
{
    qreal areaPixel = 0;
    for (auto i = 0; i < points_.size(); ++i)
    {
        Point p1 = points_.at(i);
        Point p2 = points_.at((i + 1) % points_.size());
        areaPixel += p1.getX() * p2.getY() - p2.getX() * p1.getY();
    }
    areaPixel = qAbs(areaPixel);
    qreal meterPerPixelX = map.getMeterPerPixelX();
    qreal meterPerPixelY = map.getMeterPerPixelY();
    return areaPixel * meterPerPixelX * meterPerPixelY;
}

QString Polygon::report(const Map &map) const
{
    QString reportText = LayerItem::report(map);

    return reportText;
}

bool Polygon::isHealthy() const
{
    return (points_.size() > 1);
}

bool Polygon::isMaximumPoint() const
{
    return false;
}

void Polygon::draw(QPixmap &pixmap) const
{
    QPainter *painter = new QPainter(&pixmap);
    QPen pen;
    pen.setColor(getStyle().getLineColor());
    pen.setWidth(getStyle().getLineWidth());
    painter->setPen(pen);
    QBrush brush;
    brush.setColor(getStyle().getLineColor());
    painter->setBrush(brush);
    QPolygon qPolygon;
    for (auto i = 0; i < points_.size(); ++i)
    {
        QPoint qPoint(points_.at(i).getX(), points_.at(i).getY());
        qPolygon.append(qPoint);
    }
    QPainterPath path;
    path.addPolygon(qPolygon);
    painter->fillPath(path, getStyle().getFillColor());
    painter->drawPath(path);
    painter->drawPolygon(qPolygon);
    delete painter;
}

LayerItem* Polygon::clone() const
{
    return new Polygon(*this);
}
