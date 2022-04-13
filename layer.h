#ifndef LAYER_H
#define LAYER_H

#include <QVector>
#include "displayedobject.h"

class Layer : public DisplayedObject
{
public:
    Layer();

    QVector<DisplayedObject> object;
};

#endif // LAYER_H
