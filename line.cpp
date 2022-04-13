#include "line.h"

Line::Line(Point start, Point finish) : start_(start), finish_(finish)
{
    lineType_ = SOLID;
    width_ = 2;
}

Point Line::getStart()
{
    return start_;
}

Point Line::getFinish()
{
    return finish_;
}

LineType Line::getLineType() const
{
    return lineType_;
}

void Line::setLineType(const LineType &type)
{
    lineType_ = type;
}

qint64 Line::getWidth() const
{
    return width_;
}

void Line::setWidth(const qint64 &width)
{
    width_ = width;
}
