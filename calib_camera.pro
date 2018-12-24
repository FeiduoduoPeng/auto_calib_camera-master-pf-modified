#-------------------------------------------------
#
# Project created by QtCreator 2018-06-26T03:51:25
#
#-------------------------------------------------

QT       += core gui serialport multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 \
CONFIG += link_pkgconfig
#CONFIG += -rtti
QMAKE_CXXFLAGS += -std=c++11
#QMAKE_CXXFLAGS += -rtti

PKGCONFIG += eigen3

TARGET = calib_camera
TEMPLATE = app

INCLUDEPATH += $$PWD/include
SOURCES += main.cpp\
    mainwindow.cpp \
    communication.cpp \
    thread.cpp \
    src/fisheye_calibrate.cpp \
    src/devices_id.cpp \
    src/cedriver_usb.cpp \
    src/cedriver_cam.cpp \
    src/cedriver_config.cpp \
    src/list_devices.cpp \
    src/celib_img_process.cpp \
    src/myWriteMySQL.cpp \
    src/cetool_cali_stereo_capture_img.cpp \
    src/rechargecam.cpp

HEADERS  += mainwindow.h \
    communication.h \
    thread.h \
    global.h \
    include/fisheye_calibrate.h \
    include/cedriver_cam.h \
    include/cedriver_imu.h \
    include/cedriver_config.h \
    include/celib_img_process.h \
    include/cedriver_usb.h \
    include/cooleye_monocular/list_devices.h \
    include/mycetool_calib_stereo_capture_img.h \
    include/cedriver_global_config.h \
    include/devices_id.h \
    include/myWriteMySQL.h \
    include/threadsafe_queue.h	\
    include/V4l2Access.h	\
    include/V4l2Capture.h	\
    include/V4l2Device.h	\
    include/V4l2MmapDevice.h	\
    include/V4l2Output.h	\
    include/V4l2ReadWriteDevice.h \
    include/rechargecam.h


FORMS    += mainwindow.ui

INCLUDEPATH += /usr/local/include \
/usr/local/include/opencv \
/usr/local/include/opencv2 \
/usr/include/pcl-1.7 \
/usr/include \
/usr/include/eigen3


LIBS += -L/usr/local/lib
LIBS += -L/usr/lib
LIBS += -L/usr/lib/x86_64-linux-gun
LIBS += -Lmylib
LIBS += -lmysqlcppconn


#INCLUDEPATH += $$(OPENNI2_INCLUDE)
#LIBS += -L$$(OPENNI2_REDIST)

INCLUDEPATH += include/openni2
LIBS += -Linclude/openni2_redist/x64

# LIBS += -lDevicesID	\
LIBS += -lastra_wrapper \
        -lCEDRIVER_CAM_MONOCULAR \
        -lCEDRIVER_CONFIG_MONOCULAR \
        -lv4l2wrapper	\
        -llog4cpp

LIBS += -lpcl_io -lpcl_common -lpcl_segmentation
LIBS += -lOpenNI2 -lusb-1.0 -lGL -lGLU -lglut -lmysqlcppconn
LIBS += /usr/lib/x86_64-linux-gnu/libboost_system.so \
        /usr/lib/x86_64-linux-gnu/libboost_thread.so \
        /usr/lib/x86_64-linux-gnu/libboost_chrono.so \
        /usr/lib/x86_64-linux-gnu/libboost_date_time.so \
        /usr/lib/x86_64-linux-gnu/libboost_atomic.so

LIBS += /usr/local/lib/libopencv_calib3d.so\
    /usr/local/lib/libopencv_core.so \
    /usr/local/lib/libopencv_features2d.so \
    /usr/local/lib/libopencv_flann.so \
    /usr/local/lib/libopencv_highgui.so \
    /usr/local/lib/libopencv_imgproc.so \
    /usr/local/lib/libopencv_ml.so \
    /usr/local/lib/libopencv_objdetect.so \
    /usr/local/lib/libopencv_photo.so \
    /usr/local/lib/libopencv_stitching.so \
    /usr/local/lib/libopencv_superres.so \
    /usr/local/lib/libopencv_video.so \
    /usr/local/lib/libopencv_videostab.so \
    /usr/local/lib/libopencv_imgcodecs.so \
