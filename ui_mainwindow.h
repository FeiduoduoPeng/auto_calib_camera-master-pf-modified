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
    QWidget *TabBino;
    QLabel *Bino_left_show;
    QLabel *Bino_right_show;
    QPushButton *pushButton_open_bino;
    QPushButton *pushButton_save_bino;
    QPushButton *pushButton_start_calib_bino;
    QPushButton *pushButton_clear_bino;
    QLabel *Bino_left_rectified;
    QPushButton *pushButton_show_rectified;
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
    QPushButton *pushButton_2;
    QPushButton *pushButton_init;
    QPushButton *pushButton_move_forward;
    QPushButton *pushButton_backward;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1128, 819);
        MainWindow->setMinimumSize(QSize(640, 480));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_6 = new QGridLayout(centralWidget);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
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
        radioButton_IR->setChecked(false);

        gridLayout->addWidget(radioButton_IR, 0, 0, 1, 1);

        radioButton_color = new QRadioButton(groupBox_2);
        radioButton_color->setObjectName(QStringLiteral("radioButton_color"));
        radioButton_color->setChecked(true);

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
        radioButton_select_color_calib->setChecked(true);

        gridLayout_3->addWidget(radioButton_select_color_calib, 0, 0, 1, 1);

        pushButton_start_calib = new QPushButton(groupBox_3);
        pushButton_start_calib->setObjectName(QStringLiteral("pushButton_start_calib"));

        gridLayout_3->addWidget(pushButton_start_calib, 4, 0, 1, 1);

        pushButton_clean = new QPushButton(groupBox_3);
        pushButton_clean->setObjectName(QStringLiteral("pushButton_clean"));

        gridLayout_3->addWidget(pushButton_clean, 2, 0, 1, 1);

        radioButton_select_ir_calib = new QRadioButton(groupBox_3);
        radioButton_select_ir_calib->setObjectName(QStringLiteral("radioButton_select_ir_calib"));
        radioButton_select_ir_calib->setChecked(false);

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
        TabBino = new QWidget();
        TabBino->setObjectName(QStringLiteral("TabBino"));
        Bino_left_show = new QLabel(TabBino);
        Bino_left_show->setObjectName(QStringLiteral("Bino_left_show"));
        Bino_left_show->setGeometry(QRect(90, 0, 381, 211));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Bino_left_show->sizePolicy().hasHeightForWidth());
        Bino_left_show->setSizePolicy(sizePolicy1);
        Bino_right_show = new QLabel(TabBino);
        Bino_right_show->setObjectName(QStringLiteral("Bino_right_show"));
        Bino_right_show->setGeometry(QRect(500, 0, 381, 211));
        sizePolicy1.setHeightForWidth(Bino_right_show->sizePolicy().hasHeightForWidth());
        Bino_right_show->setSizePolicy(sizePolicy1);
        pushButton_open_bino = new QPushButton(TabBino);
        pushButton_open_bino->setObjectName(QStringLiteral("pushButton_open_bino"));
        pushButton_open_bino->setGeometry(QRect(30, 520, 101, 31));
        pushButton_save_bino = new QPushButton(TabBino);
        pushButton_save_bino->setObjectName(QStringLiteral("pushButton_save_bino"));
        pushButton_save_bino->setGeometry(QRect(30, 560, 101, 31));
        pushButton_start_calib_bino = new QPushButton(TabBino);
        pushButton_start_calib_bino->setObjectName(QStringLiteral("pushButton_start_calib_bino"));
        pushButton_start_calib_bino->setGeometry(QRect(30, 600, 101, 31));
        pushButton_clear_bino = new QPushButton(TabBino);
        pushButton_clear_bino->setObjectName(QStringLiteral("pushButton_clear_bino"));
        pushButton_clear_bino->setGeometry(QRect(30, 640, 101, 31));
        Bino_left_rectified = new QLabel(TabBino);
        Bino_left_rectified->setObjectName(QStringLiteral("Bino_left_rectified"));
        Bino_left_rectified->setGeometry(QRect(80, 280, 771, 211));
        pushButton_show_rectified = new QPushButton(TabBino);
        pushButton_show_rectified->setObjectName(QStringLiteral("pushButton_show_rectified"));
        pushButton_show_rectified->setGeometry(QRect(150, 640, 91, 31));
        tabWidget->addTab(TabBino, QString());
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
        pushButton_2 = new QPushButton(Tab2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(530, 510, 91, 31));
        pushButton_init = new QPushButton(Tab2);
        pushButton_init->setObjectName(QStringLiteral("pushButton_init"));
        pushButton_init->setGeometry(QRect(530, 470, 91, 31));
        pushButton_move_forward = new QPushButton(Tab2);
        pushButton_move_forward->setObjectName(QStringLiteral("pushButton_move_forward"));
        pushButton_move_forward->setGeometry(QRect(420, 510, 91, 31));
        pushButton_backward = new QPushButton(Tab2);
        pushButton_backward->setObjectName(QStringLiteral("pushButton_backward"));
        pushButton_backward->setGeometry(QRect(420, 470, 91, 31));
        tabWidget->addTab(Tab2, QString());

        gridLayout_6->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1128, 28));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        PortBox->setCurrentIndex(-1);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "\344\270\262\345\217\243\350\256\276\347\275\256", 0));
        BaudBox->clear();
        BaudBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "115200", 0)
         << QApplication::translate("MainWindow", "57600", 0)
         << QApplication::translate("MainWindow", "9600", 0)
        );
        pushButton_open_serial->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\344\270\262\345\217\243", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "\346\230\276\347\244\272\350\256\276\347\275\256", 0));
        radioButton_IR->setText(QApplication::translate("MainWindow", "\347\272\242\345\244\226\345\216\237\345\233\276", 0));
        radioButton_color->setText(QApplication::translate("MainWindow", "\345\275\251\350\211\262\345\216\237\345\233\276", 0));
        pushButton_open_camera->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\347\233\270\346\234\272", 0));
        radioButton_IR_calib->setText(QApplication::translate("MainWindow", "\345\267\262\346\240\241\346\255\243\347\272\242\345\244\226\345\233\276", 0));
        radioButton_color_calib->setText(QApplication::translate("MainWindow", "\345\267\262\346\240\241\346\255\243\345\275\251\350\211\262\345\233\276", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "\346\240\241\346\255\243\351\200\211\351\241\271", 0));
        radioButton_select_color_calib->setText(QApplication::translate("MainWindow", "\346\240\241\346\255\243\345\275\251\350\211\262\345\233\276", 0));
        pushButton_start_calib->setText(QApplication::translate("MainWindow", "\350\207\252\345\212\250\345\274\200\345\247\213", 0));
        pushButton_clean->setText(QApplication::translate("MainWindow", "\346\270\205\351\231\244\346\211\200\346\234\211\345\233\276\347\211\207", 0));
        radioButton_select_ir_calib->setText(QApplication::translate("MainWindow", "\346\240\241\346\255\243\347\272\242\345\244\226\345\233\276", 0));
        pushButton_save_image->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\345\275\223\345\211\215\345\233\276\347\211\207", 0));
        pushButton_read_image_list->setText(QApplication::translate("MainWindow", "\345\215\225 \346\240\241\346\255\243\345\233\276\345\203\217", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "\347\233\270\346\234\272\344\275\215\345\247\277", 0));
        pushButton->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240\344\275\215\345\247\277", 0));
        label->setText(QApplication::translate("MainWindow", "video", 0));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "\347\212\266\346\200\201", 0));
        label_2->setText(QApplication::translate("MainWindow", "\344\277\257\344\273\260\350\247\222:", 0));
        label_4->setText(QApplication::translate("MainWindow", "\345\275\223\345\211\215\344\275\215\345\247\277:", 0));
        label_3->setText(QApplication::translate("MainWindow", "\346\250\252\346\273\232\350\247\222:", 0));
        label_5->setText(QApplication::translate("MainWindow", "\347\233\256\346\240\207\344\275\215\345\247\277:", 0));
        groupBox_6->setTitle(QApplication::translate("MainWindow", "\345\237\272\346\234\254\350\256\276\347\275\256:", 0));
        label_6->setText(QApplication::translate("MainWindow", "\350\247\222\347\202\271\345\256\275\346\225\260:", 0));
        label_7->setText(QApplication::translate("MainWindow", "\347\204\246\347\202\271\351\253\230\346\225\260:", 0));
        checkBox_show_check->setText(QApplication::translate("MainWindow", "\345\256\236\346\227\266\350\247\222\347\202\271", 0));
        tabWidget->setTabText(tabWidget->indexOf(Tab1), QApplication::translate("MainWindow", "\345\233\276\345\203\217", 0));
        Bino_left_show->setText(QApplication::translate("MainWindow", "BinoLeft", 0));
        Bino_right_show->setText(QApplication::translate("MainWindow", "BinoRight", 0));
        pushButton_open_bino->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\345\217\214\347\233\256", 0));
        pushButton_save_bino->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\345\217\214\347\233\256", 0));
        pushButton_start_calib_bino->setText(QApplication::translate("MainWindow", "\346\240\207\345\256\232", 0));
        pushButton_clear_bino->setText(QApplication::translate("MainWindow", "\346\270\205\351\231\244\345\217\214\347\233\256", 0));
        Bino_left_rectified->setText(QApplication::translate("MainWindow", "Rectified", 0));
        pushButton_show_rectified->setText(QApplication::translate("MainWindow", "\347\237\253\346\255\243\346\225\210\346\236\234", 0));
        tabWidget->setTabText(tabWidget->indexOf(TabBino), QApplication::translate("MainWindow", "\345\217\214\347\233\256", 0));
        pushButton_save_lists->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\345\210\227\350\241\250", 0));
        pushButton_read_lists->setText(QApplication::translate("MainWindow", "\350\257\273\345\217\226\345\210\227\350\241\250", 0));
        radioButton_list1->setText(QApplication::translate("MainWindow", "\345\210\227\350\241\2501", 0));
        radioButton_list2->setText(QApplication::translate("MainWindow", "\345\210\227\350\241\2502", 0));
        radioButton_list3->setText(QApplication::translate("MainWindow", "\345\210\227\350\241\2503", 0));
        pushButton_clear_record->setText(QApplication::translate("MainWindow", "\346\270\205\351\231\244", 0));
        pushButton_chk_crn_distr->setText(QApplication::translate("MainWindow", "\350\247\222\347\202\271\345\210\206\345\270\203", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "\345\201\234\346\255\242\347\247\273\345\212\250", 0));
        pushButton_init->setText(QApplication::translate("MainWindow", "\345\210\235\345\247\213\344\275\215\347\275\256", 0));
        pushButton_move_forward->setText(QApplication::translate("MainWindow", "\346\240\207\345\256\232\346\235\277\345\211\215\350\277\233", 0));
        pushButton_backward->setText(QApplication::translate("MainWindow", "\346\240\207\345\256\232\346\235\277\345\220\216\351\200\200", 0));
        tabWidget->setTabText(tabWidget->indexOf(Tab2), QApplication::translate("MainWindow", "\350\256\276\347\275\256\344\270\216\346\243\200\346\237\245", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
