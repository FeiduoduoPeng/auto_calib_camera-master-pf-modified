#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <QFile>
#include <QTableWidgetItem>
#include "QStandardItemModel"
#include "communication.h"
#include <QMessageBox>
#include <QSettings>
#include <QDebug>
#include <stdint.h>
#include <bits/stdc++.h>
#include <vector>
#include "dirent.h"
#include <QDebug>
#include <QTimer>

#include <sstream>
#include "calib3d.hpp"
#include "devices_id.h"

Ui::MainWindow *my_ui;
extern std::mutex pfmutex;

using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    my_ui=ui;

    binoTimer =  new QTimer(this);
    servoTimer = new QTimer(this);
    servoInitTimer = new QTimer(this);
    checkTimer = new QTimer(this);
    rechargecam = new RechargeCam;
    color_image_list_file_name = "color_image_list_file.yaml";
    depth_image_list_file_name = "depth_image_list_file.yaml";

    /*initialize the frames*/
    QDir dir_l("./imgL");
    QStringList filter;
    filter<<"*.jpg";
    dir_l.setNameFilters(filter);
    QFileInfoList fileinfo = dir_l.entryInfoList(filter);
    frames = fileinfo.count() ;

    //查找可用的串口
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()){
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite)){
            ui->PortBox->addItem(serial.portName());
            serial.close();
        }
    }
    ui->BaudBox->setCurrentIndex(0);
    ui->pushButton_open_serial->setText(tr("打开串口"));
    ui->pushButton_open_camera->setText(tr("open_camera"));

    QObject::connect(rechargecam, SIGNAL(send()), this, SLOT(rcgaccept()), Qt::BlockingQueuedConnection);
    QObject::connect(&thread, SIGNAL(send(QString)), this, SLOT(accept(QString)), Qt::BlockingQueuedConnection);
    QObject::connect(&fisheyecalib, SIGNAL(send(int)), this, SLOT(fisheyecalibStatus(int)) );
    QObject::connect(&monotrd, SIGNAL(send()), this, SLOT(monoaccept()), Qt::BlockingQueuedConnection);
    QObject::connect(binoTimer, SIGNAL(timeout()), this, SLOT(binoTimerHandler()));
    QObject::connect(servoTimer, SIGNAL(timeout()), this, SLOT(servoStop()));
    QObject::connect(servoInitTimer, SIGNAL(timeout()), this, SLOT(servoInitStop()));
    QObject::connect(checkTimer, SIGNAL(timeout()), this, SLOT(checkHandler()) );

    QStringList labels = QObject::trUtf8("X,Y").simplified().split(",");
    model->setHorizontalHeaderLabels(labels);
    model->setColumnCount(2);
    model->setRowCount(100); //行
    ui->tableView->setModel(model);
    ui->tableView->show();
    ui->tableView->model()->index(1,2);
    on_pushButton_read_lists_clicked();
   // imageLable = new QLable(this);

    model2->setColumnCount(REC_WIDTH);
    model2->setRowCount(REC_HEIGHT);
    for(int i=0; i<REC_WIDTH; i++){
        for(int j=0; j<REC_HEIGHT; j++){
            QStandardItem *itemId = new QStandardItem(QString::number(0));
            model2->setItem(i,j,itemId);
        }
    }
    ui->tableView_2->setModel(model2);
    for(int i=0; i<REC_WIDTH; ++i){
        ui->tableView_2->setColumnWidth(i,ui->tableView_2->width()/REC_WIDTH-1);
    }
    for(int i=0; i<REC_HEIGHT; ++i){
        ui->tableView_2->setRowHeight(i,ui->tableView_2->height()/REC_HEIGHT-1);
    }
    ui->tableView_2->show();
    myWriteXML(100);

    ui->lineEdit_RcgID->setValidator( new QIntValidator(0, 9999, this) );

    ui->pushButton_open_bino->setVisible(false);
    ui->pushButton_save_bino->setVisible(false);
    ui->pushButton_start_calib_bino->setVisible(false);
    ui->pushButton_clean->setVisible(false);
    ui->pushButton_save_image->setVisible(false);

    checkTimer->start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateBinoFileNum(){
    QDir dir_l("./imgL");
    QStringList filter;
    filter<<"*.jpg";
    dir_l.setNameFilters(filter);
    QFileInfoList fileinfo = dir_l.entryInfoList(filter);
    frames = fileinfo.count() ;
}

bool MainWindow::executeCMD(const char *cmd){
    FILE *ptr;
    char buf_ps[1024];
    char ps[1024]={0};
    strcpy(ps, cmd);
    if((ptr=popen(ps, "r"))!=NULL){
        while(fgets(buf_ps, 1024, ptr)!=NULL)
        {}
        pclose(ptr);
        ptr = NULL;
        return true;
    }else{
        return false;
    }
}

void MainWindow::binoCalibStatus(int exitCode, QProcess::ExitStatus exitStatus){
    string camera_id = binofile_tmp_e.substr( binofile_tmp_e.find_last_of("/")+1 );
    if(exitCode == 0){
        FileStorage fs(binofile_tmp_e, FileStorage::READ);
        cv::Mat T;
        if(fs.isOpened()){
            fs["T"] >> T;
        }
        double X = abs(T.at<double>(0,0));
        if(X>95.0 && X<105.0 ){		//双目的结构参数沿X方向是100mm左右
            QMessageBox::about(this, camera_id.c_str(), string("成功").c_str());
            return;
        }else{
            QMessageBox::about(this, camera_id.c_str(), string("外参失败").c_str());
            return;
        }
    }else{
        if(exitCode > 0){
            std::string content;
            content = "删除第"+std::to_string(exitCode)+"张图，并按“单校正图像”重试";
            QMessageBox::about(this,tr("标定失败"), content.c_str());        }
    }
}

void MainWindow::fisheyecalibStatus(int s){
    std::string camera_id = monofile_tmp.substr( monofile_tmp.find_last_of("/")+1 );
    if(s == 0){
        QMessageBox::about(this, camera_id.c_str(), tr("标定成功"));
    }else if(s == -1){
        QMessageBox::about(this, camera_id.c_str(), tr("标定失败"));
    }else{
        std::string content;
        content = "删除第"+std::to_string(s)+"张图，并按“单校正图像”重试";
        std::cout<<"err img: "<<s<<std::endl;
        QMessageBox::about(this,tr("标定失败"), content.c_str());
    }
}

