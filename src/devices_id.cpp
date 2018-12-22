#include "devices_id.h"

#include <iostream>
#include <string>
#include <memory>
#include "astra_camera/astra_device_manager.h"
#include "astra_camera/astra_exception.h"
#include "cooleye_monocular/list_devices.h"

using astra_wrapper::AstraDeviceManager;
using astra_wrapper::AstraDeviceInfo;
using astra_wrapper::AstraException;
using namespace std;

bool getDeviceID(std::string &rgbd, std::string &bino, std::string &mono)
{

  //*************RGBD***************//
  static astra_wrapper::AstraDeviceManager manager; //TODO use static to avoid destory this class, or program will be crash
  boost::shared_ptr<std::vector<astra_wrapper::AstraDeviceInfo> > device_infos = manager.getConnectedDeviceInfos();
  std::vector<std::string> serials;

  for (size_t i = 0; i < device_infos->size(); ++i)
  {
    std::cout << device_infos->at(i) << std::endl;
    try {
      std::string serial;
//      std::cout << "ID: " << device_infos->at(i).product_id_ <<std::endl;
//      std::cout<<"****************************"<<std::endl;

      if(device_infos->at(i).product_id_ == 0x404){
        serial = "D" + manager.getSerial(device_infos->at(i).uri_);
      }else if(device_infos->at(i).product_id_ == 0x407){
        serial = "E" + manager.getSerial(device_infos->at(i).uri_);
      }else{
        serial = "X" + manager.getSerial(device_infos->at(i).uri_);
      }
      serials.push_back(serial);
    }
    catch (const AstraException& exception)
    {
      cout<<"no rgbd found"<<endl;
    }
  }
  if(serials.size() != 0){
    rgbd = serials[0];
  }else{
    rgbd = std::string("0");
  }

  //********bino/mono-cular*********//
  MonocularDevices monocular_devices;
  int num = monocular_devices.initialize();
  if(num < 1){
      std::cout << "Can not find interested devices." << std::endl;
  }
  monocular_devices.getSerial();

  bino = monocular_devices.serial_stereo.substr(0,12);
  mono = monocular_devices.serial0;

  if(serials.size() > 0 )
      std::cout << "rgbd_cam : " << serials[0] << std::endl;
  else std::cout << "rgbd_cam : " << 0 << std::endl;
  std::cout << "bino_cam : " << bino << std::endl;
  std::cout << "mono_cam : " << mono << std::endl;

  return true;
}
