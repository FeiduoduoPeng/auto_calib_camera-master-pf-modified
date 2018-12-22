

#include "thread.h"

#include "mainwindow.h"
#include <QApplication>


#include <stdlib.h>

#include <iostream>

#include <string>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <iostream>

#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <qdebug.h>
using namespace std;
using namespace openni;
using namespace cv;


#define DEPTH_SCALE_FACTOR 256./4096.
#define COLOR_CHANNEL 1
#define IR_CHANNEL 2
Thread::Thread()
{
  save_image_flag = 0;
}

void Thread::stop()
{
    run_flag = 0;
}

void Thread::save_image()
{
    static int i=0;
    string image_name;
    char temp[50];
    i++;
    sprintf(temp,"color_image/cImageBGR%d.jpg",i);
    image_name.append(temp);
    cv::imwrite(image_name,get_color_img());

    image_name.clear();
    sprintf(temp,"IR_image/mScaledIR%d.jpg",i);
    image_name.append(temp);
    cv::imwrite(image_name,get_ir_img());
}

void Thread::SetImageSave()
{
     mutex.lock();
     save_image_flag = 1;
     mutex.unlock();
}

void Thread::SetImageShowColor()
{
     mutex.lock();
     if(show_channel != COLOR_CHANNEL)
     {
        is_change_to_color = 1;
        show_channel = COLOR_CHANNEL;
     }
     mutex.unlock();
}

void Thread::SetImageShowIR()
{
    mutex.lock();
    if(show_channel != IR_CHANNEL)
    {
       is_change_to_ir = 1;
       show_channel = IR_CHANNEL;
    }
    mutex.unlock();
}

cv::Mat Thread::get_color_img()
{
    mutex.lock();
    cv::Mat temp_= cImageBGR;
    mutex.unlock();
    return temp_;
}

cv::Mat Thread::get_depth_img()
{
    mutex.lock();
    cv::Mat temp_= mScaledDepth;
    mutex.unlock();
    return temp_;
}

cv::Mat Thread::get_ir_img()
{
    mutex.lock();
    cv::Mat temp_= cImageIR;
    mutex.unlock();
    return temp_;
}

void CheckOpenNIError(Status result, string status)
{
    if (result != STATUS_OK)
        cerr << status << " Error: " << OpenNI::getExtendedError() << endl;
}

void Thread::run()
{
    run_flag = 1;
    Status result = STATUS_OK;

    is_change_to_ir = 0;
    is_change_to_color = 0;
    VideoFrameRef oniColorImg;
    VideoFrameRef oniIrImg;
    cv::Mat cvBGRImg;
    cv::Mat cvIrImg;

    result = OpenNI::initialize();
    CheckOpenNIError(result, "initialize context");

    Device device;
    result = device.open(openni::ANY_DEVICE);

    VideoStream oniIrStream;
    result = oniIrStream.create(device, openni::SENSOR_IR);


    VideoMode modeIr;
    modeIr.setResolution(640, 480);
    modeIr.setFps(30);
    modeIr.setPixelFormat(PIXEL_FORMAT_GRAY16);
    oniIrStream.setVideoMode(modeIr);

    VideoStream oniColorStream;
    result = oniColorStream.create(device, openni::SENSOR_COLOR);
    VideoMode modeColor;
    modeColor.setResolution(640, 480);
    modeColor.setFps(30);
    modeColor.setPixelFormat(PIXEL_FORMAT_RGB888);
    oniColorStream.setVideoMode(modeColor);

    save_image_flag = 0;
    show_channel = IR_CHANNEL;
    if(show_channel ==IR_CHANNEL){
       oniIrStream.start();
        oniColorStream.stop();
    }
    if(show_channel ==COLOR_CHANNEL){
        oniIrStream.stop();
        oniColorStream.start();
    }

    while (run_flag)
    {
        if (save_image_flag) {
            if(show_channel ==IR_CHANNEL)
            {
                oniIrStream.stop();
                oniColorStream.start();
                if (oniColorStream.readFrame(&oniColorImg) == STATUS_OK)
                {
                    cv::Mat cvRGBImg(oniColorImg.getHeight(), oniColorImg.getWidth(), CV_8UC3, (void*)oniColorImg.getData());
                    cv::cvtColor(cvRGBImg, cvBGRImg, CV_RGB2BGR);
                    flip(cvBGRImg, cImageBGR, 1);
                    save_image();
                    save_image_flag = 0;
                }
                oniColorStream.stop();
                oniIrStream.start();
            }
            if(show_channel ==COLOR_CHANNEL)
            {
                oniColorStream.stop();
                oniIrStream.start();

                if (oniIrStream.readFrame(&oniIrImg) == STATUS_OK)
                {
                    cv::Mat cvRawImg16U(oniIrImg.getHeight(), oniIrImg.getWidth(), CV_16UC1, (void*)oniIrImg.getData());
                    cvRawImg16U.convertTo(cvIrImg, CV_8U);
                    flip(cvIrImg, cvIrImg, 1);
                    cImageIR = cvIrImg;
                    save_image();
                    save_image_flag = 0;
                }
                oniIrStream.stop();
                oniColorStream.start();
            }
        }

        if(show_channel ==IR_CHANNEL)
        {
            if(is_change_to_ir)
            {
                oniColorStream.stop();
                oniIrStream.start();

                is_change_to_ir = 0;
            }
            if (oniIrStream.readFrame(&oniIrImg) == STATUS_OK)
            {
                cv::Mat cvRawImg16U(oniIrImg.getHeight(), oniIrImg.getWidth(), CV_16UC1, (void*)oniIrImg.getData());
                cvRawImg16U.convertTo(cvIrImg, CV_8U);
                flip(cvIrImg, cvIrImg, 1);
                cImageIR = cvIrImg;
                emit send(QString("thread"));
            }
        }
        if(show_channel ==COLOR_CHANNEL)
        {
            if(is_change_to_color)
            {
                oniIrStream.stop();
                oniColorStream.start();
                is_change_to_color = 0;
            }
            if (oniColorStream.readFrame(&oniColorImg) == STATUS_OK)
            {
                cv::Mat cvRGBImg(oniColorImg.getHeight(), oniColorImg.getWidth(), CV_8UC3, (void*)oniColorImg.getData());
                cv::cvtColor(cvRGBImg, cvBGRImg, CV_RGB2BGR);
                flip(cvBGRImg, cImageBGR, 1);
                emit send(QString("thread"));
            }
        }
    }

    oniColorStream.destroy();
    oniIrStream.destroy();
    device.close();
    OpenNI::shutdown();

}



