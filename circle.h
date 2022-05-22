#ifndef CIRCLE_H
#define CIRCLE_H

#include <QVector>

#include "layeritem.h"
#include "point.h"

class Circle : public LayerItem
{
public:
    Circle(const Point &firstPoint, const QString &name = "Окружность", const QString &description = "");

    qreal radius(const Map &map) const;

    qreal perimeter(const Map &map) const override;
    qreal square(const Map &map) const override;
    QString report(const Map &map) const override;
    bool isHealthy() const override;
    bool isMaximumPoint() const override;

    void draw(QPixmap &pixmap) const override;

    LayerItem* clone() const override;
};

#endif // CIRCLE_H
