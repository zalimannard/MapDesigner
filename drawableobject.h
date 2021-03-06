#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include "imageobject.h"
#include "style.h"

class DrawableObject : public ImageObject
{
public:
    DrawableObject(const Point &keyNode, const QString &name, const QString &description, const bool &visibility = true);

    Point* appendPoint(const Point &point);

    virtual bool isHealthy() const = 0;
    virtual bool isMaximumPoint() const = 0;
    Style getStyle() const;
    void setStyle(const Style &style);

protected:
    QVector<Point> points_;
    Style style_;
};

#endif // DRAWABLEOBJECT_H
