#ifndef PROJECT_H
#define PROJECT_H

#include <QString>

class Project
{
public:
    Project(const QString &name);

    void save(const QString &path) const;
    void open(const QString &path);

    QString getName() const;

private:
    QString name_;

};

#endif // PROJECT_H
