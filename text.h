#ifndef TEXT_H
#define TEXT_H

#include <QFont>
#include <QString>

class Text
{
public:
    Text();

    QFont font;
    QString content_;

    QString getColor() const;
    void setColor(QString newColor);

private:
    QString color_;
};

#endif // TEXT_H
