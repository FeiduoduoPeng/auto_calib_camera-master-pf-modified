#############################################################################
# Makefile for building: calib_camera
# Generated by qmake (3.0) (Qt 5.5.1)
# Project:  calib_camera.pro
# Template: app
# Command: /usr/lib/x86_64-linux-gnu/qt5/bin/qmake -spec linux-g++-64 CONFIG+=debug -o Makefile calib_camera.pro
#############################################################################

MAKEFILE      = Makefile

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_SERIALPORT_LIB -DQT_CORE_LIB
CFLAGS        = -m64 -pipe -g -Wall -W -D_REENTRANT -fPIC $(DEFINES)
CXXFLAGS      = -m64 -pipe -g -std=c++0x -Wall -W -D_REENTRANT -fPIC $(DEFINES)
INCPATH       = -I. -Iinclude -isystem /usr/local/include -isystem /usr/local/include/opencv -isystem /usr/local/include/opencv2 -isystem /usr/include/pcl-1.7 -isystem /usr/include/eigen3 -I../Document/Linux/OpenNI-Linux-x64-2.3/Include -isystem /usr/include/x86_64-linux-gnu/qt5 -isystem /usr/include/x86_64-linux-gnu/qt5/QtWidgets -isystem /usr/include/x86_64-linux-gnu/qt5/QtGui -isystem /usr/include/x86_64-linux-gnu/qt5/QtSerialPort -isystem /usr/include/x86_64-linux-gnu/qt5/QtCore -I. -I. -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64
QMAKE         = /usr/lib/x86_64-linux-gnu/qt5/bin/qmake
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = cp -f -R
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
TAR           = tar -cf
COMPRESS      = gzip -9f
DISTNAME      = calib_camera1.0.0
DISTDIR = /home/leisure/auto_calib_camera-master-pf-modified-ok-1128/.tmp/calib_camera1.0.0
LINK          = g++
LFLAGS        = -m64
LIBS          = $(SUBLIBS) -L/usr/X11R6/lib64 /usr/local/lib/libopencv_calib3d.so /usr/local/lib/libopencv_contrib.so /usr/local/lib/libopencv_core.so /usr/local/lib/libopencv_features2d.so /usr/local/lib/libopencv_flann.so /usr/local/lib/libopencv_gpu.so /usr/local/lib/libopencv_highgui.so /usr/local/lib/libopencv_imgproc.so /usr/local/lib/libopencv_legacy.so /usr/local/lib/libopencv_ml.so /usr/local/lib/libopencv_nonfree.so /usr/local/lib/libopencv_objdetect.so /usr/local/lib/libopencv_ocl.so /usr/local/lib/libopencv_photo.so /usr/local/lib/libopencv_stitching.so /usr/local/lib/libopencv_superres.so /usr/local/lib/libopencv_video.so /usr/local/lib/libopencv_videostab.so /usr/local/lib/libopencv_imgcodecs.so -L/usr/local/lib -L/usr/lib -lmysqlcppconn -L/home/leisure/Document/Linux/OpenNI-Linux-x64-2.3/Redist -lOpenNI2 -lusb-1.0 -lGLU -lglut -lboost_system -lpcl_io -lpcl_common -lpcl_segmentation -lQt5Widgets -lQt5Gui -lQt5SerialPort -lQt5Core -lGL -lpthread 
AR            = ar cqs
RANLIB        = 
SED           = sed
STRIP         = strip

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		mainwindow.cpp \
		communication.cpp \
		thread.cpp \
		src/cedriver_usb.cpp \
		src/cedriver_cam.cpp \
		src/cedriver_config.cpp \
		src/celib_img_process.cpp \
		src/cetool_cali_stereo_capture_img.cpp moc_mainwindow.cpp \
		moc_thread.cpp
OBJECTS       = main.o \
		mainwindow.o \
		communication.o \
		thread.o \
		cedriver_usb.o \
		cedriver_cam.o \
		cedriver_config.o \
		celib_img_process.o \
		cetool_cali_stereo_capture_img.o \
		moc_mainwindow.o \
		moc_thread.o
