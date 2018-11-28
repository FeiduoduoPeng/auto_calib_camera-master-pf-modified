
#ifndef THREAD_H

#define THREAD_H

#include<QThread>

#include<QString>

#include <QMutex>
#include "OpenNI.h"
#include <opencv2/core/core.hpp>
class Thread : public QThread

{

    Q_OBJECT

public:

    Thread();

    virtual void run();

    void stop();
    void save_image();

    cv::Mat get_color_img();
    cv::Mat get_ir_img();
    cv::Mat get_depth_img();
    void SetImageSave();
    void SetImageShowIR();
    void SetImageShowColor();
signals:

    void send(QString msg);

private:


    cv::Mat cImageBGR;
    cv::Mat cImageIR;
    cv::Mat mScaledDepth;
    volatile  int run_flag ;
    volatile  int save_image_flag ;
    volatile  int show_channel;
    volatile  int is_change_to_color;
    volatile  int is_change_to_ir;
    QMutex mutex;
};



#endif // THREAD_H