void MainWindow::rgbdCalibStatus(int exitCode, QProcess::ExitStatus exitStatus){
    std::string camera_id = rgbdfile_tmp_ir.substr( rgbdfile_tmp_ir.find_last_of("/")+1 );
    if(exitCode == 0){
        std::cout<<rgbdfile_tmp_ir<<std::endl;
        cv::FileStorage fs(rgbdfile_tmp_ir, FileStorage::READ);
        if(!fs.isOpened()){
            QMessageBox::about(this, camera_id.c_str(), QString("标定失败") );
            return;
        }
        double rms;
        fs["avg_reprojection_error"] >> rms;
        if(rms<1.0)
            QMessageBox::about(this, camera_id.c_str(), QString("标定成功") );
        else{
            QMessageBox::about(this, camera_id.c_str(), QString("rms fail") );
        }
    }
}
void MainWindow::rcgCalibStatus(int exitCode, QProcess::ExitStatus exitStatus){
//    QMessageBox::about(this, "MESSAGE", QString("exitCode: %1").arg(exitCode) );
    int rcgid = ui->lineEdit_RcgID->text().toInt();
    if(exitCode == 0){
        std::cout<<rgbdfile_tmp_ir<<std::endl;
        cv::FileStorage fs("./CalibrationParam/Rcg"+std::to_string(rcgid)+".yml", FileStorage::READ);
        if(!fs.isOpened()){
            QMessageBox::about(this, QString::number(rcgid), QString("标定失败") );
            return;
        }
        double rms;
        fs["avg_reprojection_error"] >> rms;
        if(rms<1.0){
            QMessageBox::about(this, QString::number(rcgid), QString("标定成功") );
//            int temp = ui->lineEdit_RcgID->text().toInt() + 1;
            ui->lineEdit_RcgID->setText(QString::number(rcgid+1));
        }else{
            QMessageBox::about(this, QString::number(rcgid), QString("rms fail") );
        }
    }
//    std::cout<<rgbdfile_tmp_ir<<std::endl;
//    cv::FileStorage fs(rgbdfile_tmp_ir, FileStorage::READ);
//    double rms;
//    fs["avg_reprojection_error"] >> rms;
//    if(rms<1.0)
//        QMessageBox::about(this, camera_id.c_str(), QString("标定成功") );
//    else{
//        QMessageBox::about(this, camera_id.c_str(), QString("rms fail") );
//    }
}

bool loadCameraParams(string file_name,Mat &cameraMatrix, Mat &distCoeffs){
    FileStorage fs(file_name, FileStorage::READ);//这个名字就是你之前校正得到的yml文件
    if(fs.isOpened()){
        fs["camera_matrix"] >> cameraMatrix;
        fs["distortion_coefficients"] >> distCoeffs;
        return true;
    }else{
        return false;
    }
}

cv::Point2d MainWindow::pixel2cam(const cv::Point2d &p, const cv::Mat &K){
    return cv::Point2d(
                (p.x - K.at<double>(0,2)) / K.at<double>(0,0),
                (p.y - K.at<double>(1,2)) / K.at<double>(1,1) );
}

/**
* @input, image;
* @output, error between fitting-plane and original points;
*/
double MainWindow::plane_fitting(std::string left_img_file, std::string right_img_file){
    cv::Mat left_img =	cv::imread(left_img_file);
    cv::Mat right_img =	cv::imread(right_img_file);

    //rectify the image
    cv::Mat l_remapx, l_remapy, r_remapx, r_remapy;
    cv::Mat img_left_remap, img_right_remap;
    cv::fisheye::initUndistortRectifyMap(M1, D1, R1, P1, left_img.size(), CV_16SC2, l_remapx, l_remapy);
    cv::fisheye::initUndistortRectifyMap(M2, D2, R2, P2, right_img.size(), CV_16SC2, r_remapx, r_remapy);
    cv::remap(left_img, img_left_remap, l_remapx, l_remapy, cv::INTER_LINEAR);
    cv::remap(right_img, img_right_remap, r_remapx, r_remapy, cv::INTER_LINEAR);

    //find chessboardcorner;
    //std::vector<cv::Point2f> corners_left, corners_right;
    std::vector<cv::Point2d> corners_left, corners_right;
    bool found = false;
    found = cv::findChessboardCorners(img_left_remap,cv::Size(10,11), corners_left);
    found = found && cv::findChessboardCorners(img_right_remap,cv::Size(10,11), corners_right);
    if(found){
        assert(corners_left.size() == corners_right.size());
    }else{
        return 0;
    }
    for(int i=0; i<corners_left.size(); ++i){
        corners_left[i] = pixel2cam(corners_left[i], M1);
        corners_right[i] = pixel2cam(corners_right[i], M2);
    }

    cv::Mat myT1 = (cv::Mat_<double>(3,4) <<
                    1,0,0,0,
                    0,1,0,0,
                    0,0,1,0);
    cv::Mat myT2;
    //cv::Mat myT2 = (cv::Mat_<double>(3,4) <<
    //                R.at<double>(0,0), R.at<double>(0,1), R.at<double>(0,2),  T.at<double>(0,0),
    //                R.at<double>(1,0), R.at<double>(1,1), R.at<double>(1,2),  T.at<double>(1,0),
    //                R.at<double>(2,0), R.at<double>(2,1), R.at<double>(2,2),  T.at<double>(2,0) );
    cv::hconcat(R,T,myT2);
    assert(myT1.cols==myT2.cols && myT1.rows==myT2.rows);
    cv::Mat pts_4d;
    cv::triangulatePoints(myT1, myT2, corners_left, corners_right, pts_4d);

    //calculate the 3d points, and create PointCloud
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    cloud->width = 10;
    cloud->height =11;
    cloud->points.resize(cloud->width * cloud->height);
    for(int i=0; i<pts_4d.cols; ++i){
        cv::Mat x = pts_4d.col(i);
        x /= x.at<double>(3,0);
        cloud->points[i].x = x.at<double>(0,0);
        cloud->points[i].y = x.at<double>(1,0);
        cloud->points[i].z = x.at<double>(2,0);
    }
    pcl::io::savePCDFileBinary("map.pcd", *cloud);

    /***************fitting*******************/
    pcl::ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients);
    pcl::PointIndices::Ptr inliers (new pcl::PointIndices);
    // Create the segmentation object
    pcl::SACSegmentation<pcl::PointXYZ> seg;
    // Optional
    seg.setOptimizeCoefficients (true);
    // Mandatory
    seg.setModelType (pcl::SACMODEL_PLANE);
    seg.setMethodType (pcl::SAC_RANSAC);
    seg.setDistanceThreshold (5);
    seg.setInputCloud (cloud);
    seg.segment (*inliers, *coefficients);

    if (inliers->indices.size () == 0)
    {
      PCL_ERROR ("Could not estimate a planar model for the given dataset.");
      return (-1);
    }

    std::cout << "Model coefficients: " << coefficients->values[0] << " "
                                        << coefficients->values[1] << " "
                                        << coefficients->values[2] << " "
                                        << coefficients->values[3] << std::endl;
    std::cout << "Model inliers: " << inliers->indices.size () << std::endl;

    //calculate error;
    double estimateDist =  coefficients->values[3] /
            sqrt(
                pow(coefficients->values[0],2) +
                pow(coefficients->values[1],2) +
                pow(coefficients->values[2],2)
            );
    std::cout<<"distance: "<< estimateDist <<std::endl;

    double plane_fit_error = 0;
    for(int i=0; i<pts_4d.cols; ++i){
        plane_fit_error += (
                    coefficients->values[0] * cloud->points[i].x +
                    coefficients->values[1] * cloud->points[i].y +
                    coefficients->values[2] * cloud->points[i].z +
                    coefficients->values[3]
                    ) /
                    sqrt(
                        pow(coefficients->values[0],2) +
                        pow(coefficients->values[1],2) +
                        pow(coefficients->values[2],2)
                    );
    }
    plane_fit_error /= pts_4d.cols;
    plane_fit_error = abs(plane_fit_error );
    char num[64];
    sprintf(num, "%f", plane_fit_error);
    QMessageBox::about(this,tr("Fit-Plane Error"), string(num).c_str());
    //std::cout<<"Plane-fitting Average Error: "<< plane_fit_error <<std::endl;

    return 0;
}
Mat calibrator(string calib_file,Mat view)//需要校正处理的图片
{
    vector<string> imageList;
    static bool bLoadCameraParams = false;
    static Mat cameraMatrix, distCoeffs, map1, map2;
    Mat rview;
    Size imageSize, newImageSize;

    if (!view.data)
     return Mat();

    imageSize.width = view.cols;
    imageSize.height = view.rows;

    newImageSize.width = imageSize.width;
    newImageSize.height = imageSize.height;

    if (bLoadCameraParams == false)
    {
        if(loadCameraParams(calib_file,cameraMatrix, distCoeffs)==true)
        bLoadCameraParams = true;
        initUndistortRectifyMap(cameraMatrix, distCoeffs, Mat(),
        getOptimalNewCameraMatrix(cameraMatrix, distCoeffs, imageSize, 1, newImageSize, 0), newImageSize, CV_16SC2, map1, map2);
    }

    //undistort( view, rview, cameraMatrix, distCoeffs, cameraMatrix );
    remap(view, rview, map1, map2, INTER_LINEAR);

    //imshow("左图", rview);
    //int c = 0xff & waitKey();

    rview.copyTo(view);

    return view;
}
//读取接收到的数据
void MainWindow::Read_Data()
{

    char len=0;
    char buf[500];
    QString textbuf;
    len=serial->read(buf,500);
    if(len==(-1))
    {
        qDebug() << tr("接收串口错误!");
        return;
    }
    for(char i=0;i<len;i++)
    {
        Motor_DT_Data_Receive_Prepare((unsigned char )buf[i]);
    }
}

