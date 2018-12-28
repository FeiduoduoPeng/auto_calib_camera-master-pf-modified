#ifndef __FISHEYE_CALIBRATE_H__
#define __FISHEYE_CALIBRATE_H__

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>

#include <fstream>
#include <dirent.h>

#define CORNER_WIDTH 10
#define CORNER_HEIGHT 11
#define squareSize 30


int FisheyeCalibrate(std::string rootdirPath, std::string xxtrinsics);
//void FishEyeCalibrate();

#endif  //fisheye_calibrate.h
