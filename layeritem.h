#ifndef LAYERITEM_H
#define LAYERITEM_H

#include <QPixmap>

#include "drawableobject.h"
#include "map.h"

class LayerItem : public DrawableObject
{
public:
    LayerItem(const Point &firstPoint, const QString &name = "Новый объект", const QString &description = "");
    LayerItem(const LayerItem &layerItem) : DrawableObject(layerItem) {};

    virtual qreal perimeter(const Map &map) const = 0;
    virtual qreal square(const Map &map) const = 0;
    virtual QStringList report(const Map &map) const = 0;

    virtual LayerItem* clone() const = 0;

private:
    QVector<Point> points_;
};

#endif // LAYERITEM_H
