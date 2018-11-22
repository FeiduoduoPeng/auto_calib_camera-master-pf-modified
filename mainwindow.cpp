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
#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <sstream>
#include "calib3d.hpp"

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
    color_image_list_file_name = "color_image_list_file.yaml";
    depth_image_list_file_name = "depth_image_list_file.yaml";
    color_calib_file_name = "color_calib_file.yml";
    depth_calib_file_name = "depth_calib_file.yml";
    /*initialize the frames*/
    QDir dir_l("./imgL");
    QStringList filter;
    filter<<"*.jpg";
    dir_l.setNameFilters(filter);
    QFileInfoList fileinfo = dir_l.entryInfoList(filter);

    frames = fileinfo.count() ;
    //查找可用的串口
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->PortBox->addItem(serial.portName());
            serial.close();
        }
    }
    ui->BaudBox->setCurrentIndex(0);
    ui->pushButton_open_serial->setText(tr("打开串口"));
    ui->pushButton_open_camera->setText(tr("open_camera"));

    QObject::connect(&thread, SIGNAL(send(QString)), this, SLOT(accept(QString)),Qt::BlockingQueuedConnection);
    QObject::connect(binoTimer, SIGNAL(timeout()), this, SLOT(binoTimerHandler()));
    QObject::connect(servoTimer, SIGNAL(timeout()), this, SLOT(servoStop()));

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

    fs_in = cv::FileStorage("./config/intrinsics.yml", cv::FileStorage::READ);
    fs_ex = cv::FileStorage("./config/extrinsics.yml", cv::FileStorage::READ);
    /******read the xxtrinsics matrix to rectify image*******/
    if( (!fs_in.isOpened()) || (!fs_ex.isOpened()) ){
        printf("Failed to open file xxtrinsic.yml");
        matrix_rdy = false;
    }
    else{
        fs_in["M1"] >> M1;
        fs_in["D1"] >> D1;
        fs_in["M2"] >> M2;
        fs_in["D2"] >> D2;

        fs_ex["R"]	>> R;
        fs_ex["T"]	>> T;
        fs_ex["R1"]	>> R1;
        fs_ex["R2"]	>> R2;
        fs_ex["P1"]	>> P1;
        fs_ex["P2"]	>> P2;
        fs_ex["Q"]	>> Q;
        matrix_rdy = true;
    }


    /************************************************************/
    /***********disable some widget for easy use!****************/
    /***********disable some widget for easy use!****************/
    /***********disable some widget for easy use!****************/
    /************************************************************/
    //ui->Slider_x->setDisabled(true);
    //ui->Slider_y->setDisabled(true);
    //ui->pushButton->setDisabled(true);
    //ui->pushButton_save_lists->setDisabled(true);
    //ui->pushButton_read_lists->setDisabled(true);
    //ui->spinBox_grid_height->setDisabled(true);
    //ui->spinBox_grid_width->setDisabled(true);
    //ui->radioButton_color_calib->setDisabled(true);
    //ui->radioButton_IR_calib->setDisabled(true);
    //ui->radioButton_select_ir_calib->setDisabled(true);
    //ui->pushButton_save_image->setDisabled(true);
    //ui->radioButton_IR->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
