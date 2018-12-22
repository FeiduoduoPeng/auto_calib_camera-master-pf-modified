#include "mainwindow.h"
#include <exception>
#include "communication.h"
#include <QApplication>
#include "devices_id.h"
#include "astra_camera/astra_exception.h"


#include <stdlib.h>

#include <iostream>

#include <string>


int main(int argc, char *argv[])
{
//    string rgbd, bino, mono;
//    try{
//        getDeviceID(rgbd, bino, mono);
//        cout<<rgbd<<endl<<bino<<endl<<mono<<endl;
//    }catch(const astra_wrapper::AstraException& exception){
//        std::cout<<"f**k ya1"<<std::endl;
//    }catch(...){
//        std::cout<<"f**k ya2"<<std::endl;
//    }
//    while(1){}
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
