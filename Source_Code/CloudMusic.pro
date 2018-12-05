QT       += core gui multimedia sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CloudMusic
TEMPLATE = app

RC_ICONS = Desktopico.ico

LIBS += ../taglib/lib/libtag.dll.a
LIBS += ../taglib/lib/libtag_c.dll.a

INCLUDEPATH += ./taglib/include/taglib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    MainWidget.cpp \
    TitleBar.cpp \
    FramelessWidget.cpp \
    miniWidget.cpp \
    TrayIconMenu.cpp \
    BottomWidget.cpp \
    MiddleWidget.cpp \
    MiddleWidgetLeftList.cpp \
    MiddleWidgetRightStack.cpp \
    ListWidgetFindMusic.cpp \
    AnimationWidget.cpp \
    ListWidgetLocalMusic.cpp \
    SelectDirFrame.cpp \
    PlaySongInfoWidget.cpp \
    SongListFrame.cpp \
    PlayListItemStyle.cpp \
    SkinWidget.cpp \
    ClickLabel.cpp \
    TurntableWidget.cpp

HEADERS  += \
    MainWidget.h \
    TitleBar.h \
    FramelessWidget.h \
    miniWidget.h \
    TrayIconMenu.h \
    BottomWidget.h \
    MiddleWidget.h \
    MiddleWidgetLeftList.h \
    MiddleWidgetRightStack.h \
    ListWidgetFindMusic.h \
    AnimationWidget.h \
    ListWidgetLocalMusic.h \
    SelectDirFrame.h \
    PlaySongInfoWidget.h \
    SongListFrame.h \
    PlayListItemStyle.h \
    SkinWidget.h \
    ClickLabel.h \
    TurntableWidget.h

RESOURCES += \
    res.qrc

DISTFILES +=
