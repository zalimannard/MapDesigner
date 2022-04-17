#include "polyline.h"

Polyline::Polyline(const Point &start)
{
    points.append(start);
}

qreal Polyline::calculateLength() const
{
    qreal answer = 0;
//    for (auto i = 1; i < points.size(); ++i)
//    {
//        answer += points.at(i - 1).distance(points.at(i));
//    }
    return answer;
}
