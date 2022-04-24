#include "layeritem.h"

LayerItem::LayerItem(const Point &firstPoint, const QString &name, const QString &description) : DrawableObject (name, description)
{
    this->points_.append(firstPoint);
}
