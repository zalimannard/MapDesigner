#include "substance.h"

Substance::Substance(QString name)
{
    setName(name);
}

QString Substance::getName()
{
    return name_;
}

void Substance::setName(QString value)
{
    name_ = value;
}
