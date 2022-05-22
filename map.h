#ifndef MAP_H
#define MAP_H

#include <QQueue>
#include <QPair>

#include "imageobject.h"
#include "point.h"
#include "wind.h"

class Map : public ImageObject
{
public:
    Map(const QString &pathToImage);

    QString getPathToImage() const;
    void addPoint(const Point &imagePoint, const Point &earthPoint);
    Point imagePointToEarthPoint(const Point &imagePoint) const;
    qreal distance(const Point &first, const Point &second) const;
    qreal getMeterPerPixelX() const;
    qreal getMeterPerPixelY() const;
    Wind* getWind();
    void setWind(Wind &value);

    void draw(QPixmap &pixmap) const override;

private:
    QQueue<QPair<Point, Point> > points_; // .first - imagePoint, .second - earthPoint
    QString pathToImage_;
    Wind* wind_ = nullptr;
};

#endif // MAP_H
