#ifndef POLYGON_H
#define POLYGON_H

#include <QVector>

#include "layeritem.h"
#include "point.h"

class Polygon : public LayerItem
{
public:
    Polygon(const Point &firstPoint, const QString &name = "Многоугольник", const QString &description = "");

    qreal perimeter(const Map &map) const override;
    qreal square(const Map &map) const override;
    QStringList report(const Map &map) const override;
    bool isHealthy() const override;

    void draw(QPixmap &pixmap) const override;

    LayerItem* clone() const override;
};

#endif // POLYGON_H
