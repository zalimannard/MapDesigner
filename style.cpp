#include "style.h"

Style::Style()
{
    setLineType(LineType::SOLID);
    setLineWidth(5);
    setLineColor(QColor(255, 0, 0));
    setFillColor(QColor(0, 255, 0));
}

LineType Style::getLineType() const
{
    return lineType_;
}

void Style::setLineType(const LineType &type)
{
    lineType_ = type;
}

qint64 Style::getLineWidth() const
{
    return lineWidth_;
}

void Style::setLineWidth(const qint64 &width)
{
    lineWidth_ = width;
}

QColor Style::getLineColor() const
{
    return lineColor_;
}

void Style::setLineColor(const QColor &color)
{
    lineColor_ = color;
}

QColor Style::getFillColor() const
{
    return fillColor_;
}

void Style::setFillColor(const QColor &color)
{
    fillColor_ = color;
}
