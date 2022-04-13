#include "displayedobject.h"

DisplayedObject::DisplayedObject()
{
    visibleCondition_ = true;
}

bool DisplayedObject::isVisible() const
{
    return visibleCondition_;
}

void DisplayedObject::setVisible(const bool &condition)
{
    visibleCondition_ = condition;
}

QString DisplayedObject::getName() const
{
    return name_;
}

void DisplayedObject::setName(const QString &name)
{
    name_ = name;
}
