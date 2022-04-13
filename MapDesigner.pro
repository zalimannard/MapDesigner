QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    displayedobject.cpp \
    layer.cpp \
    line.cpp \
    main.cpp \
    map.cpp \
    point.cpp \
    polygon.cpp \
    polyline.cpp \
    text.cpp \
    viewer.cpp

HEADERS += \
    displayedobject.h \
    layer.h \
    line.h \
    map.h \
    point.h \
    polygon.h \
    polyline.h \
    text.h \
    viewer.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
