#include "drawableobject.h"

DrawableObject::DrawableObject(const QString &name, const QString &description) : ImageObject(name, description)
{

}

LineType DrawableObject::getLineType() const
{
    return this->lineType_;
}

void DrawableObject::setLineType(const LineType &type)
{
    this->lineType_ = type;
}

qint64 DrawableObject::getLineWidth() const
{
    return this->lineWidth_;
}

void DrawableObject::setLineWidth(const qint64 &width)
{
    this->lineWidth_ = width;
}

QColor DrawableObject::getColor() const
{
    return this->color_;
}

void DrawableObject::setColor(const QColor &color)
{
    this->color_ = color;
}
