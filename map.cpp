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

bool Map::isBinded()
{
    return true;
}
