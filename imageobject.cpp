#include <QDebug>

#include "imageobject.h"

ImageObject::ImageObject(const Point &keyNode, const QString &name, const QString &description, const bool &visibility)
{
    setPosition(keyNode);
    setVisible(visibility);
    setName(name);
    setDescription(description);
}

Point ImageObject::getPosition() const
{
    return position_;
}

void ImageObject::setPosition(const Point &point)
{
    position_ = point;
}

bool ImageObject::isVisible() const
{
    return visibility_;
}

void ImageObject::setVisible(const bool &visibility)
{
    visibility_ = visibility;
}

QString ImageObject::getName() const
{
    return name_;
}

void ImageObject::setName(const QString &name)
{
    name_ = name;
}

QString ImageObject::getDescription() const
{
    return description_;
}

void ImageObject::setDescription(const QString &description)
{
    description_ = description;
}
