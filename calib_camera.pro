#-------------------------------------------------
#
# Project created by QtCreator 2018-06-26T03:51:25
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TARGET = calib_camera
TEMPLATE = app

INCLUDEPATH += $$PWD/include
SOURCES += main.cpp\
        mainwindow.cpp \
    communication.cpp \
    thread.cpp \
    src/cedriver_usb.cpp \
    src/cedriver_cam.cpp \
    src/cedriver_config.cpp \
    src/celib_img_process.cpp \
    src/cetool_cali_stereo_capture_img.cpp

HEADERS  += mainwindow.h \
    communication.h \
    thread.h \
    global.h \
    include/cedriver_cam.h \
    include/cedriver_imu.h \
    include/cedriver_config.h \
    include/celib_img_process.h \
    include/cedriver_usb.h \
    include/mycetool_calib_stereo_capture_img.h \
    include/threadsafe_queue.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/local/include \

/usr/local/include/opencv \

/usr/local/include/opencv2 \

INCLUDEPATH += $$(OPENNI2_INCLUDE)


LIBS += /usr/local/lib/libopencv_calib3d.so\
    /usr/local/lib/libopencv_contrib.so \
    /usr/local/lib/libopencv_core.so \
    /usr/local/lib/libopencv_features2d.so \
    /usr/local/lib/libopencv_flann.so \
    /usr/local/lib/libopencv_gpu.so \
    /usr/local/lib/libopencv_highgui.so \
    /usr/local/lib/libopencv_imgproc.so \
    /usr/local/lib/libopencv_legacy.so \
    /usr/local/lib/libopencv_ml.so \
    /usr/local/lib/libopencv_nonfree.so \
    /usr/local/lib/libopencv_objdetect.so \
    /usr/local/lib/libopencv_ocl.so \
    /usr/local/lib/libopencv_photo.so \
    /usr/local/lib/libopencv_stitching.so \
    /usr/local/lib/libopencv_superres.so \
    /usr/local/lib/libopencv_video.so \
    /usr/local/lib/libopencv_videostab.so \
    /usr/local/lib/libopencv_imgcodecs.so \


LIBS += -L/use/local/lib
LIBS += -lmysqlcppconn

LIBS += -L$$(OPENNI2_REDIST)

LIBS += -lOpenNI2 -lusb-1.0 -lGL -lGLU -lglut
