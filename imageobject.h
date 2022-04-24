#ifndef IMAGEOBJECT_H
#define IMAGEOBJECT_H

#include <QPixmap>

class ImageObject
{
public:
    ImageObject(const QString &name, const QString &description);
    ImageObject(const ImageObject &imageObject) {};

    virtual void draw(QPixmap &pixmap) const = 0;

    bool isVisible() const;
    void setVisible(const bool &visibility);
    QString getName() const;
    void setName(const QString &name);
    QString getDescription() const;
    void setDescription(const QString &description);

private:
    bool visibility_;
    QString name_;
    QString description_;
};

#endif // IMAGEOBJECT_H
