QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../../Controller/sources/controller.cpp \
    ../../../Model/sources/API.cpp \
    ../../../Model/sources/data_checker.cpp  \
    ../../../Model/sources/DBG_functs.cpp \
    ../../../Model/sources/infix_to_postfix.cpp \
    ../../../Model/sources/postfix_calculator.cpp \
    ../../../Model/sources/token_extraction.cpp \
    functiongraphd.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \


HEADERS += \
    functiongraphd.h \
    mainwindow.h \
    qcustomplot.h \
    ../../../Controller/headers/controller.h \
    ../../../Model/headers/backend.h \

FORMS += \
    functiongraphd.ui \
    mainwindow.ui

# LIBS += "../../../Model/s21_calc_backend.a"

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Makefile \
    UltraCalculator.pro.user
