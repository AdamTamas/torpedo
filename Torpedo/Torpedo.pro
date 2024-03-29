QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    modelConnection.cpp \
    modelTorpedo.cpp \
    playerBase.cpp \
    playerCPU.cpp \
    playerOnline.cpp \
    tcpServer.cpp \
    tcpSocket.cpp \
    widgetChat.cpp \
    widgetConnectGameOptions.cpp \
    widgetNewGameOptions.cpp \
    widgetShipPlace.cpp

HEADERS += \
    basebuildingblocks.h \
    mainwindow.h \
    modelConnection.h \
    modelTorpedo.h \
    playerBase.h \
    playerCPU.h \
    playerOnline.h \
    tcpServer.h \
    tcpSocket.h \
    widgetChat.h \
    widgetConnectGameOptions.h \
    widgetNewGameOptions.h \
    widgetShipPlace.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QMAKE_CXXFLAGS += -std=gnu++11
