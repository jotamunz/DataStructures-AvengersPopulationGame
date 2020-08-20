QT       += core gui
QT       += network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Date.cpp \
    HashMapFamily.cpp \
    HashMapId.cpp \
    HashSport.cpp \
    HashThanos.cpp \
    Person.cpp \
    Sin.cpp \
    Stream.cpp \
    Virtue.cpp \
    World.cpp \
    judgmentform.cpp \
    main.cpp \
    mainwindow.cpp \
    smtp.cpp \
    txtfilesform.cpp

HEADERS += \
    BinaryTree.h \
    Date.h \
    DoubleList.h \
    HashMapFamily.h \
    HashMapId.h \
    HashSport.h \
    HashThanos.h \
    Person.h \
    Sin.h \
    Stream.h \
    Virtue.h \
    World.h \
    judgmentform.h \
    mainwindow.h \
    smtp.h \
    txtfilesform.h

FORMS += \
    judgmentform.ui \
    mainwindow.ui \
    txtfilesform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc

DISTFILES += \
    ../../Downloads/ThanosBackground.jpg
