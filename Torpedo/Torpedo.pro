QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    baseplayer.cpp \
    cpuplayer.cpp \
    main.cpp \
    mainwindow.cpp \
    newgameoptionswidget.cpp \
    shippplacewidget.cpp \
    torpedomodel.cpp

HEADERS += \
    basebuildingblocks.h \
    baseplayer.h \
    cpuplayer.h \
    mainwindow.h \
    newgameoptionswidget.h \
    shippplacewidget.h \
    torpedomodel.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
