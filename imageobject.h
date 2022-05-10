#ifndef IMAGEOBJECT_H
#define IMAGEOBJECT_H

#include <QPixmap>
#include "point.h"

class ImageObject
{
public:
    ImageObject(const Point &keyNode, const QString &name, const QString &description, const bool &visibility = true);

    virtual void draw(QPixmap &pixmap) const = 0;

    Point getPosition() const;
    void setPosition(const Point &point);
    bool isVisible() const;
    void setVisible(const bool &visibility);
    QString getName() const;
    void setName(const QString &name);
    QString getDescription() const;
    void setDescription(const QString &description);

protected:
    Point position_ = Point(0, 0);
    bool visibility_;
    QString name_;
    QString description_;
};

#endif // IMAGEOBJECT_H
