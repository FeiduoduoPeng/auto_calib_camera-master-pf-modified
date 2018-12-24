#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <iostream>
#include <signal.h>
#include <iomanip>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"

#include "cedriver_usb.h"
#include "cedriver_cam.h"
#include "cedriver_imu.h"
#include "cedriver_config.h"
#include "cedriver_global_config.h"
#include "celib_img_process.h"

#include "mycetool_calib_stereo_capture_img.h"

using namespace cv;
using namespace std;

std::mutex pfmutex;
pthread_t ce_cam_capture_calib_thread;
bool ce_cam_capture_calib_stop_run = false;


bool g_bSaveImg = false;

pthread_t ce_cali_catch_enter_key_thread;
bool ce_cali_catch_enter_key_stop_run = false;


extern threadsafe_queue<d1_img_output_pkg *> img_pkg_list_d1;


static void* ce_cali_catch_enter_key(void *)
{
    char c;
	while (!ce_cali_catch_enter_key_stop_run)
	{
        c = cin.get();
		if ('\n' == c)
		{
            g_bSaveImg = true;
			cout<<"catch enter key!"<<endl;
		}
		else
		{
			cout<<c;
		}

	}
    ce_cali_catch_enter_key_thread = 0;
    pthread_exit(NULL);
}


int ce_cali_catch_enter_key_init()
{
    int temp = pthread_create(&ce_cali_catch_enter_key_thread, NULL, ce_cali_catch_enter_key, NULL);
    if(temp)
    {
        printf("Failed to create thread catch enter key \r\n");
        return CE_ERROR;
    }
    return SUCCESS;
}


void ce_cali_catch_enter_key_close()
{
    ce_cali_catch_enter_key_stop_run = true;
    if(ce_cali_catch_enter_key_thread != 0)
    {
        pthread_join(ce_cali_catch_enter_key_thread,NULL);
    }

    printf("cali capture and save success!!! \r\n");
}




static void* ce_cam_capture_calib(lrImg &plr)
{
    ce_config_get_cf_cam_rectify_force_off();

    Size board_size = Size(11,10);

    cv::Mat img_left(cv::Size(ce_config_get_cf_img_width(),ce_config_get_cf_img_height()),CV_8UC1);
    cv::Mat img_right(cv::Size(ce_config_get_cf_img_width(),ce_config_get_cf_img_height()),CV_8UC1);
    cv::Mat img_left_corners(cv::Size(ce_config_get_cf_img_width(),ce_config_get_cf_img_height()),CV_8UC1);
    cv::Mat img_right_corners(cv::Size(ce_config_get_cf_img_width(),ce_config_get_cf_img_height()),CV_8UC1);

    Mat result;
    int cnt_save = 0;
    vector<Point2f> corners_left;
    vector<Point2f> corners_right;

    d1_img_output_pkg *img_lr_pkg;

    while(!ce_cam_capture_calib_stop_run)
    {
        if(!img_pkg_list_d1.try_pop(img_lr_pkg))
        {
            usleep(50000);	//sleep 50 ms
            continue;
        }

        if(img_pkg_list_d1.size() != 0)
        {
            delete img_lr_pkg->left_img;
            delete img_lr_pkg->right_img;
            delete img_lr_pkg;
            continue;
        }


        // get the image
        memcpy(img_left.data, img_lr_pkg->left_img->data, ce_config_get_cf_img_size());
        memcpy(img_right.data,img_lr_pkg->right_img->data,ce_config_get_cf_img_size());

        //int ret_left = findChessboardCorners(img_left, board_size, corners_left,
        //            CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);/* 提取角点 */

        //cvtColor(img_left, img_left_corners, COLOR_GRAY2BGR);
        //drawChessboardCorners(img_left_corners, board_size, corners_left, ret_left);

        //int ret_right = findChessboardCorners(img_right, board_size, corners_right,
        //            CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);/* 提取角点 */

        //cvtColor(img_right, img_right_corners, COLOR_GRAY2BGR);
        //drawChessboardCorners(img_right_corners, board_size, corners_right, ret_right);

        pfmutex.lock();
        plr.left = img_left.clone();
        plr.right = img_right.clone();
        pfmutex.unlock();

        delete img_lr_pkg->left_img;
        delete img_lr_pkg->right_img;
        delete img_lr_pkg;
    }
    ce_cam_capture_calib_thread = 0;
    pthread_exit(NULL);
}

int ce_cam_capture_calib_init(lrImg &plr)
{
    //int temp = pthread_create(&ce_cam_capture_calib_thread, NULL, ce_cam_capture_calib, NULL);
    //if(temp)
    //{
    //    printf("celog: Failed to create thread show image \r\n");
    //    return ERROR;

    //}
    ce_cam_capture_calib_stop_run = false;
    std::thread mythread(ce_cam_capture_calib,std::ref(plr));
    mythread.detach();

    return SUCCESS;
}

void ce_cam_capture_calib_close()
{
    ce_cam_capture_calib_stop_run = true;
    if(ce_cam_capture_calib_thread != 0)
    {
        pthread_join(ce_cam_capture_calib_thread,NULL);
    }

}


















