#include <QPainter>

#include "polyline.h"

Polyline::Polyline(const Point &firstPoint, const QString &name, const QString &description)
    : LayerItem(firstPoint, name, description)
{

}

qreal Polyline::perimeter(const Map &map) const
{
    qreal perimeter = 0.0;
    for (auto i = 0; i < points_.size() - 1; ++i)
    {
        perimeter += map.distance(points_.at(i), points_.at(i + 1));
    }
    return perimeter;
}

qreal Polyline::square(const Map &map) const
{
    return 0.0;
}

QStringList Polyline::report(const Map &map) const
{
    QStringList reportText = LayerItem::report(map);

    return reportText;
}

bool Polyline::isHealthy() const
{
    return (points_.size() > 1);
}

bool Polyline::isMaximumPoint() const
{
    return false;
}

void Polyline::draw(QPixmap &pixmap) const
{
    QPainter *painter = new QPainter(&pixmap);
    QPen pen;
    pen.setColor(getStyle().getLineColor());
    pen.setWidth(getStyle().getLineWidth());
    if (getStyle().getLineType() == LineType::SOLID)
    {
        pen.setStyle(Qt::PenStyle::SolidLine);
    }
    else if (getStyle().getLineType() == LineType::DOTTED)
    {
        pen.setStyle(Qt::PenStyle::DotLine);
    }
    painter->setPen(pen);
    for (auto i = 0; i < points_.size() - 1; ++i)
    {
        painter->drawLine(points_.at(i).getX(), points_.at(i).getY(),
                          points_.at(i + 1).getX(), points_.at(i + 1).getY());
    }
    delete painter;
}

LayerItem* Polyline::clone() const
{
    return new Polyline(*this);
}
