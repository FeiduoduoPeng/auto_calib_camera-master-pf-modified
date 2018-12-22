#ifndef THREAD_H
#define THREAD_H

#define MONO_CHESSBOARD

#include<QThread>
#include<QString>
#include <QMutex>
#include <QSound>
#include <QMessageBox>
#include "OpenNI.h"
#include <opencv2/core/core.hpp>
#include "cedriver_cam.h"
#include "cedriver_config.h"
#include "fisheye_calibrate.h"

class Thread : public QThread{
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


class monoThread : public QThread{
    Q_OBJECT
public:
    monoThread(){
    }
    virtual void run(){
        ce_config_load_settings("./config/cecfg_std.txt");
        int r = ce_cams1_capture_init();
        if(r < 0){
            printf("celog: cam capture error \r\n");
        }
        else{
            printf("celog: cam capture success \r\n");

            r = pf_ce_cams1_preprocess_init(pf_img);
            if(r < 0){
                printf("celog: cam preprocess error \r\n");
            }
            else{
                printf("celog: cam preprocess sucess \r\n");
            }
        }
        while(mono_run_flag){
            std::vector<cv::Point2f> corners;
            if(pf_img.data != nullptr){

#ifdef MONO_CHESSBOARD
                /****enable chessboard corner display function*******/
                int ret = cv::findChessboardCorners(pf_img, cv::Size(10,11), corners);	//time-sonsuming operation
                cv::cvtColor(pf_img, pf_img_corner, cv::COLOR_GRAY2BGR);
                if(ret)
                    cv::drawChessboardCorners(pf_img_corner, cv::Size(10,11), corners, ret);
#else
                pf_img_corner = pf_img.clone();
                msleep(20);
#endif
                emit send();
            }
        }
    }

    void stop(){
        ce_cams1_capture_close();
        ce_cams1_preprocess_close();
//        mtx.unlock();
        mono_run_flag = false;
    }

    cv::Mat getMonoImg(){
        mtx.lock();
        cv::Mat temp_ = pf_img;
        mtx.unlock();
        return temp_;
    }
    cv::Mat getMonoImgCorner(){
        return pf_img_corner;
    }

    void SaveImage(){
        static int suffix = 0;
        char imgName[100];
        sprintf(imgName,"Mono/mono%d.jpg",suffix++);
        mtx.lock();
        cv::imwrite(imgName, pf_img);
        mtx.unlock();
    }
    void monoStartPre(void){
        mono_run_flag = true;
    }

signals:
    void send();

private:
    cv::Mat  pf_img = cv::Mat(cv::Size(ce_config_get_cf_img_width(),ce_config_get_cf_img_height()),CV_8UC1);
    cv::Mat  pf_img_corner = cv::Mat(cv::Size(ce_config_get_cf_img_width(),ce_config_get_cf_img_height()),CV_8UC3);
    QMutex mtx;
    bool mono_run_flag=true;
};


//**this class is to operate the time-consuming fisheye calibration**//
class fisheyeCalib: public QThread{
    Q_OBJECT
public:
    fisheyeCalib(){
        imgPath = std::string("./Mono");
        xxFile = std::string("./CalibrationParam/mono_xxtrinsics.yml");
    }

    virtual void run(){
        int ill_img = FisheyeCalibrate(imgPath, xxFile);
        if(ill_img == 0){
            emit send(0);
        }else{
            std::cout<<"mono fail image: "<<ill_img<<std::endl;
            emit send(ill_img);
        }
        sleep(1);
    }

    void stop(){
    }
    void setPathFile(std::string path, std::string xxfile){
        imgPath = path;
        xxFile = xxfile;
    }

signals:
    void send(int);

private:
    std::string imgPath;
    std::string xxFile;
};

#endif // THREAD_H
