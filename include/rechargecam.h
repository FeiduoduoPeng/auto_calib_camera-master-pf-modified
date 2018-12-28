#ifndef __RECHARGECAM_h__
#define __RECHARGECAM_h__
#include <iostream>
#include <unistd.h>
#include <chrono>

#include <QThread>
#include <QMutex>
#include <QString>

#include "include/logger.h"
#include "include/V4l2Access.h"
#include "include/V4l2Capture.h"
#include "include/V4l2Device.h"
#include "include/V4l2MmapDevice.h"
#include "include/V4l2Output.h"
#include "include/V4l2ReadWriteDevice.h"

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"

#define WIDTH  480
#define HEIGHT  640
#define FPS  30

class RechargeCam : public QThread{
    Q_OBJECT

public:
    RechargeCam();
    ~RechargeCam();
    virtual void run();
    virtual void stop(){
        runFlag = false;
        delete videoCapture;
    }

public:
    void cvtYUV2RGB(unsigned char* yuv_buffer, cv::Mat& image, int height, int width);
    void saveImg();
    cv::Mat getImg(bool hasCorner);

signals:
    void send();

private:
    V4l2Capture *videoCapture;
    bool runFlag;
    timeval timeout;
    int bufferSize = WIDTH*HEIGHT*2;
    char *buffer;
    cv::Mat img;
    cv::Mat img_c;
    QMutex mtx;
};
#endif
