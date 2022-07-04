QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Notes/Note.cpp \
    Notes/NoteImage.cpp \
    Notes/NoteText.cpp \
    Notes/NoteBoardLink.cpp \
    Tools/DBManager.cpp \
    Tools/DataHandler.cpp \
    UI-Components/Board.cpp \
    UI-Components/Cork.cpp \
    UI-Components/Sidebar.cpp \
    UI-Components/Wall.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Notes/Note.h \
    Notes/NoteImage.h \
    Notes/NoteText.h \
    Notes/NoteBoardLink.h \
    Tools/DBManager.h \
    Tools/DataHandler.h \
    UI-Components/Board.h \
    UI-Components/Cork.h \
    UI-Components/Sidebar.h \
    UI-Components/Wall.h \
    mainwindow.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
