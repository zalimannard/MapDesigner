#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include "imageobject.h"

enum LineType
{
    SOLID,
    DOTTED
};

class DrawableObject : public ImageObject
{
public:
    DrawableObject(const QString &name, const QString &description);
    DrawableObject(const DrawableObject &drawableObject) : ImageObject(drawableObject) {};

    LineType getLineType() const;
    void setLineType(const LineType &type);
    qint64 getLineWidth() const;
    void setLineWidth(const qint64 &width);
    QColor getColor() const;
    void setColor(const QColor &color);

private:

    LineType lineType_;
    qint64 lineWidth_;
    QColor color_;
};

#endif // DRAWABLEOBJECT_H