DIST          = /usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_pre.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/linux.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/sanitize.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base-unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-base.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/qconfig.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_clucene_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_designer.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_designer_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_designercomponents_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfs_device_lib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_help.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_help_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_multimedia.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_multimediawidgets.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_platformsupport_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_qml.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_qml_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_qmldevtools_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_qmltest.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_qmltest_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_quick.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_quick_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_quickparticles_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_quickwidgets.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_quickwidgets_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_script.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_script_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_scripttools.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_scripttools_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_serialport.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_svg.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_uiplugin.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_uitools.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_uitools_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_webkit.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_webkitwidgets.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_x11extras.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xmlpatterns.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xmlpatterns_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_functions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_config.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64/qmake.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_post.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exclusive_builds.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_pre.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resolve_config.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_post.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/link_pkgconfig.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/c++11.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/warn_on.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resources.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/moc.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/opengl.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/uic.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/thread.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/testcase_targets.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exceptions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/yacc.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/lex.prf \
		calib_camera.pro mainwindow.h \
		communication.h \
		thread.h \
		global.h \
		include/cedriver_cam.h \
		include/cedriver_imu.h \
		include/cedriver_config.h \
		include/celib_img_process.h \
		include/cedriver_usb.h \
		include/mycetool_calib_stereo_capture_img.h \
		include/threadsafe_queue.h main.cpp \
		mainwindow.cpp \
		communication.cpp \
		thread.cpp \
		src/cedriver_usb.cpp \
		src/cedriver_cam.cpp \
		src/cedriver_config.cpp \
		src/celib_img_process.cpp \
		src/cetool_cali_stereo_capture_img.cpp
QMAKE_TARGET  = calib_camera
DESTDIR       = #avoid trailing-slash linebreak
TARGET        = calib_camera


first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

$(TARGET): ui_mainwindow.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: calib_camera.pro /usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64/qmake.conf /usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_pre.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/linux.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/sanitize.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base-unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-base.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/qconfig.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_clucene_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_designer.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_designer_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_designercomponents_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfs_device_lib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_help.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_help_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_multimedia.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_multimediawidgets.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_platformsupport_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_qml.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_qml_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_qmldevtools_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_qmltest.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_qmltest_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_quick.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_quick_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_quickparticles_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_quickwidgets.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_quickwidgets_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_script.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_script_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_scripttools.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_scripttools_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_serialport.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_svg.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_uiplugin.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_uitools.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_uitools_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_webkit.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_webkitwidgets.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_x11extras.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xmlpatterns.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xmlpatterns_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_functions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_config.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64/qmake.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_post.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exclusive_builds.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_pre.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resolve_config.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_post.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/link_pkgconfig.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/c++11.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/warn_on.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resources.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/moc.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/opengl.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/uic.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/thread.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/testcase_targets.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exceptions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/yacc.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/lex.prf \
		calib_camera.pro \
		/usr/lib/x86_64-linux-gnu/libQt5Widgets.prl \
		/usr/lib/x86_64-linux-gnu/libQt5Gui.prl \
		/usr/lib/x86_64-linux-gnu/libQt5SerialPort.prl \
		/usr/lib/x86_64-linux-gnu/libQt5Core.prl
	$(QMAKE) -spec linux-g++-64 CONFIG+=debug -o Makefile calib_camera.pro
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_pre.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/unix.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/linux.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/sanitize.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base-unix.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-base.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-unix.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/qconfig.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_clucene_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_designer.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_designer_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_designercomponents_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfs_device_lib_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_help.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_help_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_multimedia.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_multimediawidgets.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_platformsupport_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_qml.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_qml_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_qmldevtools_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_qmltest.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_qmltest_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_quick.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_quick_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_quickparticles_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_quickwidgets.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_quickwidgets_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_script.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_script_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_scripttools.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_scripttools_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_serialport.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_svg.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_uiplugin.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_uitools.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_uitools_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_webkit.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_webkitwidgets.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_x11extras.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xmlpatterns.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xmlpatterns_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_functions.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_config.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64/qmake.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_post.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exclusive_builds.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_pre.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resolve_config.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_post.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/link_pkgconfig.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/c++11.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/warn_on.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resources.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/moc.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/opengl.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/uic.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/thread.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/testcase_targets.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exceptions.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/yacc.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/lex.prf:
calib_camera.pro:
/usr/lib/x86_64-linux-gnu/libQt5Widgets.prl:
/usr/lib/x86_64-linux-gnu/libQt5Gui.prl:
/usr/lib/x86_64-linux-gnu/libQt5SerialPort.prl:
/usr/lib/x86_64-linux-gnu/libQt5Core.prl:
qmake: FORCE
	@$(QMAKE) -spec linux-g++-64 CONFIG+=debug -o Makefile calib_camera.pro

qmake_all: FORCE


all: Makefile $(TARGET)

