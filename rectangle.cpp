#include <QPainter>

#include "rectangle.h"

Rectangle::Rectangle(const Point &firstPoint, const QString &name, const QString &description)
    : LayerItem(firstPoint, name, description)
{

}

qreal Rectangle::perimeter(const Map &map) const
{
    qreal perimeter = 0.0;

    return perimeter;
}

qreal Rectangle::square(const Map &map) const
{
    return 0.0;
}

QStringList Rectangle::report(const Map &map) const
{
    // TODO
    return QStringList("TODO");
}

bool Rectangle::isHealthy() const
{

}

void Rectangle::draw(QPixmap &pixmap) const
{

}

LayerItem* Rectangle::clone() const
{
    return new Rectangle(*this);
}
