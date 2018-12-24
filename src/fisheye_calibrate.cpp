#include <opencv2/opencv.hpp>
#include "fisheye_calibrate.h"
#include "myWriteMySQL.h"
#include <algorithm>
#include <QThread>


bool stringCmp(std::string s1, std::string s2){
    s1.erase(0,11);	//delete this part "./Mono/mono"
    s2.erase(0,11);
    for(int i=0; i<4; i++){
        s1.pop_back();
        s2.pop_back();
    }
    return std::stoi(s1) < std::stoi(s2);
}

int FisheyeCalibrate(std::string rootdirPath, std::string xxtrinsics){
    using namespace std;
    using namespace cv;
    DIR * dir;
    struct dirent * ptr;
    string x, dirPath;
    vector<string> filenames;
    dir = opendir((char *)rootdirPath.c_str()); //打开一个目录
    while((ptr = readdir(dir)) != NULL) //循环读取目录数据
    {
        x = ptr->d_name;
        dirPath = rootdirPath + "/" + x;
        if( string::npos == dirPath.find(".jpg")){
            continue;
        }
        filenames.push_back(dirPath);
    }
    std::sort(filenames.begin(), filenames.end(), stringCmp );
//    for(int i=0; i<filenames.size(); ++i){
//        std::cout<<filenames[i]<<std::endl;
//    }
    closedir(dir);//关闭目录指针
    cout<<"found images number: "<<filenames.size()<<endl;

    vector<cv::Point3d> obj;
    for(int i=0; i<CORNER_HEIGHT; ++i){
        for(int j=0; j<CORNER_WIDTH; ++j){
            obj.push_back( cv::Point3d(float(j*squareSize),
                                        float(i*squareSize), 0 ));
        }
    }
    if(filenames.size() == 0){
        std::cerr<<"MONO-CALIB no file found"<<std::endl;
        return -1;
    }

    vector<Mat> pics;
    cv::Mat gray_pic;
    vector<cv::Point2f> corners;
    vector<vector<cv::Point2d> > imgPoints;
    Size sz = imread(filenames[0]).size();

    for(int i=0; i<filenames.size(); ++i){
        gray_pic = cv::imread(filenames[i]);
        if(gray_pic.empty()){
            std::cerr<<"MONO-CALIB open error"<<std::endl;
            return -1;
        }
        int found = findChessboardCorners(gray_pic, Size(CORNER_WIDTH, CORNER_HEIGHT), corners);
        if(found){
//            cv::drawChessboardCorners(gray_pic, Size(CORNER_WIDTH, CORNER_HEIGHT), corners, found);
//            cv::imshow("corners",gray_pic);
//            QThread::msleep(100);
//            cv::destroyAllWindows();
            vector<cv::Point2d> corners_d;
            for(int i=0; i<corners.size(); ++i){
                corners_d.push_back( cv::Point2d((double)corners[i].x, (double)corners[i].y) );
            }
            imgPoints.push_back(corners_d);
            corners.clear();
        }
    }
    vector<vector<cv::Point3d> > objPoints(imgPoints.size(), obj);

    cv::Mat K;
    cv::Mat D;
    vector<cv::Mat> rvecs, tvecs;
    int flag = 0;
    flag |= cv::fisheye::CALIB_RECOMPUTE_EXTRINSIC;
    flag |= cv::fisheye::CALIB_CHECK_COND;
    flag |= cv::fisheye::CALIB_FIX_SKEW; 

    double rms=0;
    try{
        rms = cv::fisheye::calibrate(
                objPoints, imgPoints, sz,
                K, D, cv::noArray(), cv::noArray(),
                flag,
                cv::TermCriteria(3,20,1e-6) );
    }catch(cv::Exception &e){
        std::string s(e.what());
        std::cout<<s<<std::endl;
        int in_pos = s.find("in function",0);
        std::string ill_s = s.substr(in_pos-3,2);
        int ill_num = std::stoi(ill_s);
        destroyAllWindows();
        return ill_num+1;
    }
    if(rms>1.0){
        return -1;
    }
    cv::FileStorage fs(xxtrinsics, cv::FileStorage::WRITE);
    fs << "K" << K;
    fs << "D" << D;
    fs << "rms" << rms;
    fs.release();

    //save camera-params to mysql , the function is added by pf;
    stringstream ss;
    ss << "\nK: " << K << "\nD: " << D << "\nrms: " << rms;
    if(xxtrinsics.size()>34){
        myWriteMySQL(xxtrinsics.substr(19,12)+"0", ss.str(), "mono_cam");
    }else{
        myWriteMySQL("uuid=0", ss.str(), "mono_cam");
    }
    cv::destroyAllWindows();

    Mat UndistortImg;
    Mat DistortImg = cv::imread(filenames[0]);

    Mat new_intrinsic_mat;
    K.copyTo(new_intrinsic_mat);
    new_intrinsic_mat.at<double>(0,0) *= 0.4;
    new_intrinsic_mat.at<double>(1,1) *= 0.4;
    new_intrinsic_mat.at<double>(0,2) += 0.0;
    new_intrinsic_mat.at<double>(1,2) += 0.0;

//    try{
//        cv::fisheye::undistortImage(
//            DistortImg,
//            UndistortImg,
//            K,
//            D,
//            new_intrinsic_mat
//        );
//        imshow(filenames[0], UndistortImg);
//    }catch(...){
//        return -1;
//    }
    destroyAllWindows();
    return 0;
}
