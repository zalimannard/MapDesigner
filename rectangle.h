#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QVector>

#include "layeritem.h"
#include "point.h"

class Rectangle : public LayerItem
{
public:
    Rectangle(const Point &firstPoint, const QString &name = "Параллелограмм", const QString &description = "");

    qreal perimeter(const Map &map) const override;
    qreal area(const Map &map) const override;
    QString report(const Map &map) const override;
    bool isHealthy() const override;
    bool isMaximumPoint() const override;

    void draw(QPixmap &pixmap) const override;

    LayerItem* clone() const override;
};

#endif // RECTANGLE_H
