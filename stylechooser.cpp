#include "stylechooser.h"

StyleChooser::StyleChooser(Style* style, QWidget *parent)
    : QWidget{parent}
{
    style_ = style;
    show();
}

Style* StyleChooser::getStyle()
{
    return style_;
}
