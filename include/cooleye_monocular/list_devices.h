#ifndef LIST_DEVICES_H
#define LIST_DEVICES_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <signal.h>

#include "cedriver_cam.h"
#include "cedriver_usb.h"
#include "cedriver_config.h"
#include "cedriver_global_config.h"

class MonocularDevices
{
public:
    MonocularDevices();
    ~MonocularDevices();

    int initialize(void);
    int getSerial(void);
    int setSerial(int cam, int serial_);

    int caml_addr;
    int camr_addr;
    int cam0_addr;
    int cam1_addr;
    int cam2_addr;

    std::string serial_stereo;
    std::string serial0;
    std::string serial1;
    std::string serial2;

private:
    libusb_device_handle *cam_left_handle;
    libusb_device_handle *cam_right_handle;
    libusb_device_handle *cam0_handle;
    libusb_device_handle *cam1_handle;
    libusb_device_handle *cam2_handle;
};

#endif // LIST_DEVICES_H