bool MainWindow::incre_record(int i, int j){
    if(i<0 || j<0 || i>=REC_WIDTH || j>REC_HEIGHT)
        return false;

    int n = ui->tableView_2->model()->index(i,j).data().toInt()+1;
    QStandardItem *item = new QStandardItem(QString::number(n));
    model2->setItem(i,j,item);
    return true;
}

bool MainWindow::caculate_all_record(int img_type){
    std::vector<string> Files;
    switch(img_type){
        case 1: read_all_file_name("./color_image/",Files); break;
        case 2: read_all_file_name("./IR_image/",Files); break;
        default: return false;
    }
    //std::for_each(Files.begin(), Files.end(),[](std::string s){std::cout<<s<<std::endl;});
    for(auto img_file:Files){
        std::vector<cv::Point2f> ptCorners;
        cv::Mat img_origin = cv::imread(img_file);
        cv::Mat img;
        cv::transpose(img_origin, img);
        cv::findChessboardCorners(
                    img,cv::Size(
                            ui->spinBox_grid_width->value(),
                            ui->spinBox_grid_height->value()),
                    ptCorners, 3 );

        int grid_cols = img.cols/REC_WIDTH;
        int grid_rows = img.rows/REC_HEIGHT;
        for(auto pt:ptCorners){
            incre_record( pt.x / grid_cols, pt.y / grid_rows);
        }
    }
}

QImage  Mat2QImage(cv::Mat cvImg)
{
    QImage qImg;
    if(cvImg.channels()==3)                             //3 channels color image
    {

        static cv::Mat cv_temp;
        cv::cvtColor(cvImg,cv_temp,CV_BGR2RGB);
        qImg =QImage((const unsigned char*)(cv_temp.data),
                    cv_temp.cols, cv_temp.rows,
                    cv_temp.cols*cv_temp.channels(),
                    QImage::Format_RGB888);
    }
    else if(cvImg.channels()==1)                    //grayscale image
    {
        qImg =QImage((const unsigned char*)(cvImg.data),
                    cvImg.cols,cvImg.rows,
                    cvImg.cols*cvImg.channels(),
                    QImage::Format_Indexed8);
    }
    else
    {
        qImg =QImage((const unsigned char*)(cvImg.data),
                    cvImg.cols,cvImg.rows,
                    cvImg.cols*cvImg.channels(),
                    QImage::Format_RGB888);
    }
    return qImg;
}

