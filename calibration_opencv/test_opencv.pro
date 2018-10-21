TARGET = test_opencv

TEMPLATE = app
CONFIG += c++11
CONFIG -= qt

SOURCES += test_opencv.cpp

INCLUDEPATH += /usr/local/include
INCLUDEPATH += /usr/local/include/opencv 
INCLUDEPATH += /usr/local/include/opencv2 

LIBS += -L/usr/local/lib \
-lopencv_core \
-lopencv_highgui \
-lopencv_imgproc \
-lopencv_imgcodecs