#include "rechargecam.h"

RechargeCam::RechargeCam(){
    buffer =  new char[WIDTH*HEIGHT*2];
    img = cv::Mat(cv::Size(HEIGHT,WIDTH), CV_8UC3);
}

RechargeCam::~RechargeCam(){
    delete buffer;
    delete videoCapture;
}

void RechargeCam::run(){
    V4L2DeviceParameters param("/dev/video0", V4L2_PIX_FMT_YUYV, WIDTH, HEIGHT, FPS, 1);
    videoCapture = V4l2Capture::create(param, V4l2Access::IOTYPE_MMAP);
    videoCapture->setExposure(500);
    runFlag = true;
    while(runFlag){
        std::vector<cv::Point2f> corners;
        try{
            if(videoCapture->isReadable(&timeout) == 1 ){
                size_t nb = videoCapture->read(buffer, bufferSize);
                mtx.lock();
                cvtYUV2RGB((unsigned char *)buffer, img, HEIGHT, WIDTH);
                mtx.unlock();

//                if(img.data != nullptr){
//                    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
//                    img_c = img.clone();
//                    int ret = cv::findChessboardCorners(img, cv::Size(10,11), corners);	//time-sonsuming operation
//                    if(ret)
//                        cv::drawChessboardCorners(img_c, cv::Size(10,11), corners, ret);
//                    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
//                    std::chrono::duration<double> time_used = std::chrono::duration_cast<std::chrono::duration<double> >(t2-t1);
//                    std::cout<<"time elapsed: "<<time_used.count()<<"s"<<std::endl;
//                }
            }
        }catch(...){
            std::cout<<"cant read!"<<std::endl;
        }
        emit send();
    }
}

void RechargeCam::cvtYUV2RGB(unsigned char* yuv_buffer, cv::Mat& image, int height, int width){
    int length_ = height * width * 2;
    int rgb_buffer_pointer = 0;
    float y0, u, y1, v;
    // image.create(480, 640, CV_8UC3);

    for(int i =0; i < length_; i += 4){
        y0 = yuv_buffer[i + 0];
        u  = yuv_buffer[i + 1];
        y1 = yuv_buffer[i + 2];
        v  = yuv_buffer[i + 3];

        image.data[rgb_buffer_pointer++] = (y0 + (1.370705 * (v - 128)));
        image.data[rgb_buffer_pointer++] = (y0 - (0.698001 * (v - 128)) - (0.337633 * (u - 128)));
        image.data[rgb_buffer_pointer++] = (y0 + (1.732446 * (u - 128)));
        image.data[rgb_buffer_pointer++] = (y1 + (1.370705 * (v - 128)));
        image.data[rgb_buffer_pointer++] = (y1 - (0.698001 * (v - 128)) - (0.337633 * (u - 128)));
        image.data[rgb_buffer_pointer++] = (y1 + (1.732446 * (u - 128)));
    }
}

void RechargeCam::saveImg(){
    static int suffix = 0;
    mtx.lock();
    cv::imwrite(QString("imgRcg/rcg%1.jpg").arg(suffix++).toStdString(), img);
    mtx.unlock();
}

cv::Mat RechargeCam::getImg(bool hasCorner){
    if(!hasCorner)
        return img;
    else
        return img;
//        return img_c;
}
