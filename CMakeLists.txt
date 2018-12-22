cmake_minimum_required(VERSION 2.8)

project(camtest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -g")


find_package(OpenCV 3.4.2 REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_library(CEDRIVER_CONFIG src/cedriver_config.cpp)

add_executable( cpp-example-calibration src/calibration.cpp src/myWriteMySQL.cpp)
target_link_libraries( cpp-example-calibration 
                        ${OpenCV_LIBS}
                        mysqlcppconn)

add_executable(CETOOL_CALI_STEREO_CAL src/cetool_cali_stereo_cal.cpp src/myWriteMySQL.cpp)
target_link_libraries(  CETOOL_CALI_STEREO_CAL 
                        #CEDRIVER_CAM 
                        CEDRIVER_CONFIG 
                        #CEDRIVER_IMU 
                        usb-1.0 
                        mysqlcppconn
                        ${OpenCV_LIBS}
                        )
                        
                        
