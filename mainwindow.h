#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "thread.h"
#include <iostream>
#include <string>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "QStandardItemModel"

#define REC_WIDTH 5
#define REC_HEIGHT 5

using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    int read_all_file_name(string path,vector<string> &Files);
    bool executeCMD(const char *cmd);
    void Read_Data();
    bool incre_record(int i, int j);
    bool caculate_all_record(int img_type);

    bool SaveStringList(const string outputname, vector<string>& l);
    ~MainWindow();

public slots:

    void accept(QString msg);

private slots:

    void on_pushButton_open_camera_clicked();

    void on_pushButton_save_image_clicked();

    void on_pushButton_open_serial_clicked();

    void on_pushButton_read_image_list_clicked();

    void on_pushButton_clean_clicked();

    void on_pushButton_clicked();

    void on_pushButton_start_calib_clicked();

    void handleTimeout();
    void on_pushButton_read_lists_clicked();

    void on_pushButton_save_lists_clicked();

    void on_Slider_y_valueChanged(int value);

    void on_Slider_x_valueChanged(int value);

    void on_radioButton_list1_clicked();

    void on_radioButton_list2_clicked();

    void on_radioButton_list3_clicked();

    void on_radioButton_IR_toggled(bool checked);

    void on_radioButton_color_toggled(bool checked);

    void on_pushButton_clear_record_clicked();

    void on_pushButton_chk_crn_distr_clicked();

private:
    Ui::MainWindow *ui;
    Thread thread;
    QTimer *m_pTimer;
    string depth_calib_file_name;
    string color_calib_file_name;
    string depth_image_list_file_name;
    string color_image_list_file_name;
    string IR_image_list_file_name;
    int run_step ;
    int list_num = 0;
    QStandardItemModel* model = new QStandardItemModel();
    QStandardItemModel* model2 = new QStandardItemModel();

};

#endif // MAINWINDOW_H
