#ifndef WIND_H
#define WIND_H

#include "drawableobject.h"

class Wind : public DrawableObject
{
public:
    Wind(const Point &keyNode, const QString &name = "Ветер",
         const QString &description = "Дует", const bool &visibility = true);

    void draw(QPixmap &pixmap) const override;

    bool isHealthy() const override;
    bool isMaximumPoint() const override;
    bool isApplied() const;
    void setApplied(bool value);
    qreal getDegreesDuration() const;

private:
    bool applied_ = true;
};

#endif // WIND_H