bool MainWindow::executeCMD(const char *cmd)
{
    FILE *ptr;
    char buf_ps[1024];
    char ps[1024]={0};
    strcpy(ps, cmd);
    if((ptr=popen(ps, "r"))!=NULL)
    {
        while(fgets(buf_ps, 1024, ptr)!=NULL)
        {

        }
        pclose(ptr);
        ptr = NULL;
        return true;
    }
    else
    {
        printf("popen %s error\n", ps);
        return false;
    }

}
bool loadCameraParams(string file_name,Mat &cameraMatrix, Mat &distCoeffs)
{
    FileStorage fs(file_name, FileStorage::READ);//这个名字就是你之前校正得到的yml文件

    if(fs.isOpened())
    {
        fs["camera_matrix"] >> cameraMatrix;
        fs["distortion_coefficients"] >> distCoeffs;
        return true;
    }
    else
    {
        return false;
    }
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
    std::vector<cv::Point2d> corners_left, corners_right;
    bool found = false;
    found = cv::findChessboardCorners(img_left_remap,cv::Size(10,11), corners_left);
    found = found && cv::findChessboardCorners(img_right_remap,cv::Size(10,11), corners_right);
    cv::Mat myT1 = (cv::Mat_<double>(3,4) <<
                    1,0,0,0,
                    0,1,0,0,
                    0,0,1,0);
    cv::Mat myT2;
    cv::hconcat(R,T,myT2);
    cv::Mat pts_4d;
    if(found){
        assert(corners_left.size() == corners_right.size());
    }

    //calculate the 3d points;
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    cloud->width = 10;
    cloud->height =11;
    cloud->points.resize(cloud->width * cloud->height);

    cv::triangulatePoints(myT1, myT2, corners_left, corners_right, pts_4d);
    std::vector<cv::Point3d> points;
    for(int i=0; i<pts_4d.cols; ++i){
        cv::Mat x = pts_4d.col(i);
        x /= x.at<float>(3,0);
        cv::Point3d p(
                        x.at<float>(0,0),
                        x.at<float>(1,0),
                        x.at<float>(2,0)
                    );
        cloud->points[i].x = x.at<float>(0,0);
        cloud->points[i].y = x.at<float>(1,0);
        cloud->points[i].z = x.at<float>(2,0);
        //points.push_back(p);
    }
    //fitting;
    //calculate error;

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

   // qDebug()<<msg;
    // 显示出深度图像
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
                /*******************/
                //int grid_cols = imgShow.cols/REC_WIDTH;
                //int grid_rows = imgShow.rows/REC_HEIGHT;
                //for(auto pt:tempCorners){
                //    incre_record(pt.x/grid_cols, pt.y/grid_rows);
                //}
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
       // thread.SetImageShowColor();

       image = Mat2QImage(calibrator(color_calib_file_name,thread.get_color_img()));
    }
    else if(ui->radioButton_IR_calib->isChecked())
    {
       // thread.SetImageShowIR();
       image = Mat2QImage(calibrator(depth_calib_file_name,thread.get_ir_img()));
    }


    ui->label->setPixmap(QPixmap::fromImage(image));
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
    if(ui->pushButton_open_camera->text()==tr("open_camera"))
    {
        thread.start();
        ui->pushButton_open_camera->setText(tr("close_camera"));

    }
    else
    {
        ui->pushButton_open_camera->setText(tr("open_camera"));
        thread.stop();
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
      std::cerr << "fail! Please specify an output file, don't want to overwrite you images!" << endl;

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
    QProcess *proc = new QProcess;
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("LD_LIBRARY_PATH","/usr/local/lib");
    proc->setProcessEnvironment(env);
    proc->start("./CETOOL_CALI_STEREO_CAL -w=10 -h=11 stereo_calib.xml ");	//it's working!

    std::cout<<"in calibration"<<std::endl;
    return true;
}

void MainWindow::on_pushButton_save_image_clicked()
{
    thread.SetImageSave();

}

