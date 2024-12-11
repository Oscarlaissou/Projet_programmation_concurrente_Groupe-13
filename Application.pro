QT       += core gui
QT       += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
RESOURCES += \
parquet.qrc


SOURCES += \
    Staff.cpp \
    StaffController.cpp \
    Table.cpp \
    TableController.cpp \
    chefdecuisine.cpp \
    chefdepartie.cpp \
    chefdepatisserie.cpp \
    human.cpp \
    kitchencontroller.cpp \
    main.cpp \
    mainwindow.cpp \
    plongeur.cpp

HEADERS += \
    Staff.h \
    StaffController.h \
    Table.h \
    TableController.h \
    chefdecuisine.h \
    chefdepartie.h \
    chefdepatisserie.h \
    human.h \
    kitchencontroller.h \
    mainwindow.h \
    plongeur.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
