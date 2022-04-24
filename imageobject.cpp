#include "imageobject.h"

ImageObject::ImageObject(const QString &name, const QString &description)
{
    this->setName(name);
    this->setDescription(description);
}

bool ImageObject::isVisible() const
{
    return this->visibility_;
}

void ImageObject::setVisible(const bool &visibility)
{
    this->visibility_ = visibility;
}

QString ImageObject::getName() const
{
    return this->name_;
}

void ImageObject::setName(const QString &name)
{
    this->name_ = name;
}

QString ImageObject::getDescription() const
{
    return this->description_;
}

void ImageObject::setDescription(const QString &description)
{
    this->description_ = description;
}
