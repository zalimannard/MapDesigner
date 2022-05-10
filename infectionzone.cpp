#include <QPainter>

#include "infectionzone.h"

InfectionZone::InfectionZone(const Point &firstPoint, const QString &name, const QString &description)
    : LayerItem(firstPoint, name, description)
{

}

qreal InfectionZone::perimeter(const Map &map) const
{
    qreal perimeter = 0.0;

    return perimeter;
}

qreal InfectionZone::square(const Map &map) const
{
    return 0.0;
}

QStringList InfectionZone::report(const Map &map) const
{
    // TODO
    return QStringList("TODO");
}

bool InfectionZone::isHealthy() const
{

}

void InfectionZone::draw(QPixmap &pixmap) const
{

}

LayerItem* InfectionZone::clone() const
{
    return new InfectionZone(*this);
}
