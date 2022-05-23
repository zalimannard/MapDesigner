#ifndef INFECTIONZONE_H
#define INFECTIONZONE_H

#include <QVector>

#include "layeritem.h"
#include "point.h"
#include "substance.h"

class InfectionZone : public LayerItem
{
public:
    InfectionZone(const Point &firstPoint, Map* map, qreal time = 1,
                  qreal weight = 1, const QString &name = "Зона заражения",
                  const QString &description = "");

    qreal perimeter(const Map &map) const override;
    qreal area(const Map &map) const override;
    QString report(const Map &map) const override;
    bool isHealthy() const override;
    bool isMaximumPoint() const override;
    qreal getDepthInfection() const;

    void draw(QPixmap &pixmap) const override;

    LayerItem* clone() const override;

private:
    qreal depthInfection_ = 0.0;
    Map* map_ = nullptr;
    qreal time_;
    qreal weight_;

    Map* getMap() const;
    void setMap(Map* value);
    qreal getTime() const;
    void setTime(qreal value);
    qreal getWeight() const;
    void setWeight(qreal value);
};

#endif // INFECTIONZONE_H
