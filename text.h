#ifndef TEXT_H
#define TEXT_H

#include <QFont>
#include <QString>

#include "layeritem.h"

class Text : public LayerItem
{
public:
    Text(const Point &firstPoint, const QString &name = "Текст", const QString &description = "");

    qreal perimeter(const Map &map) const override;
    qreal square(const Map &map) const override;
    QStringList report(const Map &map) const override;
    bool isHealthy() const override;
    bool isMaximumPoint() const override;

    void draw(QPixmap &pixmap) const override;

    LayerItem* clone() const override;
};



#endif
