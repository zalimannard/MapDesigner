#include "drawableobject.h"

DrawableObject::DrawableObject(const Point &keyNode, const QString &name, const QString &description, const bool &visibility) :
    ImageObject(keyNode, name, description, visibility)
{
    points_.append(keyNode);
}

Point* DrawableObject::appendPoint(const Point &point)
{
    points_.append(point);
    return &points_.last();
}

Style DrawableObject::getStyle() const
{
    return style_;
}

void DrawableObject::setStyle(const Style &style)
{
    style_ = style;
}
