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
        answer = map.distance(points_.at(i), points_.at((i + 1) % points_.size()));
    }
    return answer;
}

qreal Polygon::square(const Map &map) const
{
    // TODO
    return 0;
}

QStringList Polygon::report(const Map &map) const
{
    QStringList reportText = LayerItem::report(map);

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


//qreal Polygon::calculatePerimeter() const
//{
//    qint64 answer = 0;
////    for (auto i = 1; i < points.size(); ++i)
////    {
////        answer += points.at(i - 1).distance(points.at(i));
////    }
//    return answer;
//}

//qreal Polygon::calculateArea() const
//{
//    qreal earthArea = 510072000000000;
//    qreal firstSum = 0;
//    qreal secondSum = 0;
////    for (auto i = 0; i < points.size(); ++i)
////    {
////        firstSum += points.at(i).getLatitude() * points.at((i + 1) % points.size()).getLongitude();
////        secondSum += points.at(i).getLongitude() * points.at((i + 1) % points.size()).getLatitude();
////    }
//    qreal answer = earthArea / 41253 * (firstSum - secondSum);
//    return answer;
//}
