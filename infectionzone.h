#ifndef INFECTIONZONE_H
#define INFECTIONZONE_H

#include <QVector>

#include "layeritem.h"
#include "point.h"

class InfectionZone : public LayerItem
{
public:
    InfectionZone(const Point &firstPoint, const QString &name = "Зона заражения", const QString &description = "");

    qreal perimeter(const Map &map) const override;
    qreal area(const Map &map) const override;
    QString report(const Map &map) const override;
    bool isHealthy() const override;
    bool isMaximumPoint() const override;

    void draw(QPixmap &pixmap) const override;

    LayerItem* clone() const override;
};

#endif // INFECTIONZONE_H
