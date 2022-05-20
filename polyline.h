#ifndef POLYLINE_H
#define POLYLINE_H

#include <QVector>

#include "layeritem.h"
#include "point.h"

class Polyline : public LayerItem
{
public:
    Polyline(const Point &firstPoint, const QString &name = "Ломаная", const QString &description = "");

    qreal perimeter(const Map &map) const override;
    qreal square(const Map &map) const override;
    QStringList report(const Map &map) const override;
    bool isHealthy() const override;
    bool isMaximumPoint() const override;

    void draw(QPixmap &pixmap) const override;

    LayerItem* clone() const override;
};

#endif // POLYLINE_H
