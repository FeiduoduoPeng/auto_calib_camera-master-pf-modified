#ifndef _DATA_TRANSFER_H
#define	_DATA_TRANSFER_H

#include <stdint.h>
#include <QSerialPort>
#include <QTimer>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#define  B_TIME_TO_SEND            0x01
#define  M_SPEED_TO_SEND           0x02
#define  M_CURRENT_TO_SEND         0x03
#define  M_POSATION_TO_SEND        0x04
#define  M_PID_POSATION_TO_SEND    0x05
#define  M_PID_SPEED_TO_SEND       0x06
#define  M_PID_CURRENT_TO_SEND     0x07
#define  M_RUN_MODE_SWITCH_TO_SEND 0x08
#define  M_RUN_STATUES             0x09
#define  M_UPDATA                  0x10
#define  M_SET_CAN_ID              0x11
#define  M_BACK_DATA               0x12

#define  M_BACK_DATA_HALL               0X01
#define  M_BACK_DATA_PID                0X02
#define  M_BACK_DATA_CAN_ID             0X03


#define MOTO_STATUES_CALIB_HALL                        0x01
#define MOTO_STATUES_STOP                              0x02
#define MOTO_STATUES_RUN                               0x03

#define MOTO_MODE_RUN_PWM                              0x11
#define MOTO_MODE_RUN_SPEED_PID                        0x12
#define MOTO_MODE_RUN_CURRENT_PID                      0x13
#define MOTO_MODE_RUN_SPEED_CURRENT_PID                0x14
#define MOTO_MODE_RUN_POSATION_SPEED_PID               0x15
#define MOTO_MODE_RUN_POSATION_SPEED_CURRENT_PID       0x16

extern bool ReachFlag;
typedef enum {
   init_system_data_error    =1,
   Jack_door_init_error,
   Jack_motor_init_error,
   Slide_motor_init_error,
   osThreadCreate_error,
   add_goods_num_error,
   add_layer_error,
   add_goods_senser_no_check,
   sell_goods_num_error,
   sell_layer_error,
   sell_over_time_error,
   sell_goods_seizing_error,
   check_Goods_over_time_error,
   Calib_Step_Enc_error,
   Turntable_Location_error,
   can_online_check_error,
   open_clock_overtime_error,
   close_clock_overtime_error,
   open_door_overtime_error,
   close_door_overtime_error,
   sell_goods_senser_error,
   Turntable_Find_Senser_error
}erro_code_num;

enum serial_cmd
{
    CMD_SELL     =        0x11,
    CMD_ASK_SUCCESS      ,
    CMD_HEART_BEAT_DATA  ,
    CMD_ADD_GOODS        ,
    CMD_SELL_SUCCESS     ,
    CMD_ERROR_CODE       ,
    CMD_LED_CTRL_CODE    ,
    CMD_POWER_OFF        ,
    CMD_START_ADD_GOODS  ,
    CMD_END_ADD_GOODS    ,
    CMD_ADD_GOODS_KEY    ,
    CMD_ASK_GOODS_INFO   ,
    CMD_GOODS_INFO       ,
    CMD_SYS_UPDATE       ,
    CMD_SYS_INIT         ,
    CMD_SYS_POWER_CMD    ,
    CMD_TOUCH_EVENT      ,
    CMD_POWER_OFF_EVENT  ,
      CMD_ASK_VERSION      ,
      CMD_BOSOM_LED_CODE
};

enum serial_dbg_cmd
{
    CMD_CALIB_TURNTABLE = 0xd0,
    CMD_READ_TURNTABLE_DATA,
    CMD_WRITE_TURNTABLE_DATA,

    CMD_CALIB_JACK_DATA,
    CMD_WRITE_JACK_DATA,
    CMD_READ_JACK_DATA,

    CMD_CALIB_DOOR_DATA,
    CMD_WRITE_DOOR_DATA,
    CMD_READ_DOOR_DATA,

    CMD_READ_MOTOR_DATA,
    CMD_WRITE_MOTO_DATA,
    CMD_WRITE_TO_FLASH,
    CMD_TEST_SENSER,
    CMD_STOP_TEST_SENSER
};

typedef struct
{

short turntable_speed[4];
short turntable_current[4];

short jack_speed;
short jack_current;
short door_speed;
short door_current;
short slide_speed;
short slide_current;

}motor_data;
typedef struct
{
  uint32_t u32_Oline_Check;//在线监测
    uint8_t  u8_turntable_status;//转盘状态第0-3位分别代表0-3层状态
    uint8_t  u8_jack_status; //拖链状态，共三种状态
    uint8_t  u8_slide_status;//滑轨状态
    uint8_t  u8_sys_status;//系统状态
    uint8_t  u8_door_lock_statue;
    uint8_t  u8_door_run_step;//门运行到那一步
  uint8_t  u8_power;//电量
    uint8_t  u8_is_charge;//是否在充电

}sell_data_t;



extern QSerialPort *serial;



typedef struct
{
	
	uint32_t u32_mcu_time_save;
	uint32_t u32_mcu_time_send;
	uint32_t computer_time;
}dt_Car_Time_t;
typedef struct 
{
		unsigned char send_version;
		unsigned char send_status;
		unsigned char send_senser;
		unsigned char send_pid1;
		unsigned char send_pid2;
		unsigned char send_pid3;
		unsigned char send_pid4;
		unsigned char send_pid5;
		unsigned char send_pid6;
		unsigned char send_rcdata;
		unsigned char send_offset;
		unsigned char send_motopwm;
		unsigned char send_time;

}dt_flag_t;
typedef struct
{
	uint32_t u32_first_time;
	uint32_t u32_time;
	float	   f_Set_hitSpeed;
	float	   f_hitSpeed;
	float	   f_hit_posation;
}Hit_Data_TypeDef;

typedef struct
{
    uint8_t	   Hall[6];
    float	   f_Voltage;
    float	   f_Temperature;
    float	   f_Current;
    float	   f_Run_Speed;
    float	   f_Run_posation;
}Moto_Data_inf_TypeDef;

extern dt_flag_t f;
extern Moto_Data_inf_TypeDef Moto_Data_inf;
void Motor_DT_Data_Receive_Anl(unsigned char *data_buf, unsigned char num);
void Motor_DT_Data_Exchange(void);
void Motor_DT_Data_Receive_Prepare(unsigned char data);

void Motor_DT_Data_Receive_Anl(unsigned char *data_buf, unsigned char num);
void Motor_DT_Get_Delta_T(unsigned char Sys_Time);
void Motor_DT_Send_Struct(void *Struct_Data,int length, unsigned char function);
void Motor_DT_Send_PID(unsigned char group,float p1_p,float p1_i,float p1_d,float p2_p
,float p2_i,float p2_d,float p3_p,float p3_i,float p3_d);
void set_pos(float x,float y);
void mytest();

#endif

