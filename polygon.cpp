#include "polygon.h"

Polygon::Polygon(const Point &start)
{
    points.append(start);
}

qreal Polygon::calculatePerimeter() const
{
    qint64 answer = 0;
//    for (auto i = 1; i < points.size(); ++i)
//    {
//        answer += points.at(i - 1).distance(points.at(i));
//    }
    return answer;
}

qreal Polygon::calculateArea() const
{
    qreal earthArea = 510072000000000;
    qreal firstSum = 0;
    qreal secondSum = 0;
//    for (auto i = 0; i < points.size(); ++i)
//    {
//        firstSum += points.at(i).getLatitude() * points.at((i + 1) % points.size()).getLongitude();
//        secondSum += points.at(i).getLongitude() * points.at((i + 1) % points.size()).getLatitude();
//    }
    qreal answer = earthArea / 41253 * (firstSum - secondSum);
    return answer;
}
