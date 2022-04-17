#include "map.h"

Map::Map(QString pathToImage)
{
    pathToImage_ = pathToImage;
}

QString Map::getPathToImage()
{
    return pathToImage_;
}

void Map::setMainPoint(Point imagePoint, Point mapPoint)
{

}

//qreal Point::distance(const Point &other) const
//{
//    qreal earthRadius = 6371009; // In meters
//    qreal phi1 = qDegreesToRadians(this->getLatitude());
//    qreal phi2 = qDegreesToRadians(other.getLatitude());
//    qreal lambda1 = qDegreesToRadians(this->getLatitude());
//    qreal lambda2 = qDegreesToRadians(other.getLongitude());
//    return 2 * earthRadius * qAsin(qSqrt(
//            (qPow(qSin((phi2 - phi1) / 2), 2)) +
//                qCos(phi1) * qCos(phi2) *
//                qPow(qSin((lambda2 - lambda1) / 2), 2)));
//}
