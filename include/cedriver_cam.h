#ifndef CEDRIVER_CAM_H
#define CEDRIVER_CAM_H

#include "threadsafe_queue.h"
#include "cedriver_global_config.h"
#include "opencv2/opencv.hpp"
#include "global.h"
#include <thread>
#include <mutex>

struct img_pkg
{
    unsigned char data[IMG_BUF_SIZE_WVGA];
    double timestamp;
};

struct d1_img_output_pkg
{
    img_pkg *left_img;
    img_pkg *right_img;
};

struct lrImg{
    cv::Mat left;
    cv::Mat right;
};

int ce_cam_capture_init();
void ce_cam_capture_close();
int ce_cam_showimg_init(lrImg &plr);
void ce_cam_showimg_close();
int ce_cam_preprocess_init();
void ce_cam_preprocess_close();


#endif
