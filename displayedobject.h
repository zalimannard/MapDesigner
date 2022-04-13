#ifndef DISPLAYEDOBJECT_H
#define DISPLAYEDOBJECT_H

#include <QString>

class DisplayedObject
{
public:
    DisplayedObject();

    bool isVisible() const;
    void setVisible(const bool &condition);
    QString getName() const;
    void setName(const QString &name);

private:
    bool visibleCondition_;
    QString name_;
};

#endif // DISPLAYEDOBJECT_H
