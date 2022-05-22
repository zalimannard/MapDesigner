#ifndef LAYERITEM_H
#define LAYERITEM_H

#include <QPixmap>

#include "drawableobject.h"
#include "map.h"

class LayerItem : public DrawableObject
{
public:
    LayerItem(const Point &keyNode, const QString &name = "Новый объект", const QString &description = "", const bool &visibility = true);

    virtual qreal perimeter(const Map &map) const = 0;
    virtual qreal square(const Map &map) const = 0;
    virtual QString report(const Map &map) const;
    virtual bool isHealthy() const = 0;
    virtual bool isMaximumPoint() const = 0;

    virtual LayerItem* clone() const = 0;
};

#endif // LAYERITEM_H
