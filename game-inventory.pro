QT       += core gui sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    src/mainwindow.cpp \
    src/inventoryslot.cpp \
    src/database.cpp \
    src/item.cpp \
    src/itemgenerator.cpp \
    src/gamemenu.cpp \
    src/playingfield.cpp \
    src/inventory.cpp \
    src/main.cpp \

HEADERS += \
    src/mainwindow.h \
    src/inventoryslot.h \
    src/database.h \
    src/item.h \
    src/itemgenerator.h \
    src/gamemenu.h \
    src/playingfield.h \
    src/inventory.h \

FORMS += \
    src/mainwindow.ui

RESOURCES += \
    src/resources.qrc

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
