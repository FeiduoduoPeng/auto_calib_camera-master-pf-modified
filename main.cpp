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
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
