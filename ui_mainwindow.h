/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_6;
    QFrame *frame;
    QFormLayout *formLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QComboBox *BaudBox;
    QComboBox *PortBox;
    QPushButton *pushButton_open_serial;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QRadioButton *radioButton_IR;
    QRadioButton *radioButton_color;
    QPushButton *pushButton_open_camera;
    QRadioButton *radioButton_IR_calib;
    QRadioButton *radioButton_color_calib;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QRadioButton *radioButton_select_color_calib;
    QPushButton *pushButton_start_calib;
    QPushButton *pushButton_clean;
    QRadioButton *radioButton_select_ir_calib;
    QPushButton *pushButton_save_image;
    QPushButton *pushButton_read_image_list;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_5;
    QSlider *Slider_y;
    QSlider *Slider_x;
    QPushButton *pushButton;
    QTabWidget *tabWidget;
    QWidget *Tab1;
    QLabel *label;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_4;
    QLCDNumber *lcdNumber_set_pith;
    QLCDNumber *lcdnumber_imu_y;
    QLCDNumber *lcdNumber_imu_x;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label_3;
    QLCDNumber *lcdNumber_set_yaw;
    QLabel *label_5;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_7;
    QLabel *label_6;
    QSpinBox *spinBox_grid_width;
    QLabel *label_7;
    QSpinBox *spinBox_grid_height;
    QCheckBox *checkBox_show_check;
    QWidget *Tab2;
    QTableView *tableView;
    QPushButton *pushButton_save_lists;
    QPushButton *pushButton_read_lists;
    QRadioButton *radioButton_list1;
    QRadioButton *radioButton_list2;
    QRadioButton *radioButton_list3;
    QTableView *tableView_2;
    QPushButton *pushButton_clear_record;
    QPushButton *pushButton_chk_crn_distr;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(838, 793);
        MainWindow->setMinimumSize(QSize(640, 480));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_6 = new QGridLayout(centralWidget);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        formLayout = new QFormLayout(frame);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        BaudBox = new QComboBox(groupBox);
        BaudBox->setObjectName(QStringLiteral("BaudBox"));
        BaudBox->setEditable(false);

        gridLayout_2->addWidget(BaudBox, 0, 0, 1, 1);

        PortBox = new QComboBox(groupBox);
        PortBox->setObjectName(QStringLiteral("PortBox"));
        PortBox->setEditable(false);
        PortBox->setCurrentText(QStringLiteral(""));
        PortBox->setMaxVisibleItems(5);

        gridLayout_2->addWidget(PortBox, 1, 0, 1, 1);

        pushButton_open_serial = new QPushButton(groupBox);
        pushButton_open_serial->setObjectName(QStringLiteral("pushButton_open_serial"));

        gridLayout_2->addWidget(pushButton_open_serial, 2, 0, 1, 1);


        formLayout->setWidget(0, QFormLayout::FieldRole, groupBox);

        groupBox_2 = new QGroupBox(frame);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        radioButton_IR = new QRadioButton(groupBox_2);
        radioButton_IR->setObjectName(QStringLiteral("radioButton_IR"));
        radioButton_IR->setChecked(true);

        gridLayout->addWidget(radioButton_IR, 0, 0, 1, 1);

        radioButton_color = new QRadioButton(groupBox_2);
        radioButton_color->setObjectName(QStringLiteral("radioButton_color"));
        radioButton_color->setChecked(false);

        gridLayout->addWidget(radioButton_color, 1, 0, 1, 1);

        pushButton_open_camera = new QPushButton(groupBox_2);
        pushButton_open_camera->setObjectName(QStringLiteral("pushButton_open_camera"));

        gridLayout->addWidget(pushButton_open_camera, 4, 0, 1, 1);

        radioButton_IR_calib = new QRadioButton(groupBox_2);
        radioButton_IR_calib->setObjectName(QStringLiteral("radioButton_IR_calib"));

        gridLayout->addWidget(radioButton_IR_calib, 2, 0, 1, 1);

        radioButton_color_calib = new QRadioButton(groupBox_2);
        radioButton_color_calib->setObjectName(QStringLiteral("radioButton_color_calib"));

        gridLayout->addWidget(radioButton_color_calib, 3, 0, 1, 1);


        formLayout->setWidget(1, QFormLayout::FieldRole, groupBox_2);

        groupBox_3 = new QGroupBox(frame);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        radioButton_select_color_calib = new QRadioButton(groupBox_3);
        radioButton_select_color_calib->setObjectName(QStringLiteral("radioButton_select_color_calib"));

        gridLayout_3->addWidget(radioButton_select_color_calib, 0, 0, 1, 1);

        pushButton_start_calib = new QPushButton(groupBox_3);
        pushButton_start_calib->setObjectName(QStringLiteral("pushButton_start_calib"));

        gridLayout_3->addWidget(pushButton_start_calib, 4, 0, 1, 1);

        pushButton_clean = new QPushButton(groupBox_3);
        pushButton_clean->setObjectName(QStringLiteral("pushButton_clean"));

        gridLayout_3->addWidget(pushButton_clean, 2, 0, 1, 1);

        radioButton_select_ir_calib = new QRadioButton(groupBox_3);
        radioButton_select_ir_calib->setObjectName(QStringLiteral("radioButton_select_ir_calib"));
        radioButton_select_ir_calib->setChecked(true);

        gridLayout_3->addWidget(radioButton_select_ir_calib, 1, 0, 1, 1);

        pushButton_save_image = new QPushButton(groupBox_3);
        pushButton_save_image->setObjectName(QStringLiteral("pushButton_save_image"));

        gridLayout_3->addWidget(pushButton_save_image, 3, 0, 1, 1);

        pushButton_read_image_list = new QPushButton(groupBox_3);
        pushButton_read_image_list->setObjectName(QStringLiteral("pushButton_read_image_list"));

        gridLayout_3->addWidget(pushButton_read_image_list, 5, 0, 1, 1);


        formLayout->setWidget(3, QFormLayout::FieldRole, groupBox_3);

        groupBox_4 = new QGroupBox(frame);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setMinimumSize(QSize(0, 100));
        gridLayout_5 = new QGridLayout(groupBox_4);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        Slider_y = new QSlider(groupBox_4);
        Slider_y->setObjectName(QStringLiteral("Slider_y"));
        Slider_y->setEnabled(false);
        Slider_y->setMinimum(-30);
        Slider_y->setMaximum(30);
        Slider_y->setPageStep(1);
        Slider_y->setValue(0);
        Slider_y->setSliderPosition(0);
        Slider_y->setOrientation(Qt::Vertical);
        Slider_y->setInvertedAppearance(true);
        Slider_y->setInvertedControls(false);

        gridLayout_5->addWidget(Slider_y, 0, 0, 1, 1);

        Slider_x = new QSlider(groupBox_4);
        Slider_x->setObjectName(QStringLiteral("Slider_x"));
        Slider_x->setEnabled(false);
        Slider_x->setMinimum(-30);
        Slider_x->setMaximum(30);
        Slider_x->setPageStep(1);
        Slider_x->setValue(0);
        Slider_x->setOrientation(Qt::Horizontal);

        gridLayout_5->addWidget(Slider_x, 0, 1, 1, 1);


        formLayout->setWidget(4, QFormLayout::FieldRole, groupBox_4);

        pushButton = new QPushButton(frame);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        formLayout->setWidget(5, QFormLayout::FieldRole, pushButton);


        gridLayout_6->addWidget(frame, 0, 1, 1, 1);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        Tab1 = new QWidget();
        Tab1->setObjectName(QStringLiteral("Tab1"));
        Tab1->setMinimumSize(QSize(640, 480));
        label = new QLabel(Tab1);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(9, 9, 640, 480));
        label->setMinimumSize(QSize(640, 480));
        label->setBaseSize(QSize(640, 480));
        groupBox_5 = new QGroupBox(Tab1);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 560, 341, 111));
        gridLayout_4 = new QGridLayout(groupBox_5);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        lcdNumber_set_pith = new QLCDNumber(groupBox_5);
        lcdNumber_set_pith->setObjectName(QStringLiteral("lcdNumber_set_pith"));

        gridLayout_4->addWidget(lcdNumber_set_pith, 2, 2, 1, 1);

        lcdnumber_imu_y = new QLCDNumber(groupBox_5);
        lcdnumber_imu_y->setObjectName(QStringLiteral("lcdnumber_imu_y"));

        gridLayout_4->addWidget(lcdnumber_imu_y, 1, 2, 1, 1);

        lcdNumber_imu_x = new QLCDNumber(groupBox_5);
        lcdNumber_imu_x->setObjectName(QStringLiteral("lcdNumber_imu_x"));

        gridLayout_4->addWidget(lcdNumber_imu_x, 1, 1, 1, 1);

        label_2 = new QLabel(groupBox_5);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_4->addWidget(label_2, 0, 2, 1, 1);

        label_4 = new QLabel(groupBox_5);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_4->addWidget(label_4, 1, 0, 1, 1);

        label_3 = new QLabel(groupBox_5);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_4->addWidget(label_3, 0, 1, 1, 1);

        lcdNumber_set_yaw = new QLCDNumber(groupBox_5);
        lcdNumber_set_yaw->setObjectName(QStringLiteral("lcdNumber_set_yaw"));

        gridLayout_4->addWidget(lcdNumber_set_yaw, 2, 1, 1, 1);

        label_5 = new QLabel(groupBox_5);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_4->addWidget(label_5, 2, 0, 1, 1);

        groupBox_6 = new QGroupBox(Tab1);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(370, 560, 201, 102));
        gridLayout_7 = new QGridLayout(groupBox_6);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        label_6 = new QLabel(groupBox_6);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_7->addWidget(label_6, 0, 0, 1, 1);

        spinBox_grid_width = new QSpinBox(groupBox_6);
        spinBox_grid_width->setObjectName(QStringLiteral("spinBox_grid_width"));
        spinBox_grid_width->setValue(10);

        gridLayout_7->addWidget(spinBox_grid_width, 0, 1, 1, 1);

        label_7 = new QLabel(groupBox_6);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_7->addWidget(label_7, 1, 0, 1, 1);

        spinBox_grid_height = new QSpinBox(groupBox_6);
        spinBox_grid_height->setObjectName(QStringLiteral("spinBox_grid_height"));
        spinBox_grid_height->setValue(11);

        gridLayout_7->addWidget(spinBox_grid_height, 1, 1, 1, 1);

        checkBox_show_check = new QCheckBox(groupBox_6);
        checkBox_show_check->setObjectName(QStringLiteral("checkBox_show_check"));

        gridLayout_7->addWidget(checkBox_show_check, 2, 1, 1, 1);

        tabWidget->addTab(Tab1, QString());
        Tab2 = new QWidget();
        Tab2->setObjectName(QStringLiteral("Tab2"));
        tableView = new QTableView(Tab2);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(30, 50, 241, 501));
        tableView->setInputMethodHints(Qt::ImhNone);
        tableView->setEditTriggers(QAbstractItemView::AllEditTriggers);
        pushButton_save_lists = new QPushButton(Tab2);
        pushButton_save_lists->setObjectName(QStringLiteral("pushButton_save_lists"));
        pushButton_save_lists->setGeometry(QRect(290, 470, 89, 25));
        pushButton_read_lists = new QPushButton(Tab2);
        pushButton_read_lists->setObjectName(QStringLiteral("pushButton_read_lists"));
        pushButton_read_lists->setGeometry(QRect(290, 520, 89, 25));
        radioButton_list1 = new QRadioButton(Tab2);
        radioButton_list1->setObjectName(QStringLiteral("radioButton_list1"));
        radioButton_list1->setGeometry(QRect(300, 400, 112, 23));
        radioButton_list1->setChecked(true);
        radioButton_list2 = new QRadioButton(Tab2);
        radioButton_list2->setObjectName(QStringLiteral("radioButton_list2"));
        radioButton_list2->setGeometry(QRect(300, 420, 112, 23));
        radioButton_list3 = new QRadioButton(Tab2);
        radioButton_list3->setObjectName(QStringLiteral("radioButton_list3"));
        radioButton_list3->setGeometry(QRect(300, 440, 112, 23));
        tableView_2 = new QTableView(Tab2);
        tableView_2->setObjectName(QStringLiteral("tableView_2"));
        tableView_2->setGeometry(QRect(300, 20, 271, 261));
        tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView_2->horizontalHeader()->setVisible(false);
        tableView_2->verticalHeader()->setVisible(false);
        pushButton_clear_record = new QPushButton(Tab2);
        pushButton_clear_record->setObjectName(QStringLiteral("pushButton_clear_record"));
        pushButton_clear_record->setGeometry(QRect(450, 330, 101, 31));
        pushButton_chk_crn_distr = new QPushButton(Tab2);
        pushButton_chk_crn_distr->setObjectName(QStringLiteral("pushButton_chk_crn_distr"));
        pushButton_chk_crn_distr->setGeometry(QRect(450, 290, 101, 31));
        tabWidget->addTab(Tab2, QString());

        gridLayout_6->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 838, 28));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        PortBox->setCurrentIndex(-1);
        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "serial control", 0));
        BaudBox->clear();
        BaudBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "115200", 0)
         << QApplication::translate("MainWindow", "57600", 0)
         << QApplication::translate("MainWindow", "9600", 0)
        );
        pushButton_open_serial->setText(QApplication::translate("MainWindow", "open_serial", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "camera control", 0));
        radioButton_IR->setText(QApplication::translate("MainWindow", "IR_camera", 0));
        radioButton_color->setText(QApplication::translate("MainWindow", "color_camera", 0));
        pushButton_open_camera->setText(QApplication::translate("MainWindow", "open_camera", 0));
        radioButton_IR_calib->setText(QApplication::translate("MainWindow", "IR_was_calib", 0));
        radioButton_color_calib->setText(QApplication::translate("MainWindow", "color_was_calib", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "image setting", 0));
        radioButton_select_color_calib->setText(QApplication::translate("MainWindow", "calib_clolor_image", 0));
        pushButton_start_calib->setText(QApplication::translate("MainWindow", "start_calib", 0));
        pushButton_clean->setText(QApplication::translate("MainWindow", "clear_image", 0));
        radioButton_select_ir_calib->setText(QApplication::translate("MainWindow", "calib_IR_image", 0));
        pushButton_save_image->setText(QApplication::translate("MainWindow", "save_image", 0));
        pushButton_read_image_list->setText(QApplication::translate("MainWindow", "calib_image", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "camera_Pos_setting", 0));
        pushButton->setText(QApplication::translate("MainWindow", "add pos to list", 0));
        label->setText(QApplication::translate("MainWindow", "video", 0));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "GroupBox", 0));
        label_2->setText(QApplication::translate("MainWindow", "pitch:", 0));
        label_4->setText(QApplication::translate("MainWindow", "real_pos:", 0));
        label_3->setText(QApplication::translate("MainWindow", "yaw:", 0));
        label_5->setText(QApplication::translate("MainWindow", "set_pos:", 0));
        groupBox_6->setTitle(QApplication::translate("MainWindow", "board_grid", 0));
        label_6->setText(QApplication::translate("MainWindow", "width:", 0));
        label_7->setText(QApplication::translate("MainWindow", "height", 0));
        checkBox_show_check->setText(QApplication::translate("MainWindow", "showcheck", 0));
        tabWidget->setTabText(tabWidget->indexOf(Tab1), QApplication::translate("MainWindow", "video", 0));
        pushButton_save_lists->setText(QApplication::translate("MainWindow", "sava_lists", 0));
        pushButton_read_lists->setText(QApplication::translate("MainWindow", "read_lists", 0));
        radioButton_list1->setText(QApplication::translate("MainWindow", "list1", 0));
        radioButton_list2->setText(QApplication::translate("MainWindow", "list2", 0));
        radioButton_list3->setText(QApplication::translate("MainWindow", "list3", 0));
        pushButton_clear_record->setText(QApplication::translate("MainWindow", "clear record", 0));
        pushButton_chk_crn_distr->setText(QApplication::translate("MainWindow", "chk crn distr", 0));
        tabWidget->setTabText(tabWidget->indexOf(Tab2), QApplication::translate("MainWindow", "PanTiltSetting", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
