#ifndef SUBSTANCE_H
#define SUBSTANCE_H

#include <QString>

class Substance
{
public:
    Substance(QString name);

    QString getName();
    void setName(QString value);

private:
    QString name_;

};

#endif // SUBSTANCE_H
