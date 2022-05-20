#include "text.h"

#include <QPainter>

Text::Text(const Point &firstPoint, const QString &name, const QString &description)
    : LayerItem(firstPoint, name, description)
{

}

qreal Text::perimeter(const Map &map) const
{
    return 0.0;
}

qreal Text::square(const Map &map) const
{
    return 0.0;
}

QStringList Text::report(const Map &map) const
{
    QStringList reportText = LayerItem::report(map);

    return reportText;
}

bool Text::isHealthy() const
{
    return (points_.size() == 1);
}

bool Text::isMaximumPoint() const
{
    return (points_.size() == 1);
}

void Text::draw(QPixmap &pixmap) const
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
        const QString str = getName();
        painter->drawText(points_.at(0).getX(), points_.at(0).getY(), str);

        delete painter;
    }
}

LayerItem* Text::clone() const
{
    return new Text(*this);
}
