#ifndef STYLE_H
#define STYLE_H

#include <QColor>
#include <QFont>

enum LineType
{
    SOLID,
    DOTTED
};

class Style
{
public:
    Style();

    LineType getLineType() const;
    void setLineType(const LineType &type);
    qint64 getLineWidth() const;
    void setLineWidth(const qint64 &width);
    QColor getLineColor() const;
    void setLineColor(const QColor &color);
    QColor getFillColor() const;
    void setFillColor(const QColor &color);

private:
    LineType lineType_;
    qint64 lineWidth_;
    QColor lineColor_;
    QColor fillColor_;
};

#endif // STYLE_H