void MainWindow::accept(QString msg)
{
    QImage image;
    const int board_w = ui->spinBox_grid_width->value();
    const int board_h = ui->spinBox_grid_height->value();
    //cv::imshow( "Depth Image", thread.get_depth_img() );
    // 然后显示彩色图像
    //cv::imshow( "Color Image", thread.get_color_img() );
    if(ui->radioButton_color->isChecked())
    {
        thread.SetImageShowColor();
        cv::Mat imgShow = thread.get_color_img().clone();
        if(ui->checkBox_show_check->isChecked())
        {
            if(imgShow.channels() < 3)
            {
                cv::cvtColor(imgShow, imgShow, CV_GRAY2RGB);
            }
            cv::Mat imggray = thread.get_color_img().clone();
            if(imggray.channels() == 3)
            {
                cv::cvtColor(imggray, imggray, CV_RGB2GRAY);
            }

            cv::Size chessBoardSize = cv::Size(board_w, board_h);
            IplImage tempgray = imggray;
            bool findchessboard = cvCheckChessboard(&tempgray, chessBoardSize);
            if(findchessboard)
            {
                std::vector<cv::Point2f> tempCorners;
                bool find_corners_result = cv::findChessboardCorners(imggray, chessBoardSize, tempCorners, 3);
                if(find_corners_result)
                {
                    cv::drawChessboardCorners(imgShow, chessBoardSize, tempCorners, find_corners_result);
                }
            }
        }
        image = Mat2QImage(imgShow);
    }
    else if(ui->radioButton_IR->isChecked())
    {
        thread.SetImageShowIR();
        cv::Mat imgShow = thread.get_ir_img();

        if(ui->checkBox_show_check->isChecked())
        {
            if(imgShow.channels() < 3)
            {
                cv::cvtColor(imgShow, imgShow, CV_GRAY2RGB);
            }
            cv::Mat imggray = thread.get_ir_img().clone();
            if(imggray.channels() == 3)
            {
                cv::cvtColor(imggray, imggray, CV_RGB2GRAY);
            }

            cv::Size chessBoardSize = cv::Size(board_w, board_h);
            IplImage tempgray = imggray;
            bool findchessboard = cvCheckChessboard(&tempgray, chessBoardSize);
            if(findchessboard)
            {
                std::vector<cv::Point2f> tempCorners;
                bool find_corners_result = cv::findChessboardCorners(imggray, chessBoardSize, tempCorners, 3);
                if(find_corners_result)
                {
                    cv::drawChessboardCorners(imgShow, chessBoardSize, tempCorners, find_corners_result);
                }
            }
        }
        image = Mat2QImage(imgShow);
    }
    else if(ui->radioButton_color_calib->isChecked())
    {
//        thread.SetImageShowColor();
//        image = Mat2QImage(calibrator(color_calib_file_name,thread.get_color_img()));
    }
    else if(ui->radioButton_IR_calib->isChecked())
    {
//        thread.SetImageShowIR();
//        image = Mat2QImage(calibrator(depth_calib_file_name,thread.get_ir_img()));
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::monoaccept(){
    cv::Mat img = monotrd.getMonoImg();
    if(ui->checkBox_show_check->isChecked()){
        cv::Mat img_corner = monotrd.getMonoImgCorner();
        QImage qimg = Mat2QImage(img_corner);
        ui->label->setPixmap(QPixmap::fromImage(qimg));
        return;
    }
    QImage qimg = Mat2QImage(img);
    ui->label->setPixmap(QPixmap::fromImage(qimg));
}

void MainWindow::rcgaccept(){
    cv::Mat img;
    if(ui->checkBox_show_check->isChecked()){
        img = rechargecam->getImg(true);
//        cv::Mat img_corner = monotrd.getMonoImgCorner();
//        QImage qimg = Mat2QImage(img_corner);
//        ui->label->setPixmap(QPixmap::fromImage(qimg));
//        return;
    }else{
        img = rechargecam->getImg(false);
    }
    QImage qimg = Mat2QImage(img);
    ui->label->setPixmap(QPixmap::fromImage(qimg));
}


bool MainWindow::saveBinoImage(const lrImg &plr){
    std::ostringstream ostr_l, ostr_r;
    ostr_l<<"./imgL/"<<"left"<<frames<<".jpg";
    ostr_r<<"./imgR/"<<"right"<<frames<<".jpg";
    cv::imwrite(ostr_l.str(), plr.left);
    cv::imwrite(ostr_r.str(), plr.right);
    frames++;
}

void MainWindow::on_pushButton_open_camera_clicked()
{
    if(ui->pushButton_open_camera->text()==tr("open_camera")){	//open camera
        /*******obtain the camera id*******/
        getDeviceID(rgbdfile_tmp_ir, binofile_tmp_e, monofile_tmp);

        if(binofile_tmp_e != "0"){
            //binofile_tmp_i = "./CalibrationParam/" + binofile_tmp_e + "I.yml";
            binofile_tmp_e = "./CalibrationParam/" + binofile_tmp_e + "0.yml";
            binoExeString = string("./CETOOL_CALI_STEREO_CAL -w=10 -h=11 -s=30 ") +
                            string("-xxtrin=") + binofile_tmp_e + " " +
                            string("stereo_calib.xml");
        }if(monofile_tmp != "0"){
            monofile_tmp = "./CalibrationParam/" + monofile_tmp + ".yml";
            fisheyecalib.setPathFile( string("./Mono"), monofile_tmp);
        }if(rgbdfile_tmp_ir != "0"){
            rgbdfile_tmp_color = "./CalibrationParam/" + rgbdfile_tmp_ir + "C.yml";
            rgbdfile_tmp_ir = "./CalibrationParam/" + rgbdfile_tmp_ir + "R.yml";
            color_calib_file_name = rgbdfile_tmp_color;
            depth_calib_file_name = rgbdfile_tmp_ir;
        }if(binofile_tmp_e=="0" && monofile_tmp=="0" && rgbdfile_tmp_ir=="0" && ui->lineEdit_RcgID->text().isEmpty()){	//TODO:此处打开充电摄像头可以被绕开
            QMessageBox::about(this,tr("Recognize: "), "found no device");
            return;
        }
        /**********obtain end**************/
        ui->lineEdit_RcgID->setDisabled(true);

        if(ui->radioButton_IR_calib->isChecked()){	//monocular camera
            executeCMD("cp monoParam/* .");		//load calib-param
            on_radioButton_list1_clicked();
            monotrd.monoStartPre();
            monotrd.start();
            ui->TabBino->setDisabled(true);
        }else if(ui->radioButton_color_calib->isChecked()){		//binocular camera
            executeCMD("cp binoParam/* .");		//load calib-param
            on_radioButton_list1_clicked();
            CheckDurationMs = 600;
            ce_config_load_settings("./config/cecfg_std.txt");
            int r = ce_cam_capture_init();
            if(r < 0){
                printf("celog: cam capture error \r\n");
            }else{
                printf("celog: cam capture success \r\n");
                r = ce_cam_preprocess_init();
                if(r < 0){
                    printf("celog: cam preprocess error \r\n");
                }else{
                    //ce_cam_showimg_init(plr);
                    ce_cam_capture_calib_init(plr);
                }
            }
            ui->Tab1->setDisabled(true);
            binoTimer->start(100);
        }else if(ui->radioButtonRechargeCamera->isChecked()){	//auto-recharge camera
            executeCMD("cp rcgParam/* .");		//load calib-param
            try{
                rechargecam->start();
            }catch(...){
                QMessageBox::about(this, tr("No Cam: "), "插入自充摄像头");
            }
        }else{
            executeCMD("cp rgbdParam/* .");		//load calib-param
            on_radioButton_list1_clicked();
            ui->TabBino->setDisabled(true);
            thread.start();
        }
        ui->pushButton_open_camera->setText(tr("close_camera"));
        ui->pushButton_start_calib->setDisabled(false);	//you can only auto start after opening camera;
        ui->radioButton_IR_calib->setDisabled(true);
        ui->radioButton_color_calib->setDisabled(true);
        ui->radioButton_color->setDisabled(true);
        ui->radioButton_IR->setDisabled(true);
        ui->radioButtonRechargeCamera->setDisabled(true);
    }else{		//close camera
        ui->pushButton_open_camera->setText(tr("open_camera"));
        if(ui->radioButton_IR_calib->isChecked()){
            monotrd.stop();
        }else if(ui->radioButton_color_calib->isChecked()){		//close binocular camera
            ce_cam_capture_close();
            ce_cam_preprocess_close();
            ce_cam_capture_calib_close();
            binoTimer->stop();
        }else if(ui->radioButtonRechargeCamera->isChecked()){		//close auto-recharge camera
            rechargecam->stop();
        }else{
            thread.stop();
        }
        ui->TabBino->setDisabled(false);
        ui->Tab1->setDisabled(false);
        ui->radioButton_IR_calib->setDisabled(false);
        ui->radioButton_color_calib->setDisabled(false);
        ui->radioButton_color->setDisabled(false);
        ui->radioButton_IR->setDisabled(false);
        ui->radioButtonRechargeCamera->setDisabled(false);
    }
}

int MainWindow::read_all_file_name(string path,vector<string> &Files)
{
      struct dirent *ptr;
      DIR *dir;
      vector<string> files;
      dir=opendir(path.c_str());
      while((ptr=readdir(dir))!=NULL)
      {
          //跳过'.'和'..'两个目录
          if(ptr->d_name[0] == '.')
              continue;
          //cout << ptr->d_name << endl;
          files.push_back(ptr->d_name);
      }
      for (int i = 0; i < files.size(); ++i)
      {
          string temp = files[i];
          if(temp.substr(temp.size()-3,temp.size()-1).compare("jpg")==0)//过滤除jpg以外文件
          {
            Files.push_back(path+temp);
            //cout << files[i] << endl;
          }
      }

      closedir(dir);
      return 0;
}

bool MainWindow::SaveStringList(const string outputname, vector<string>& l)
{
    Mat m = imread(outputname); //check if the output is an image - prevent overwrites!
    if(!m.empty()){
      std::cerr << "fail! Please specify an output file, don't want to overwrite your images!" << endl;
      return 1;
    }

    FileStorage fs(outputname, FileStorage::WRITE);
    fs << "images" << "[";
    for(int i = 0; i < l.size(); i++){
      fs << l[i];
    }
    fs << "]";
}

bool MainWindow::myWriteXML(int total_imgs, string s){
    std::ofstream out_file;
    out_file.open(s);
    if(!out_file){
        return false;
    }

    out_file<<"<?xml version=\"1.0\"?>\n"<<std::endl;
    out_file<<"<opencv_storage>"<<std::endl;
    out_file<<"<imagelist>"<<std::endl;
    for(int i=0; i<total_imgs; ++i){
        out_file<<"\"./imgL/left"<<i<<".jpg\""<<std::endl;
        out_file<<"\"./imgR/right"<<i<<".jpg\""<<std::endl;
    }
    out_file<<"</imagelist>"<<std::endl;
    out_file<<"</opencv_storage>"<<std::endl;
    out_file.close();
    return true;
}

bool MainWindow::myBinocularCalibration(){
//    QProcess *proc = new QProcess;
    QObject::connect(proc, SIGNAL(finished(int,QProcess::ExitStatus)),this, SLOT(binoCalibStatus(int, QProcess::ExitStatus)) );
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("LD_LIBRARY_PATH","/usr/local/lib");
    proc->setProcessEnvironment(env);
    proc->start(binoExeString.c_str());	//it's working!
    return true;
}

void MainWindow::on_pushButton_save_image_clicked()
{
    if(ui->radioButton_IR_calib->isChecked()){
        monotrd.SaveImage();
    }else if(ui->radioButton_color_calib->isChecked()){
        mySaveFlag = true;
    }
    else{
        thread.SetImageSave();
    }
}

void MainWindow::on_pushButton_open_serial_clicked()
{
    if(ui->pushButton_open_serial->text()==tr("打开串口")){
        serial = new QSerialPort;
        serial->setPortName(ui->PortBox->currentText());//设置串口名
        serial->open(QIODevice::ReadWrite);//打开串口
        serial->setBaudRate(ui->BaudBox->currentText().toInt());//设置波特率
        serial->setDataBits(QSerialPort::Data8);//设置数据位数
        serial->setParity(QSerialPort::NoParity);//设置奇偶校验
        serial->setStopBits(QSerialPort::OneStop);//设置停止位
        serial->setFlowControl(QSerialPort::NoFlowControl);//设置流控制
        //关闭设置菜单使能
        ui->PortBox->setEnabled(false);
        ui->BaudBox->setEnabled(false);
        ui->Slider_x->setEnabled(true);
        ui->Slider_y->setEnabled(true);
        ui->pushButton_open_serial->setText(tr("关闭串口"));
        //连接信号槽
        QObject::connect(serial, &QSerialPort::readyRead, this, &MainWindow::Read_Data);
    }else{
        //关闭串口
        serial->clear();
        serial->close();
        serial->deleteLater();
        //恢复设置使能
        ui->PortBox->setEnabled(true);
        ui->BaudBox->setEnabled(true);
        ui->Slider_x->setEnabled(false);
        ui->Slider_y->setEnabled(false);

        ui->pushButton_open_serial->setText(tr("打开串口"));
    }
}
void int2str(const int &int_temp,string &string_temp)
{
        stringstream stream;
        stream<<int_temp;
        string_temp=stream.str();   //此处也可以用 stream>>string_temp
}
void MainWindow::on_pushButton_read_image_list_clicked()
{
    vector<string> Files;
    string cmd,width,height;
    int2str(ui->spinBox_grid_height->value(),height);
    int2str(ui->spinBox_grid_width->value(),width);

    ui->pushButton_start_calib->setDisabled(true);
    qDebug()<<"in binary execution action";
//    updateBinoFileNum();
    if(ui->radioButton_IR_calib->isChecked()){	//calibrate the monocular
        //monocular calibration
        qDebug()<<"monocular calibrating...";
        fisheyecalib.start();
    }
    else if(ui->radioButton_color_calib->isChecked()){	//calibrate the  binocular
        qDebug()<<"binocular calibrating...";
        on_pushButton_start_calib_bino_clicked();
    }
    else if(ui->radioButton_color->isChecked()){	//calibrate the rgbd-color
        qDebug()<<"rgbd-color calibrating...";
        read_all_file_name("./color_image/",Files);
        SaveStringList(color_image_list_file_name, Files);
        cmd = "./cpp-example-calibration -w "+width+" -h "+height+" -o " + color_calib_file_name + " " + color_image_list_file_name;
        executeCMD(cmd.c_str());
    }
    else if(ui->radioButton_IR->isChecked()){	//calibrate the rgbd-ir
        qDebug()<<"rgbd-IR calibrating...";
        read_all_file_name("./IR_image/",Files);
        SaveStringList(depth_image_list_file_name, Files);
        cmd = "./cpp-example-calibration -w "+width+" -h "+height+" -o " + depth_calib_file_name + " " + depth_image_list_file_name;
//        executeCMD(cmd.c_str());		//dongfang
        QProcess *ir_ps = new QProcess(this);

        QObject::connect(ir_ps, SIGNAL(finished(int,QProcess::ExitStatus)),this, SLOT(rgbdCalibStatus(int, QProcess::ExitStatus)) );
        ir_ps->start(cmd.c_str());
    }
    else if(ui->radioButtonRechargeCamera->isChecked()){	//calibrate the recharge camera
        qDebug()<<"rcgCam calibrating...";
        std::vector<std::string> files;
        QString id = ui->lineEdit_RcgID->text();
        if(id.isEmpty()){
            QMessageBox::about(this,tr("Rcg"),tr("输入ID并重试"));
            return;
        }
        read_all_file_name("./imgRcg/",files);
        SaveStringList(depth_image_list_file_name, files);
        cmd = "./cpp-example-calibration -w "+width+" -h "+height+" -o ./CalibrationParam/Rcg" + id.toStdString() + ".yml" + " " + depth_image_list_file_name;

        QProcess *rcg_ps = new QProcess(this);
        QObject::connect(rcg_ps, SIGNAL(finished(int,QProcess::ExitStatus)),this, SLOT(rcgCalibStatus(int, QProcess::ExitStatus)) );
        rcg_ps->start(cmd.c_str());
    }
}

void MainWindow::on_pushButton_clean_clicked()
{
    on_pushButton_clear_bino_clicked();
    executeCMD("rm imgRcg/*");
    executeCMD("rm color_image/*");
    executeCMD("rm Mono/*");
    executeCMD("rm IR_image/*");
    executeCMD("rm ./color_image_list_file.yaml");
    executeCMD("rm ./depth_image_list_file.yaml");
    executeCMD("rm ./imagelist.yaml");
    QMessageBox::about(this,tr("Message"),tr("clear success"));
}

void MainWindow::on_pushButton_clicked()
{

  int x,y;
  QString data_name;
  if(ui->radioButton_list1->isChecked())
      data_name = "list1.data";
  else if(ui->radioButton_list2->isChecked())
      data_name = "list2.data";
  else if(ui->radioButton_list3->isChecked())
      data_name = "list3.data";

  QFile ExpandData(data_name);

  if(ExpandData.open(QIODevice::WriteOnly))
  {
      int list_num = 0;
      QTextStream Out(&ExpandData);
      for( list_num =0;list_num<100;list_num++)
      {
          if(ui->tableView->model()->index(list_num,0).data().isValid()&&ui->tableView->model()->index(list_num,1).data().isValid())
          {
              x = ui->tableView->model()->index(list_num,0).data().toFloat();
              y = ui->tableView->model()->index(list_num,1).data().toFloat();
              Out<<list_num;
              Out << ' ';
              Out<<x;
              Out << ' ';
              Out<<y; //标签里的数据(键--值的方式)
              Out << ' ';
          }
          else
              break;
      }
      x = ui->Slider_x->value();
      y = ui->Slider_y->value();
      Out<<list_num;
      Out << ' ';
      Out<<x;
      Out << ' ';
      Out<<y; //标签里的数据(键--值的方式)
      Out << ' ';
  }
  ExpandData.close();
  on_pushButton_read_lists_clicked();
}

void MainWindow::servoMoveForward(void){
    m_pTimer->stop();
    int data[2];
    data[0]=0;
    Motor_DT_Send_Struct((uint8_t *)data,8,0x15);
    //servoTimer->start(servoDelay);
}
void MainWindow::servoMoveBackward(void){
    m_pTimer->stop();
    int data[2];
    data[0]=2;
    Motor_DT_Send_Struct((uint8_t *)data,8,0x15);
    //servoTimer->start(servoDelay);
}
void MainWindow::servoStop(void){
    //servoTimer->stop();
    int data[2];
    data[0]=1;
    Motor_DT_Send_Struct((uint8_t *)data,8,0x15);
//    m_pTimer->start(CheckDurationMs);
}
void MainWindow::servoInitStop(void){
    //servoInitTimer->stop();
    //int data[2];
    //data[0]=1;
    //Motor_DT_Send_Struct((uint8_t *)data,8,0x15);
    std::cout<<"servoInitStop"<<std::endl;
}

void MainWindow::handleTimeout()
{
    static float x,y;
    static int i=0;

    if(m_pTimer->isActive()){
        if(run_step == 0){
            if(ui->tableView->model()->index(list_num,0).data().isValid()&&ui->tableView->model()->index(list_num,1).data().isValid()){
                x = ui->tableView->model()->index(list_num,0).data().toFloat() ;
                y = ui->tableView->model()->index(list_num,1).data().toFloat() ;
                ui->lcdNumber_set_pith->display(y);
                ui->lcdNumber_set_yaw->display(x);
                list_num++;
            }else{
                if(position==0){
                    if(ui->radioButton_IR->isChecked() || ui->radioButtonRechargeCamera->isChecked() ){	//RGBD-IR keep stillness;
                        run_step = 3;
                        return ;
                    }
                    position = 1;
                    ui->radioButton_list2->setChecked(true);
                    on_radioButton_list2_clicked();
                    servoMoveForward();
                    run_step = 0;
                    list_num = 0;
                    return ;
                }else if(position==1){
                    position = 2;
                    ui->radioButton_list3->setChecked(true);
                    on_radioButton_list3_clicked();
                    servoMoveForward();
                    run_step = 0;
                    list_num = 0;
                    return ;
                }else if(position==2){
                    position = 0;
                    on_radioButton_list1_clicked();
                    run_step = 3;
                    return ;
                }else{
                    assert(false);
                }
            }
            set_pos(x,y);
            run_step = 1;
        }else if(run_step == 1){
            if(abs(ui->lcdNumber_imu_x->value() - x)<2.0 && abs(ui->lcdnumber_imu_y->value() - y)<2.0){
                run_step = 2;
            }
        }else if(run_step == 2){
            if(ui->radioButton_color_calib->isChecked()){	//save binocular image
                on_pushButton_save_bino_clicked();
            }else if( ui->radioButton_IR_calib->isChecked()){	//save monocular image
                monotrd.SaveImage();
            }else if( ui->radioButtonRechargeCamera->isChecked()){	//save auto-recharge camera image
                rechargecam->saveImg();
            }else{	//rgbd
                thread.SetImageSave();
            }
            run_step = 0;
        }else if(run_step == 3){
            m_pTimer->stop();
            ui->pushButton_start_calib->setText(tr("自动开始"));
            run_step =0;
            list_num = 0;
            //drive the chessboard back to initial position
            if(ui->radioButton_color_calib->isChecked() ||  ui->radioButton_IR_calib->isChecked() ){
                on_pushButton_init_clicked();
            }
            on_radioButton_list1_clicked();
            on_pushButton_read_image_list_clicked();	//start calibration
        }
    }
}

void MainWindow::checkHandler(){
    if(ReachFlag){
        ReachFlag = false;
        if(position == 1 || position ==2)
            m_pTimer->start(CheckDurationMs);
    }
}

void MainWindow::binoTimerHandler(){
    cv::Mat left_resized, right_resized;
    cv::Mat left_rectified, right_rectified;
    cv::Mat l_remapx, l_remapy, r_remapx, r_remapy;
    cv::Mat canvas, toShow;

    pfmutex.lock();
    if(plr.left.data && plr.right.data){
        cv::resize(plr.left, left_resized, cv::Size(plr.left.cols/2 ,plr.left.rows/2));
        cv::resize(plr.right, right_resized, cv::Size(plr.right.cols/2 ,plr.right.rows/2));

        if(enable_rectify && matrix_rdy){
            cv::fisheye::initUndistortRectifyMap(M1, D1, R1, P1, plr.left.size(), CV_16SC2, l_remapx, l_remapy);
            cv::fisheye::initUndistortRectifyMap(M2, D2, R2, P2, plr.right.size(), CV_16SC2, r_remapx, r_remapy);
            cv::remap(plr.left, left_rectified, l_remapx, l_remapy, cv::INTER_LINEAR);
            cv::remap(plr.right, right_rectified, r_remapx, r_remapy, cv::INTER_LINEAR);

            cv::resize(left_rectified, left_rectified, cv::Size(plr.left.cols/2 ,plr.left.rows/2));
            cv::resize(right_rectified, right_rectified, cv::Size(plr.right.cols/2 ,plr.right.rows/2));

            canvas.create(left_rectified.size().height, left_rectified.size().width *2, CV_8UC1);
            assert(left_resized.size() == right_resized.size());

            cv::Mat roil = canvas( cv::Rect(0, 0, left_rectified.size().width, left_rectified.size().height) );
            cv::Mat roir = canvas( cv::Rect(left_rectified.size().width, 0, right_rectified.size().width, right_rectified.size().height));
            left_rectified.copyTo(roil);
            right_rectified.copyTo(roir);

            cvtColor(canvas, toShow, COLOR_GRAY2BGR);
            int dist = floor(canvas.size().height / 10);
            for(int i=1; i<10; ++i){
                line(toShow, Point(0, i*dist), Point(toShow.size().width, i*dist), Scalar(0,255,0), 1, 8);
            }
        }
        if(mySaveFlag){
            saveBinoImage(plr);
            mySaveFlag = false;
        }
    }
    pfmutex.unlock();
    ui->Bino_left_rectified->setPixmap(QPixmap::fromImage(Mat2QImage(toShow)) );
    ui->Bino_left_rectified->adjustSize();

    ui->Bino_left_show->setPixmap(QPixmap::fromImage(Mat2QImage(left_resized)) );
    ui->Bino_right_show->setPixmap(QPixmap::fromImage(Mat2QImage(right_resized)) );
    ui->Bino_left_show->adjustSize();
    ui->Bino_right_show->adjustSize();
    if(ReachFlag){
        ReachFlag = false;
        if(position == 1 || position ==2)
            m_pTimer->start(CheckDurationMs);
    }
}

void MainWindow::on_pushButton_start_calib_clicked()
{
    if(ui->pushButton_start_calib->text()==tr("自动开始")){
        if(ui->pushButton_open_serial->text() == "打开串口"){
            QMessageBox::about(this,tr("串口: "), "请打开串口！");
            return;
        }
        if(ui->pushButton_open_camera->text() == "open_camera"){
            QMessageBox::about(this,tr("相机: "), "请打开相机！");
            return;
        }

        on_pushButton_clean_clicked();
        m_pTimer = new QTimer(this);
        connect(m_pTimer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
        m_pTimer->start(CheckDurationMs);

        ui->pushButton_read_lists->setVisible(false);
        ui->pushButton_save_lists->setVisible(false);
        ui->Slider_x->setDisabled(true);
        ui->Slider_y->setDisabled(true);
        ui->pushButton->setDisabled(true);
        ui->radioButton_list1->setDisabled(true);
        ui->radioButton_list2->setDisabled(true);
        ui->radioButton_list3->setDisabled(true);
        ui->pushButton_start_calib->setText(tr("停止"));
    }else{
        run_step = 0;
        list_num = 0;
        ui->pushButton_start_calib->setText(tr("自动开始"));
        m_pTimer->stop();
//        checkTimer->stop();
    }
}

void MainWindow::on_pushButton_read_lists_clicked()
{
     int cnt,x,y;

     QString data_name;
     if(ui->radioButton_list1->isChecked())
         data_name = "list1.data";
     else if(ui->radioButton_list2->isChecked())
         data_name = "list2.data";
     else if(ui->radioButton_list3->isChecked())
         data_name = "list3.data";

     model->clear();
     QStringList labels = QObject::trUtf8("yaw,pitch").simplified().split(",");
     model->setHorizontalHeaderLabels(labels);
     model->setColumnCount(2);
     model->setRowCount(100); //行
     QFile ExpandData(data_name);
     if(ExpandData.open(QIODevice::ReadOnly))
     {
         /*文本输出流，用于保存数据*/
         QTextStream In(&ExpandData);
         QStandardItem* item = 0;
         for(int list_num =0;list_num<100;list_num++)
         {
            In>>cnt;
            In>>x;
            In>>y;
            if(In.atEnd())
                break;
            item = new QStandardItem(QString("%1").arg(x));
            model->setItem(cnt,0,item);
            item = new QStandardItem(QString("%1").arg(y));
            model->setItem(cnt,1,item);

         }

         ExpandData.close();
     }
     ui->tableView->setModel(model);
     ui->tableView->show();
}

void MainWindow::on_pushButton_save_lists_clicked()
{
    int x,y;
    QString data_name;
    if(ui->radioButton_list1->isChecked())
        data_name = "list1.data";
    else if(ui->radioButton_list2->isChecked())
        data_name = "list2.data";
    else if(ui->radioButton_list3->isChecked())
        data_name = "list3.data";

    QFile ExpandData(data_name);

    if(ExpandData.open(QIODevice::WriteOnly))
    {
        for(int list_num =0;list_num<100;list_num++)
        {

            if(ui->tableView->model()->index(list_num,0).data().isValid()&&ui->tableView->model()->index(list_num,1).data().isValid())
            {
                QTextStream Out(&ExpandData);
                x = ui->tableView->model()->index(list_num,0).data().toFloat();
                y = ui->tableView->model()->index(list_num,1).data().toFloat();
                Out<<list_num;
                Out << ' ';
                Out<<x;
                Out << ' ';
                Out<<y; //标签里的数据(键--值的方式)
                Out << ' ';
            }
        }
    }
    ExpandData.close();
}

void MainWindow::on_Slider_y_valueChanged(int value)
{
    ui->lcdNumber_set_pith->display(ui->Slider_y->value());
    ui->lcdNumber_set_yaw->display(ui->Slider_x->value());
    set_pos((float)ui->Slider_x->value(),(float)ui->Slider_y->value());
}

void MainWindow::on_Slider_x_valueChanged(int value)
{
    ui->lcdNumber_set_pith->display(ui->Slider_y->value());
    ui->lcdNumber_set_yaw->display(ui->Slider_x->value());
    set_pos((float)ui->Slider_x->value(),(float)ui->Slider_y->value());
}

void MainWindow::on_radioButton_list1_clicked()
{
    on_pushButton_read_lists_clicked();
}

void MainWindow::on_radioButton_list2_clicked()
{
    on_pushButton_read_lists_clicked();
}

void MainWindow::on_radioButton_list3_clicked()
{
    on_pushButton_read_lists_clicked();
}

void MainWindow::on_radioButton_IR_toggled(bool checked)
{
}

void MainWindow::on_radioButton_color_toggled(bool checked)
{

}

void MainWindow::on_pushButton_clear_record_clicked()
{
    for(int i=0; i<REC_WIDTH; ++i){
        for(int j=0; j<REC_HEIGHT; ++j){
            QStandardItem *item = new QStandardItem(QString::number(0));
            model2->setItem(i,j,item);
        }
    }
    ui->pushButton_chk_crn_distr->setDisabled(false);
}

void MainWindow::on_pushButton_chk_crn_distr_clicked()
{
//    if(ui->radioButton_select_ir_calib->isChecked())
//        caculate_all_record(2);
//    if(ui->radioButton_select_color_calib->isChecked())
//        caculate_all_record(1);
//    ui->pushButton_chk_crn_distr->setDisabled(true);
}

void MainWindow::on_radioButton_IR_calib_clicked()
{
    //monotrd.start();
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
}

void MainWindow::on_tabWidget_currentChanged(int index)
{}


void MainWindow::on_pushButton_open_bino_clicked()
{
    if(ui->pushButton_open_bino->text()=="打开双目"){		//open binocular camera
        ce_config_load_settings("./config/cecfg_std.txt");
        int r = ce_cam_capture_init();
        if(r < 0)
        {
            printf("celog: cam capture error \r\n");
        }else{
            printf("celog: cam capture success \r\n");

            r = ce_cam_preprocess_init();
            if(r < 0)
            {    void servoMoveForward(void);
                void servoMoveBackward(void);
                printf("celog: cam preprocess error \r\n");
            }else{
                //ce_cam_showimg_init(plr);
                ce_cam_capture_calib_init(plr);
            }
        }
        binoTimer->start(100);
        ui->pushButton_open_bino->setText("关闭双目");
    }else{		//close binocular camera
        ce_cam_capture_close();
        ui->pushButton_open_bino->setText("打开双目");
    }
}

void MainWindow::on_pushButton_save_bino_clicked()
{
    mySaveFlag = true;
}

void MainWindow::on_pushButton_clear_bino_clicked()
{
    QDir dir_l("./imgL");
    QDir dir_r("./imgR");
    foreach (QString dirFile, dir_l.entryList()) {
        std::cout<<dirFile.toStdString()<<std::endl;
        dir_l.remove(dirFile);
    }
    foreach (QString dirFile, dir_r.entryList()) {
        std::cout<<dirFile.toStdString()<<std::endl;
        dir_r.remove(dirFile);
    }
    frames = 0 ;
}

void MainWindow::on_pushButton_start_calib_bino_clicked()
{
//    myWriteXML(frames);
    std::cout<<"number of found images: "<<frames<<std::endl;
    sleep(1);
    myBinocularCalibration();
}


void MainWindow::on_pushButton_show_rectified_clicked()
{
     //fs_in = cv::FileStorage(binofile_tmp_i, cv::FileStorage::READ);
     fs = cv::FileStorage(binofile_tmp_e, cv::FileStorage::READ);
     /******read the xxtrinsics matrix to rectify image*******/
     if( !fs.isOpened() ){
         printf("Failed to open file xxtrinsic.yml");
         matrix_rdy = false;
     }else{
         fs["M1"] >> M1;
         fs["D1"] >> D1;
         fs["M2"] >> M2;
         fs["D2"] >> D2;

         fs["R"]  >> R;
         fs["T"]  >> T;
         fs["R1"] >> R1;
         fs["R2"] >> R2;
         fs["P1"] >> P1;
         fs["P2"] >> P2;
         fs["Q"]  >> Q;
         matrix_rdy = true;
     }

    if(ui->pushButton_show_rectified->text()=="矫正效果"){
        ui->pushButton_show_rectified->setText(tr("关闭效果"));
        enable_rectify = true;
        double error_bino = plane_fitting("./imgL/left0.jpg", "./imgR/right0.jpg");
    }else{
        ui->pushButton_show_rectified->setText(tr("矫正效果"));
        enable_rectify = false;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    int data[2];
    data[0]=1;
    Motor_DT_Send_Struct((uint8_t *)data,8,0x15);
}

//void MainWindow::on_pushButton_3_clicked()
//{
//}

void MainWindow::on_pushButton_init_clicked()
{
    ui->radioButton_list1->setChecked(true);
    int data[2];
    data[0]=3;
    Motor_DT_Send_Struct((uint8_t *)data,8,0x15);
}

void MainWindow::on_pushButton_move_forward_clicked()
{
    int data[2];
    data[0]=0;
    Motor_DT_Send_Struct((uint8_t *)data,8,0x15);
}

void MainWindow::on_pushButton_backward_clicked()
{
    int data[2];
    data[0]=2;
    Motor_DT_Send_Struct((uint8_t *)data,8,0x15);
}