void MainWindow::on_pushButton_open_serial_clicked()
{
    if(ui->pushButton_open_serial->text()==tr("打开串口"))
    {
        serial = new QSerialPort;
        //设置串口名
        serial->setPortName(ui->PortBox->currentText());
        //打开串口
        serial->open(QIODevice::ReadWrite);
        //设置波特率
        serial->setBaudRate(ui->BaudBox->currentText().toInt());
        //设置数据位数
        serial->setDataBits(QSerialPort::Data8);

        //设置奇偶校验
        serial->setParity(QSerialPort::NoParity);

        //设置停止位
        serial->setStopBits(QSerialPort::OneStop);

        //设置流控制
        serial->setFlowControl(QSerialPort::NoFlowControl);

        //关闭设置菜单使能
        ui->PortBox->setEnabled(false);
        ui->BaudBox->setEnabled(false);
        ui->Slider_x->setEnabled(true);
        ui->Slider_y->setEnabled(true);
        ui->pushButton_open_serial->setText(tr("关闭串口"));

        //连接信号槽
        QObject::connect(serial, &QSerialPort::readyRead, this, &MainWindow::Read_Data);

    }
    else
    {
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
    qDebug()<<"in binary execution action";
    if(ui->radioButton_select_color_calib->isChecked())
    {
        /*******************/
        //int grid_cols = imgShow.cols/REC_WIDTH;
        //int grid_rows = imgShow.rows/REC_HEIGHT;
        //for(auto pt:tempCorners){
        //    incre_record(pt.x/grid_cols, pt.y/grid_rows);
        //}
        read_all_file_name("./color_image/",Files);
        SaveStringList(color_image_list_file_name, Files);
        cmd = "./cpp-example-calibration -w "+width+" -h "+height+" -o " + color_calib_file_name + " " + color_image_list_file_name;
        executeCMD(cmd.c_str());
    }
    else
    {
        read_all_file_name("./IR_image/",Files);
        SaveStringList(depth_image_list_file_name, Files);
        cmd = "./cpp-example-calibration -w "+width+" -h "+height+" -o " + depth_calib_file_name + " " + depth_image_list_file_name;
        executeCMD(cmd.c_str());
    }

}

void MainWindow::on_pushButton_clean_clicked()
{
    on_pushButton_clear_bino_clicked();
    executeCMD("rm color_image/*");
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
    int data[2];
    data[0]=0;
    Motor_DT_Send_Struct((uint8_t *)data,8,0x15);
    servoTimer->start(servoDelay);
}
void MainWindow::servoMoveBackward(void){
    int data[2];
    data[0]=2;
    Motor_DT_Send_Struct((uint8_t *)data,8,0x15);
    servoTimer->start(servoDelay);
}
void MainWindow::servoStop(void){
    servoTimer->stop();
    int data[2];
    data[0]=1;
    Motor_DT_Send_Struct((uint8_t *)data,8,0x15);
}

void MainWindow::handleTimeout()
{
    static float x,y;
    static double position = 0;

    if(m_pTimer->isActive()){
        if(position!=0){
            //servoInit();
        }
        if(run_step == 0)
        {
            if(ui->tableView->model()->index(list_num,0).data().isValid()&&ui->tableView->model()->index(list_num,1).data().isValid())
            {
                x = ui->tableView->model()->index(list_num,0).data().toFloat() ;
                y = ui->tableView->model()->index(list_num,1).data().toFloat() ;
                ui->lcdNumber_set_pith->display(y);
                ui->lcdNumber_set_yaw->display(x);
                list_num++;
            }
            else
            {
                if(position!=3){
                    position++;
                    //ui->radioButton_list2

                    run_step = 0;
                    return ;
                }
                else{
                    run_step = 3;
                    return ;
                }
            }
            set_pos(x,y);
            run_step = 1;
        }
        else if(run_step == 1)
        {
            if(abs(ui->lcdNumber_imu_x->value() - x)<2.0 && abs(ui->lcdnumber_imu_y->value() - y)<2.0)
            {
                run_step = 2;
            }
        }
        else if(run_step == 2)
        {
            if(ui->tabWidget->currentIndex()==0){
                thread.SetImageSave();
                run_step = 0;
            }
            else if(ui->tabWidget->currentIndex()==1){
                on_pushButton_save_bino_clicked();
                run_step = 0;
            }
        }
        else if(run_step == 3)
        {
            if(ui->tabWidget->currentIndex()==0){
                on_pushButton_read_image_list_clicked();
            }
            else if(ui->tabWidget->currentIndex()==1){
                on_pushButton_start_calib_bino_clicked();
            }
            m_pTimer->stop();
            ui->pushButton_start_calib->setText(tr("自动开始"));
            run_step =0;	//pf
            list_num = 0;	//pf
        }
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

}

void MainWindow::on_pushButton_start_calib_clicked()
{
    //if(ui->pushButton_start_calib->text()==tr("start_calib"))
    if(ui->pushButton_start_calib->text()==tr("自动开始"))
    {
        m_pTimer = new QTimer(this);
        connect(m_pTimer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
        m_pTimer->start(1000);
        ui->pushButton_start_calib->setText(tr("停止"));
    }
    else
    {
        run_step = 0;
        list_num = 0;
        ui->pushButton_start_calib->setText(tr("自动开始"));
        m_pTimer->stop();
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
    if(ui->radioButton_select_ir_calib->isChecked())
        caculate_all_record(2);
    if(ui->radioButton_select_color_calib->isChecked())
        caculate_all_record(1);
    ui->pushButton_chk_crn_distr->setDisabled(true);
}

void MainWindow::on_radioButton_IR_calib_clicked()
{

}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    //if(ui->tabWidget->currentIndex() == 1){
    //    std::cout<<"disable"<<std::endl;
    //    ui->pushButton->setDisabled(true);
    //    ui->pushButton_save_lists->setDisabled(true);
    //    ui->pushButton_read_lists->setDisabled(true);
    //    ui->spinBox_grid_height->setDisabled(true);
    //    ui->spinBox_grid_width->setDisabled(true);
    //    ui->radioButton_color_calib->setDisabled(true);
    //    ui->radioButton_IR_calib->setDisabled(true);
    //    ui->radioButton_select_ir_calib->setDisabled(true);
    //    ui->pushButton_save_image->setDisabled(true);
    //    ui->radioButton_IR->setDisabled(true);
    //}else{
    //    std::cout<<"enable"<<std::endl;
    //    ui->pushButton->setDisabled(false);
    //    ui->pushButton_save_lists->setDisabled(false);
    //    ui->pushButton_read_lists->setDisabled(false);
    //    ui->spinBox_grid_height->setDisabled(false);
    //    ui->spinBox_grid_width->setDisabled(false);
    //    ui->radioButton_color_calib->setDisabled(false);
    //    ui->radioButton_IR_calib->setDisabled(false);
    //    ui->radioButton_select_ir_calib->setDisabled(false);
    //    ui->pushButton_save_image->setDisabled(false);
    //    ui->radioButton_IR->setDisabled(false);
    //}
}

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
    myWriteXML(frames);
    std::cout<<"number of found images: "<<frames<<std::endl;
    sleep(1);
    myBinocularCalibration();
}


void MainWindow::on_pushButton_show_rectified_clicked()
{
    if(ui->pushButton_show_rectified->text()=="矫正效果"){
        ui->pushButton_show_rectified->setText(tr("关闭效果"));
        enable_rectify = true;
        double error_bino = plane_fitting("./imgL/left15.jpg", "./imgR/right15.jpg");
    }else{
        ui->pushButton_show_rectified->setText(tr("矫正效果"));
        enable_rectify = false;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    //int data[2];
    //data[0]=1;
    //Motor_DT_Send_Struct((uint8_t *)data,8,0x15);
    servoMoveForward();
}
