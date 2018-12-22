#ifndef CEDRIVER_CAM_H
#define CEDRIVER_CAM_H
#include <algorithm>
#include <fstream>

#include <vector>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <string>

#include "cedriver_usb.h"
#include "cedriver_config.h"

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


/*******************monocular function*************************/
int ce_cams1_capture_init();
void ce_cams1_capture_close();
int ce_cams1_preprocess_init();
int pf_ce_cams1_preprocess_init(cv::Mat &ref_img);
void ce_cams1_preprocess_close();


/*******************xxnocular id*************************/
void ce_cams1_set_handle(libusb_device_handle *caml_handle_,
                         libusb_device_handle *camr_handle_,
                         libusb_device_handle *cam0_handle_,
                         libusb_device_handle *cam1_handle_,
                         libusb_device_handle *cam2_handle_);

std::string ce_cam_get_id(int cam_num);                 // 获得双目设备的 id
std::string ce_cams1_get_id(int cam_num);               // 获取单目设备的 id
int ce_cam_set_id(int cam_num, int serial);     // 设置双目设备的 id
int ce_cams1_set_id(int cam_num, int serial);   // 设置单目设备的　id

#endif
