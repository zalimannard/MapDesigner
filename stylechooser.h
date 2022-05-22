#ifndef STYLECHOOSER_H
#define STYLECHOOSER_H

#include <QWidget>

#include "project.h"
#include "style.h"

class StyleChooser : public QWidget
{
    Q_OBJECT
public:
    StyleChooser(Style* style, QWidget *parent = nullptr);

    Style* getStyle();

private:
    Style* style_;

    void setStyle(Style* value);
};

#endif // STYLECHOOSER_H
