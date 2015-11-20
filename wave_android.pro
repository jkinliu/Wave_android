#-------------------------------------------------
#
# Project created by QtCreator 2015-11-02T19:51:09
#
#-------------------------------------------------

QT       += core gui network #ftp #serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = wave_android
TEMPLATE = app


SOURCES += main.cpp\
    loading.cpp \
    ftp.cpp \
    plot.cpp \
    protocol.cpp \
    tcpclient.cpp \
    curwaveh.cpp \
    download.cpp \
    curwavev.cpp \
    fileanalysis.cpp \
    analysis.cpp \
    setting.cpp \
    versionset.cpp \
    blockset.cpp \
    ipset.cpp \
    installset.cpp \
    wave.cpp

HEADERS  += \
    loading.h \
    ftp.h \
    global.h \
    plot.h \
    protocol.h \
    tcpclient.h \
    curwaveh.h \
    download.h \
    curwavev.h \
    fileanalysis.h \
    analysis.h \
    libmseed.h \
    lmplatform.h \
    packdata.h \
    steimdata.h \
    unpackdata.h \
    setting.h \
    versionset.h \
    blockset.h \
    ipset.h \
    installset.h \
    wave.h \
    qftp.h \
    qtftpversion.h \
    qurlinfo.h

FORMS    += \
    curwaveh.ui \
    download.ui \
    curwavev.ui \
    fileanalysis.ui \
    analysis.ui \
    setting.ui \
    versionset.ui \
    blockset.ui \
    ipset.ui \
    installset.ui \
    wave.ui \
    loading.ui

win32: include (C:/Qwt-6.1.2/features/qwt.prf)
#unix:  include (/usr/local/qwt-6.2.0-svn/features/qwt.prf)

win32: LIBS += -lws2_32

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    wave.qrc


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-mseed-Desktop_Qt_5_5_0_MinGW_32bit-Release/release/ -lmseed
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-mseed-Desktop_Qt_5_5_0_MinGW_32bit-Release/debug/ -lmseed

INCLUDEPATH += $$PWD/../build-mseed-Desktop_Qt_5_5_0_MinGW_32bit-Release/release
DEPENDPATH += $$PWD/../build-mseed-Desktop_Qt_5_5_0_MinGW_32bit-Release/release

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-mseed-Desktop_Qt_5_5_0_MinGW_32bit-Release/release/libmseed.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-mseed-Desktop_Qt_5_5_0_MinGW_32bit-Release/debug/libmseed.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-mseed-Desktop_Qt_5_5_0_MinGW_32bit-Release/release/mseed.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-mseed-Desktop_Qt_5_5_0_MinGW_32bit-Release/debug/mseed.lib

DISTFILES +=

unix:!macx: LIBS += -L$$PWD/../../E6300/build-qtftp-Android_for_armeabi_GCC_4_8_Qt_5_5_0-Debug/lib/ -lQt5Ftp

INCLUDEPATH += $$PWD/../../E6300/build-qtftp-Android_for_armeabi_GCC_4_8_Qt_5_5_0-Debug/include
DEPENDPATH += $$PWD/../../E6300/build-qtftp-Android_for_armeabi_GCC_4_8_Qt_5_5_0-Debug/include

unix:!macx: PRE_TARGETDEPS += $$PWD/../../E6300/build-qtftp-Android_for_armeabi_GCC_4_8_Qt_5_5_0-Debug/lib/libQt5Ftp.a