dist: distdir FORCE
	(cd `dirname $(DISTDIR)` && $(TAR) $(DISTNAME).tar $(DISTNAME) && $(COMPRESS) $(DISTNAME).tar) && $(MOVE) `dirname $(DISTDIR)`/$(DISTNAME).tar.gz . && $(DEL_FILE) -r $(DISTDIR)

distdir: FORCE
	@test -d $(DISTDIR) || mkdir -p $(DISTDIR)
	$(COPY_FILE) --parents $(DIST) $(DISTDIR)/
	$(COPY_FILE) --parents mainwindow.h communication.h thread.h global.h include/cedriver_cam.h include/cedriver_imu.h include/cedriver_config.h include/celib_img_process.h include/cedriver_usb.h include/mycetool_calib_stereo_capture_img.h include/threadsafe_queue.h $(DISTDIR)/
	$(COPY_FILE) --parents main.cpp mainwindow.cpp communication.cpp thread.cpp src/cedriver_usb.cpp src/cedriver_cam.cpp src/cedriver_config.cpp src/celib_img_process.cpp src/cetool_cali_stereo_capture_img.cpp $(DISTDIR)/
	$(COPY_FILE) --parents mainwindow.ui $(DISTDIR)/


clean: compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


distclean: clean 
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


####### Sub-libraries

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

check: first

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_moc_header_make_all: moc_mainwindow.cpp moc_thread.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp moc_thread.cpp
moc_mainwindow.cpp: thread.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OpenNI.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniPlatform.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/Win32/OniPlatformWin32.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/Android-Arm/OniPlatformAndroid-Arm.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/Linux-x86/OniPlatformLinux-x86.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/Linux-Arm/OniPlatformLinux-Arm.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/MacOSX/OniPlatformMacOSX.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniProperties.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniEnums.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniCAPI.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniCTypes.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniCEnums.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniCProperties.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniVersion.h \
		include/cedriver_cam.h \
		include/threadsafe_queue.h \
		include/cedriver_global_config.h \
		global.h \
		include/cedriver_config.h \
		include/mycetool_calib_stereo_capture_img.h \
		mainwindow.h
	/usr/lib/x86_64-linux-gnu/qt5/bin/moc $(DEFINES) -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64 -I/home/leisure/auto_calib_camera-master-pf-modified-ok-1128 -I/home/leisure/auto_calib_camera-master-pf-modified-ok-1128/include -I/usr/local/include -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/include/pcl-1.7 -I/usr/include/eigen3 -I/home/leisure/Document/Linux/OpenNI-Linux-x64-2.3/Include -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtSerialPort -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/c++/5 -I/usr/include/x86_64-linux-gnu/c++/5 -I/usr/include/c++/5/backward -I/usr/lib/gcc/x86_64-linux-gnu/5/include -I/usr/local/include -I/usr/lib/gcc/x86_64-linux-gnu/5/include-fixed -I/usr/include/x86_64-linux-gnu -I/usr/include mainwindow.h -o moc_mainwindow.cpp

moc_thread.cpp: ../Document/Linux/OpenNI-Linux-x64-2.3/Include/OpenNI.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniPlatform.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/Win32/OniPlatformWin32.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/Android-Arm/OniPlatformAndroid-Arm.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/Linux-x86/OniPlatformLinux-x86.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/Linux-Arm/OniPlatformLinux-Arm.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/MacOSX/OniPlatformMacOSX.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniProperties.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniEnums.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniCAPI.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniCTypes.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniCEnums.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniCProperties.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniVersion.h \
		thread.h
	/usr/lib/x86_64-linux-gnu/qt5/bin/moc $(DEFINES) -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64 -I/home/leisure/auto_calib_camera-master-pf-modified-ok-1128 -I/home/leisure/auto_calib_camera-master-pf-modified-ok-1128/include -I/usr/local/include -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/include/pcl-1.7 -I/usr/include/eigen3 -I/home/leisure/Document/Linux/OpenNI-Linux-x64-2.3/Include -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtSerialPort -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/c++/5 -I/usr/include/x86_64-linux-gnu/c++/5 -I/usr/include/c++/5/backward -I/usr/lib/gcc/x86_64-linux-gnu/5/include -I/usr/local/include -I/usr/lib/gcc/x86_64-linux-gnu/5/include-fixed -I/usr/include/x86_64-linux-gnu -I/usr/include thread.h -o moc_thread.cpp

compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mainwindow.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainwindow.h
ui_mainwindow.h: mainwindow.ui
	/usr/lib/x86_64-linux-gnu/qt5/bin/uic mainwindow.ui -o ui_mainwindow.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

