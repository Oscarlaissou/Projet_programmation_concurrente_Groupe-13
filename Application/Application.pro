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
    # Staff.cpp \
    # StaffController.cpp \
    Table.cpp \
    chefdecuisine.cpp \
    chefdepartie.cpp \
    chefdepatisserie.cpp \
    commis1.cpp \
    commis2.cpp \
    human.cpp \
    kitchencontroller.cpp \
    main.cpp \
    mainwindow.cpp \
    plongeur.cpp \
    Client.cpp \
        ClientController.cpp \
        OrderController.cpp \
        RoomMaster.cpp \
        RoomMasterController.cpp \
        # Staff.cpp \
        # StaffController.cpp \
        TableController.cpp \
         viewwindow.cpp

HEADERS += \
    # Staff.h \
    # StaffController.h \
    Table.h \
    chefdecuisine.h \
    chefdepartie.h \
    chefdepatisserie.h \
    commis1.h \
    commis2.h \
    human.h \
    kitchencontroller.h \
    mainwindow.h \
    plongeur.h \
    Client.h \
        ClientController.h \
        OrderController.h \
        RoomMaster.h \
        RoomMasterController.h \
        # Staff.h \
        # StaffController.h \
        TableController.h \
        viewwindow.h

FORMS += \
    mainwindow.ui \
    viewwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
