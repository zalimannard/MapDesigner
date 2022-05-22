#include <QPainter>
#include <QPainterPath>

#include "rectangle.h"

Rectangle::Rectangle(const Point &firstPoint, const QString &name, const QString &description)
    : LayerItem(firstPoint, name, description)
{

}

qreal Rectangle::perimeter(const Map &map) const
{
    qreal perimeter = 0.0;

    if (isHealthy())
    {
        if (points_.size() == 2)
        {
            perimeter = 2 * map.distance(points_.at(0), points_.at(1));
        }
        else
        {
            perimeter = 2 * (map.distance(points_.at(0), points_.at(1)) +
                    map.distance(points_.at(1), points_.at(2)));
        }
    }

    return perimeter;
}

qreal Rectangle::area(const Map &map) const
{
    qreal triangleAreaPixel = 0;
    for (auto i = 0; i < points_.size(); ++i)
    {
        Point p1 = points_.at(i);
        Point p2 = points_.at((i + 1) % points_.size());
        triangleAreaPixel += p1.getX() * p2.getY() - p2.getX() * p1.getY();
    }
    triangleAreaPixel = qAbs(triangleAreaPixel);
    qreal meterPerPixelX = map.getMeterPerPixelX();
    qreal meterPerPixelY = map.getMeterPerPixelY();
    return 2 * triangleAreaPixel * meterPerPixelX * meterPerPixelY;
}

QString Rectangle::report(const Map &map) const
{
    QString reportText = LayerItem::report(map);

    return reportText;
}

bool Rectangle::isHealthy() const
{
    return ((points_.size() == 2) || (points_.size() == 3));
}

bool Rectangle::isMaximumPoint() const
{
    return (points_.size() == 3);
}

void Rectangle::draw(QPixmap &pixmap) const
{
    if (isHealthy())
    {
        QPainter *painter = new QPainter(&pixmap);
        QPen pen;
        pen.setColor(getStyle().getLineColor());
        pen.setWidth(getStyle().getLineWidth());
        painter->setPen(pen);
        QBrush brush;
        brush.setColor(getStyle().getLineColor());
        painter->setBrush(brush);

        if (points_.size() == 2)
        {
            painter->drawLine(points_.at(0).getX(), points_.at(0).getY(),
                              points_.at(1).getX(), points_.at(1).getY());
        }
        else if (points_.size() == 3)
        {
            QVector<Point> pointsForDraw = points_;
            pointsForDraw.append(Point(points_.at(0).getX() + (points_.at(2).getX() - points_.at(1).getX()),
                                 points_.at(0).getY() + (points_.at(2).getY() - points_.at(1).getY())));
            QPolygon qPolygon;
            for (auto i = 0; i < pointsForDraw.size(); ++i)
            {
                QPoint qPoint(pointsForDraw.at(i).getX(), pointsForDraw.at(i).getY());
                qPolygon.append(qPoint);
            }
            QPainterPath path;
            path.addPolygon(qPolygon);
            painter->fillPath(path, getStyle().getFillColor());
            painter->drawPath(path);
            painter->drawPolygon(qPolygon);
        }
        delete painter;
    }
}

LayerItem* Rectangle::clone() const
{
    return new Rectangle(*this);
}
