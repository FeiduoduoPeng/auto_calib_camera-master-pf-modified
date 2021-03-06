#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "thread.h"
#include <iostream>
#include <string>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QSound>
#include "QStandardItemModel"

#include "cedriver_cam.h"
#include "cedriver_config.h"
#include "mycetool_calib_stereo_capture_img.h"
#include "rechargecam.h"

#include <pcl/point_cloud.h>
#include <pcl/ModelCoefficients.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>

#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define REC_WIDTH 5
#define REC_HEIGHT 5

using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    int read_all_file_name(string path,vector<string> &Files);
    bool executeCMD(const char *cmd);
    void Read_Data();
    bool incre_record(int i, int j);
    bool caculate_all_record(int img_type);
    bool SaveStringList(const string outputname, vector<string>& l);

    bool saveBinoImage(const lrImg &plr);
    bool myWriteXML(int total_img, std::string s="stereo_calib.xml");
    bool myBinocularCalibration();
    double plane_fitting(std::string left_img_file, std::string right_img_file);
    cv::Point2d pixel2cam(const cv::Point2d &p, const cv::Mat &K);
    void updateBinoFileNum();

    ~MainWindow();

public slots:
    void accept(QString msg);
    void monoaccept();
    void rcgaccept();
    void fisheyecalibStatus(int);
    void binoCalibStatus(int exitCode, QProcess::ExitStatus exitStatus);
    void rgbdCalibStatus(int, QProcess::ExitStatus);
    void rcgCalibStatus(int, QProcess::ExitStatus);


private slots:

    void on_pushButton_open_camera_clicked();
    void on_pushButton_save_image_clicked();
    void on_pushButton_open_serial_clicked();
    void on_pushButton_read_image_list_clicked();
    void on_pushButton_clean_clicked();
    void on_pushButton_clicked();
    void on_pushButton_start_calib_clicked();
    void handleTimeout();
    void binoTimerHandler();
    void checkHandler();
    void servoMoveForward(void);
    void servoMoveBackward(void);
    void servoStop(void);
    void servoInitStop(void);
    void on_pushButton_read_lists_clicked();
    void on_pushButton_save_lists_clicked();
    void on_Slider_y_valueChanged(int value);
    void on_Slider_x_valueChanged(int value);
    void on_radioButton_list1_clicked();
    void on_radioButton_list2_clicked();
    void on_radioButton_list3_clicked();
    void on_radioButton_IR_toggled(bool checked);
    void on_radioButton_color_toggled(bool checked);
    void on_pushButton_clear_record_clicked();
    void on_radioButton_IR_calib_clicked();
    void on_tabWidget_tabBarClicked(int index);
    void on_tabWidget_currentChanged(int index);
    void on_pushButton_open_bino_clicked();
    void on_pushButton_save_bino_clicked();
    void on_pushButton_clear_bino_clicked();
    void on_pushButton_start_calib_bino_clicked();
    void on_pushButton_chk_crn_distr_clicked();
    void on_pushButton_show_rectified_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_init_clicked();
    void on_pushButton_move_forward_clicked();
    void on_pushButton_backward_clicked();

private:
    Ui::MainWindow *ui;
    Thread thread;
    RechargeCam *rechargecam;
    monoThread monotrd;
    fisheyeCalib fisheyecalib;
    QTimer *binoTimer;
    QTimer *servoTimer;
    QTimer *servoInitTimer;
    string depth_calib_file_name;
    string color_calib_file_name;
    string depth_image_list_file_name;
    string color_image_list_file_name;
    string IR_image_list_file_name;
    QProcess *proc = new QProcess;

    lrImg plr;
    bool mySaveFlag=false;
    int frames = 0;
    bool monoSave = false;
    int run_step ;
    int list_num = 0;
    QStandardItemModel* model = new QStandardItemModel();
    QStandardItemModel* model2 = new QStandardItemModel();

    /*for rectify*/
    cv::FileStorage fs;
//    cv::FileStorage fs_ex;
    cv::Mat M1,D1,M2,D2;
    cv::Mat R,T,R1,P1,R2,P2,Q;
    bool enable_rectify = false;
    bool matrix_rdy = false;
    int servoDelay = 13000;
    QTimer *m_pTimer;
    int CheckDurationMs = 400;
    int position = 0;
    QTimer *checkTimer;

    std::string binoExeString;
    std::string rgbdfile_tmp_ir;
    std::string rgbdfile_tmp_color;
    std::string binofile_tmp_i;
    std::string binofile_tmp_e;
    std::string monofile_tmp;
};

#endif // MAINWINDOW_H
