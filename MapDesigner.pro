QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    circle.cpp \
    database.cpp \
    drawableobject.cpp \
    imageobject.cpp \
    infectionzone.cpp \
    layer.cpp \
    layerdock.cpp \
    layeritem.cpp \
    main.cpp \
    map.cpp \
    maplabel.cpp \
    myscrollarea.cpp \
    point.cpp \
    polygon.cpp \
    polyline.cpp \
    project.cpp \
    rectangle.cpp \
    style.cpp \
    stylechooser.cpp \
    substance.cpp \
    text.cpp \
    toolbar.cpp \
    viewer.cpp \
    wind.cpp

HEADERS += \
    circle.h \
    database.h \
    drawableobject.h \
    imageobject.h \
    infectionzone.h \
    layer.h \
    layerdock.h \
    layeritem.h \
    map.h \
    maplabel.h \
    myscrollarea.h \
    point.h \
    polygon.h \
    polyline.h \
    project.h \
    rectangle.h \
    style.h \
    stylechooser.h \
    substance.h \
    text.h \
    toolbar.h \
    viewer.h \
    wind.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    database.ui