main.o: main.cpp mainwindow.h \
		thread.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OpenNI.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniPlatform.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/Win32/OniPlatformWin32.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/Android-Arm/OniPlatformAndroid-Arm.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/Linux-x86/OniPlatformLinux-x86.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/Linux-Arm/OniPlatformLinux-Arm.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/MacOSX/OniPlatformMacOSX.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniProperties.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniEnums.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniCAPI.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniCTypes.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniCEnums.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniCProperties.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniVersion.h \
		include/cedriver_cam.h \
		include/threadsafe_queue.h \
		include/cedriver_global_config.h \
		global.h \
		include/cedriver_config.h \
		include/mycetool_calib_stereo_capture_img.h \
		communication.h \
		ui_mainwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

mainwindow.o: mainwindow.cpp mainwindow.h \
		thread.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OpenNI.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniPlatform.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/Win32/OniPlatformWin32.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/Android-Arm/OniPlatformAndroid-Arm.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/Linux-x86/OniPlatformLinux-x86.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/Linux-Arm/OniPlatformLinux-Arm.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/MacOSX/OniPlatformMacOSX.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniProperties.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniEnums.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniCAPI.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniCTypes.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniCEnums.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniCProperties.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniVersion.h \
		include/cedriver_cam.h \
		include/threadsafe_queue.h \
		include/cedriver_global_config.h \
		global.h \
		include/cedriver_config.h \
		include/mycetool_calib_stereo_capture_img.h \
		ui_mainwindow.h \
		communication.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.cpp

communication.o: communication.cpp communication.h \
		mainwindow.h \
		thread.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OpenNI.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniPlatform.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/Win32/OniPlatformWin32.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/Android-Arm/OniPlatformAndroid-Arm.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/Linux-x86/OniPlatformLinux-x86.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/Linux-Arm/OniPlatformLinux-Arm.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/MacOSX/OniPlatformMacOSX.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniProperties.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniEnums.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniCAPI.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniCTypes.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniCEnums.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniCProperties.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniVersion.h \
		include/cedriver_cam.h \
		include/threadsafe_queue.h \
		include/cedriver_global_config.h \
		global.h \
		include/cedriver_config.h \
		include/mycetool_calib_stereo_capture_img.h \
		ui_mainwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o communication.o communication.cpp

thread.o: thread.cpp thread.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OpenNI.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniPlatform.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/Win32/OniPlatformWin32.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/Android-Arm/OniPlatformAndroid-Arm.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/Linux-x86/OniPlatformLinux-x86.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/Linux-Arm/OniPlatformLinux-Arm.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/MacOSX/OniPlatformMacOSX.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniProperties.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniEnums.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniCAPI.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniCTypes.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniCEnums.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniCProperties.h \
		../Document/Linux/OpenNI-Linux-x64-2.3/Include/OniVersion.h \
		mainwindow.h \
		include/cedriver_cam.h \
		include/threadsafe_queue.h \
		include/cedriver_global_config.h \
		global.h \
		include/cedriver_config.h \
		include/mycetool_calib_stereo_capture_img.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o thread.o thread.cpp

cedriver_usb.o: src/cedriver_usb.cpp include/cedriver_usb.h \
		include/cedriver_global_config.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o cedriver_usb.o src/cedriver_usb.cpp

cedriver_cam.o: src/cedriver_cam.cpp include/cedriver_usb.h \
		include/cedriver_global_config.h \
		include/cedriver_cam.h \
		include/threadsafe_queue.h \
		global.h \
		include/cedriver_config.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o cedriver_cam.o src/cedriver_cam.cpp

cedriver_config.o: src/cedriver_config.cpp include/cedriver_config.h \
		include/cedriver_global_config.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o cedriver_config.o src/cedriver_config.cpp

celib_img_process.o: src/celib_img_process.cpp include/celib_img_process.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o celib_img_process.o src/celib_img_process.cpp

cetool_cali_stereo_capture_img.o: src/cetool_cali_stereo_capture_img.cpp include/cedriver_usb.h \
		include/cedriver_global_config.h \
		include/cedriver_cam.h \
		include/threadsafe_queue.h \
		global.h \
		include/cedriver_imu.h \
		include/cedriver_config.h \
		include/celib_img_process.h \
		include/mycetool_calib_stereo_capture_img.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o cetool_cali_stereo_capture_img.o src/cetool_cali_stereo_capture_img.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_thread.o: moc_thread.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_thread.o moc_thread.cpp

####### Install

install:  FORCE

uninstall:  FORCE

FORCE:

