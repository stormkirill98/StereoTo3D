#-------------------------------------------------
#
# Project created by QtCreator 2019-06-27T21:22:09
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StereoTo3D
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        camera.cpp \
        definition_camera_ids.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        camera.h \
        definition_camera_ids.h \
        image_converting.h \
        mainwindow.h

FORMS += \
        mainwindow.ui

INCLUDEPATH += C:\OpenCV-4.0.1\opencv\build\include

LIBS += C:\OpenCV-4.0.1\opencv-build\bin\libopencv_core401.dll
LIBS += C:\OpenCV-4.0.1\opencv-build\bin\libopencv_highgui401.dll
LIBS += C:\OpenCV-4.0.1\opencv-build\bin\libopencv_imgcodecs401.dll
LIBS += C:\OpenCV-4.0.1\opencv-build\bin\libopencv_imgproc401.dll
LIBS += C:\OpenCV-4.0.1\opencv-build\bin\libopencv_features2d401.dll
LIBS += C:\OpenCV-4.0.1\opencv-build\bin\libopencv_calib3d401.dll
LIBS += C:\OpenCV-4.0.1\opencv-build\bin\libopencv_videoio401.dll


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
