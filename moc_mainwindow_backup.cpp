/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[46];
    char stringdata0[1121];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 6), // "accept"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 3), // "msg"
QT_MOC_LITERAL(4, 23, 33), // "on_pushButton_open_camera_cli..."
QT_MOC_LITERAL(5, 57, 32), // "on_pushButton_save_image_clicked"
QT_MOC_LITERAL(6, 90, 33), // "on_pushButton_open_serial_cli..."
QT_MOC_LITERAL(7, 124, 37), // "on_pushButton_read_image_list..."
QT_MOC_LITERAL(8, 162, 27), // "on_pushButton_clean_clicked"
QT_MOC_LITERAL(9, 190, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(10, 212, 33), // "on_pushButton_start_calib_cli..."
QT_MOC_LITERAL(11, 246, 13), // "handleTimeout"
QT_MOC_LITERAL(12, 260, 16), // "binoTimerHandler"
QT_MOC_LITERAL(13, 277, 12), // "checkHandler"
QT_MOC_LITERAL(14, 290, 16), // "servoMoveForward"
QT_MOC_LITERAL(15, 307, 17), // "servoMoveBackward"
QT_MOC_LITERAL(16, 325, 9), // "servoStop"
QT_MOC_LITERAL(17, 335, 13), // "servoInitStop"
QT_MOC_LITERAL(18, 349, 21), // "recoverCheckTimerSlot"
QT_MOC_LITERAL(19, 371, 32), // "on_pushButton_read_lists_clicked"
QT_MOC_LITERAL(20, 404, 32), // "on_pushButton_save_lists_clicked"
QT_MOC_LITERAL(21, 437, 24), // "on_Slider_y_valueChanged"
QT_MOC_LITERAL(22, 462, 5), // "value"
QT_MOC_LITERAL(23, 468, 24), // "on_Slider_x_valueChanged"
QT_MOC_LITERAL(24, 493, 28), // "on_radioButton_list1_clicked"
QT_MOC_LITERAL(25, 522, 28), // "on_radioButton_list2_clicked"
QT_MOC_LITERAL(26, 551, 28), // "on_radioButton_list3_clicked"
QT_MOC_LITERAL(27, 580, 25), // "on_radioButton_IR_toggled"
QT_MOC_LITERAL(28, 606, 7), // "checked"
QT_MOC_LITERAL(29, 614, 28), // "on_radioButton_color_toggled"
QT_MOC_LITERAL(30, 643, 34), // "on_pushButton_clear_record_cl..."
QT_MOC_LITERAL(31, 678, 31), // "on_radioButton_IR_calib_clicked"
QT_MOC_LITERAL(32, 710, 26), // "on_tabWidget_tabBarClicked"
QT_MOC_LITERAL(33, 737, 5), // "index"
QT_MOC_LITERAL(34, 743, 27), // "on_tabWidget_currentChanged"
QT_MOC_LITERAL(35, 771, 31), // "on_pushButton_open_bino_clicked"
QT_MOC_LITERAL(36, 803, 31), // "on_pushButton_save_bino_clicked"
QT_MOC_LITERAL(37, 835, 32), // "on_pushButton_clear_bino_clicked"
QT_MOC_LITERAL(38, 868, 38), // "on_pushButton_start_calib_bin..."
QT_MOC_LITERAL(39, 907, 35), // "on_pushButton_chk_crn_distr_c..."
QT_MOC_LITERAL(40, 943, 36), // "on_pushButton_show_rectified_..."
QT_MOC_LITERAL(41, 980, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(42, 1004, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(43, 1028, 26), // "on_pushButton_init_clicked"
QT_MOC_LITERAL(44, 1055, 34), // "on_pushButton_move_forward_cl..."
QT_MOC_LITERAL(45, 1090, 30) // "on_pushButton_backward_clicked"

    },
    "MainWindow\0accept\0\0msg\0"
    "on_pushButton_open_camera_clicked\0"
    "on_pushButton_save_image_clicked\0"
    "on_pushButton_open_serial_clicked\0"
    "on_pushButton_read_image_list_clicked\0"
    "on_pushButton_clean_clicked\0"
    "on_pushButton_clicked\0"
    "on_pushButton_start_calib_clicked\0"
    "handleTimeout\0binoTimerHandler\0"
    "checkHandler\0servoMoveForward\0"
    "servoMoveBackward\0servoStop\0servoInitStop\0"
    "recoverCheckTimerSlot\0"
    "on_pushButton_read_lists_clicked\0"
    "on_pushButton_save_lists_clicked\0"
    "on_Slider_y_valueChanged\0value\0"
    "on_Slider_x_valueChanged\0"
    "on_radioButton_list1_clicked\0"
    "on_radioButton_list2_clicked\0"
    "on_radioButton_list3_clicked\0"
    "on_radioButton_IR_toggled\0checked\0"
    "on_radioButton_color_toggled\0"
    "on_pushButton_clear_record_clicked\0"
    "on_radioButton_IR_calib_clicked\0"
    "on_tabWidget_tabBarClicked\0index\0"
    "on_tabWidget_currentChanged\0"
    "on_pushButton_open_bino_clicked\0"
    "on_pushButton_save_bino_clicked\0"
    "on_pushButton_clear_bino_clicked\0"
    "on_pushButton_start_calib_bino_clicked\0"
    "on_pushButton_chk_crn_distr_clicked\0"
    "on_pushButton_show_rectified_clicked\0"
    "on_pushButton_2_clicked\0on_pushButton_3_clicked\0"
    "on_pushButton_init_clicked\0"
    "on_pushButton_move_forward_clicked\0"
    "on_pushButton_backward_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      40,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,  214,    2, 0x0a /* Public */,
       4,    0,  217,    2, 0x08 /* Private */,
       5,    0,  218,    2, 0x08 /* Private */,
       6,    0,  219,    2, 0x08 /* Private */,
       7,    0,  220,    2, 0x08 /* Private */,
       8,    0,  221,    2, 0x08 /* Private */,
       9,    0,  222,    2, 0x08 /* Private */,
      10,    0,  223,    2, 0x08 /* Private */,
      11,    0,  224,    2, 0x08 /* Private */,
      12,    0,  225,    2, 0x08 /* Private */,
      13,    0,  226,    2, 0x08 /* Private */,
      14,    0,  227,    2, 0x08 /* Private */,
      15,    0,  228,    2, 0x08 /* Private */,
      16,    0,  229,    2, 0x08 /* Private */,
      17,    0,  230,    2, 0x08 /* Private */,
      18,    0,  231,    2, 0x08 /* Private */,
      19,    0,  232,    2, 0x08 /* Private */,
      20,    0,  233,    2, 0x08 /* Private */,
      21,    1,  234,    2, 0x08 /* Private */,
      23,    1,  237,    2, 0x08 /* Private */,
      24,    0,  240,    2, 0x08 /* Private */,
      25,    0,  241,    2, 0x08 /* Private */,
      26,    0,  242,    2, 0x08 /* Private */,
      27,    1,  243,    2, 0x08 /* Private */,
      29,    1,  246,    2, 0x08 /* Private */,
      30,    0,  249,    2, 0x08 /* Private */,
      31,    0,  250,    2, 0x08 /* Private */,
      32,    1,  251,    2, 0x08 /* Private */,
      34,    1,  254,    2, 0x08 /* Private */,
      35,    0,  257,    2, 0x08 /* Private */,
      36,    0,  258,    2, 0x08 /* Private */,
      37,    0,  259,    2, 0x08 /* Private */,
      38,    0,  260,    2, 0x08 /* Private */,
      39,    0,  261,    2, 0x08 /* Private */,
      40,    0,  262,    2, 0x08 /* Private */,
      41,    0,  263,    2, 0x08 /* Private */,
      42,    0,  264,    2, 0x08 /* Private */,
      43,    0,  265,    2, 0x08 /* Private */,
      44,    0,  266,    2, 0x08 /* Private */,
      45,    0,  267,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   22,
    QMetaType::Void, QMetaType::Int,   22,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   28,
    QMetaType::Void, QMetaType::Bool,   28,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   33,
    QMetaType::Void, QMetaType::Int,   33,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->accept((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->on_pushButton_open_camera_clicked(); break;
        case 2: _t->on_pushButton_save_image_clicked(); break;
        case 3: _t->on_pushButton_open_serial_clicked(); break;
        case 4: _t->on_pushButton_read_image_list_clicked(); break;
        case 5: _t->on_pushButton_clean_clicked(); break;
        case 6: _t->on_pushButton_clicked(); break;
        case 7: _t->on_pushButton_start_calib_clicked(); break;
        case 8: _t->handleTimeout(); break;
        case 9: _t->binoTimerHandler(); break;
        case 10: _t->checkHandler(); break;
        case 11: _t->servoMoveForward(); break;
        case 12: _t->servoMoveBackward(); break;
        case 13: _t->servoStop(); break;
        case 14: _t->servoInitStop(); break;
        //case 15: _t->recoverCheckTimerSlot(); break;
        case 16: _t->on_pushButton_read_lists_clicked(); break;
        case 17: _t->on_pushButton_save_lists_clicked(); break;
        case 18: _t->on_Slider_y_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->on_Slider_x_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->on_radioButton_list1_clicked(); break;
        case 21: _t->on_radioButton_list2_clicked(); break;
        case 22: _t->on_radioButton_list3_clicked(); break;
        case 23: _t->on_radioButton_IR_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: _t->on_radioButton_color_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 25: _t->on_pushButton_clear_record_clicked(); break;
        case 26: _t->on_radioButton_IR_calib_clicked(); break;
        case 27: _t->on_tabWidget_tabBarClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 28: _t->on_tabWidget_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: _t->on_pushButton_open_bino_clicked(); break;
        case 30: _t->on_pushButton_save_bino_clicked(); break;
        case 31: _t->on_pushButton_clear_bino_clicked(); break;
        case 32: _t->on_pushButton_start_calib_bino_clicked(); break;
        case 33: _t->on_pushButton_chk_crn_distr_clicked(); break;
        case 34: _t->on_pushButton_show_rectified_clicked(); break;
        case 35: _t->on_pushButton_2_clicked(); break;
        case 36: _t->on_pushButton_3_clicked(); break;
        case 37: _t->on_pushButton_init_clicked(); break;
        case 38: _t->on_pushButton_move_forward_clicked(); break;
        case 39: _t->on_pushButton_backward_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 40)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 40;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 40)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 40;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
