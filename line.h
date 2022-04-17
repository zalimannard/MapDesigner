#ifndef LINE_H
#define LINE_H

#include <QtGlobal>
#include "point.h"

enum LineType
{
    SOLID,
    DOTTED
};

class Line
{
public:
    Line(Point start, Point finish);

    Point getStart();
    Point getFinish();
    LineType getLineType() const;
    void setLineType(const LineType &type);
    qint64 getWidth() const;
    void setWidth(const qint64 &width);

private:
    Point start_;
    Point finish_;
    LineType lineType_;
    qint64 width_;
};

#endif // LINE_H
