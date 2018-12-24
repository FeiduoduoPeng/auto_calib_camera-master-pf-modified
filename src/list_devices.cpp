#include "cooleye_monocular/list_devices.h"

MonocularDevices::MonocularDevices()
{
    caml_addr = CAMD1_LEFT;
    camr_addr = CAMD1_RIGHT;
    cam0_addr = CAMS1_N0;
    cam1_addr = CAMS1_N1;
    cam2_addr = CAMS1_N2;

    cam_left_handle = NULL;
    cam_right_handle = NULL;
    cam0_handle = NULL;
    cam1_handle = NULL;
    cam2_handle = NULL;

    serial_stereo = std::string("0");
    serial0 = std::string("0");
    serial1 = std::string("0");
    serial2 = std::string("0");
}

MonocularDevices::~MonocularDevices()
{

}

int MonocularDevices::initialize(void)
{
    int r_num = 0;
    r_num = ce_usb_open();
    if(r_num < 1)
    {
        std::cerr << "celog: No cameras found! r = " << r_num << std::endl;
        return CE_ERROR;
    }
    else
    {
        // std::cout << "celog: Number of interest found: " << r_num << std::endl;
    }
    libusb_device_handle *pusb_handle;
    for(int i = 0; i < r_num; i++)
    {
        unsigned char buf = 0;
        pusb_handle = ce_usb_gethandle(i);
        int r = libusb_control_transfer(pusb_handle, RT_D2H, GET_CAM_LR, 0, 0, &buf, 1, 1000);

        if(r < 1)
        {
            std::cout << "celog: Get the device monocluar camera addr failed" << std::endl;
        }
        else
        {
            if(CAMD1_LEFT == buf)
            {
                cam_left_handle = pusb_handle;
            }
            else if(CAMD1_RIGHT == buf)
            {
                cam_right_handle = pusb_handle;
            }
            else if(CAMS1_N0 == buf)
            {
                cam0_handle = pusb_handle;
            }
            else if(CAMS1_N1 == buf)
            {
                cam1_handle = pusb_handle;
            }
            else if(CAMS1_N2 == buf)
            {
                cam2_handle = pusb_handle;
            }
        }
    }

    // ce_cams1_set_handle(cam0_handle, cam1_handle, cam2_handle);
    ce_cams1_set_handle(cam_left_handle,
                        cam_right_handle,
                        cam0_handle,
                        cam1_handle,
                        cam2_handle);
    return r_num;
}

int MonocularDevices::getSerial()
{
    if(cam_left_handle != NULL)
    {
        serial_stereo = ce_cam_get_id(caml_addr);
    }
    if(cam0_handle != NULL)
    {
        serial0 = ce_cams1_get_id(cam0_addr);
    }
    if(cam1_handle != NULL)
    {
        serial1 = ce_cams1_get_id(cam1_addr);
    }
    if(cam2_handle != NULL)
    {
        serial2 = ce_cams1_get_id(cam2_addr);
    }
    std::cout<<"*****************************"<<std::endl;
    return 0;
}

int MonocularDevices::setSerial(int cam_num, int serial_)
{
    int ret = 0;
    if(cam_num == CAMD1_LEFT)
    {
        ret = ce_cam_set_id(cam_num, serial_);
    }
    else
    {
        ret = ce_cams1_set_id(cam_num, serial_);
    }

    return ret;
    // return set_ce_cam_id(cam, serial_);
}
