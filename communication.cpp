#include "communication.h"
#include "mainwindow.h"
#include <iomanip>
#include <iostream>
#include <stdio.h>  
#include <string.h>
#include <fstream>
#include "mainwindow.h"

using namespace std;
QSerialPort *serial;
extern Ui::MainWindow *my_ui;
/////////////////////////////////////////////////////////////////////////////////////
//数据拆分宏定义，在发送大于1字节的数据类型时，比如int16、float等，需要把数据拆分成单独字节进行发送
#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)		) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )
#define u8 unsigned char
#define vs16 volatile int16_t
//#define uint8_t unsigned char
dt_flag_t f;			//需要发送数据的标志
//dt_Car_Data_t Car;
Moto_Data_inf_TypeDef Moto_Data_inf;
/////////////////////////////////////////////////////////////////////////////////////
//Data_Exchange函数处理各种数据发送请求，比如想实现每5ms发送一次传感器数据至上位机，即在此函数内实现
//此函数应由用户每1ms调用一次

	static u8 senser_cnt 	= 10;
    void Motor_DT_Data_Exchange(void)
    {
        static uint16_t cnt     = 0;
	static u8 status_cnt 	= 15;
	static u8 rcdata_cnt 	= 20;
	static u8 motopwm_cnt	= 20;
	static u8 time_cnt		= 50;

	if((cnt % senser_cnt) == (senser_cnt-1))
		f.send_senser = 1;

	if((cnt % status_cnt) == (status_cnt-1))
		f.send_status = 1;

	if((cnt % rcdata_cnt) == (rcdata_cnt-1))
		f.send_rcdata = 1;

	if((cnt % motopwm_cnt) == (motopwm_cnt-1))
		f.send_motopwm = 1;	

	if ((cnt % time_cnt) == (time_cnt - 1))
		f.send_time = 1;
	cnt++;

/////////////////////////////////////////////////////////////////////////////////////
	 if(f.send_time)//时间同步发送
	{
		f.send_time = 0;
	}
/////////////////////////////////////////////////////////////////////////////////////
	else if(f.send_pid1)
	{
		f.send_pid1 = 0;
    }
/////////////////////////////////////////////////////////////////////////////////////
	else if(f.send_pid2)
	{
	}
/////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////
//Send_Data函数是协议中所有发送数据功能使用到的发送函数
void Motor_DT_Send_Data(u8 *dataToSend , u8 length)
{
    serial->write((const char *)dataToSend,length);
}

static void Motor_DT_Send_Check(u8 head, u8 check_sum)
{
	uint8_t data_to_send[50];
	data_to_send[0]=0xAA;
	data_to_send[1]=0xAF;
	data_to_send[2]=0xEF;
	data_to_send[3]=2;
	data_to_send[4]=head;
	data_to_send[5]=check_sum;

	u8 sum = 0;
	for(u8 i=0;i<6;i++)
		sum += data_to_send[i];
	data_to_send[6]=sum;
	Motor_DT_Send_Data(data_to_send, 7);
}

/////////////////////////////////////////////////////////////////////////////////////
//Data_Receive_Prepare函数是协议预解析，根据协议的格式，将收到的数据进行一次格式性解析，格式正确的话再进行数据解析
//移植时，此函数应由用户根据自身使用的通信方式自行调用，比如串口每收到一字节数据，则调用此函数一次
//此函数解析出符合格式的数据帧后，会自行调用数据解析函数

void Motor_DT_Data_Receive_Prepare(u8 data)
{
	static u8 RxBuffer[50];
	static u8 _data_len = 0,_data_cnt = 0;
	static u8 state = 0;
	if(state==0&&data==0xAA)
	{
		state=1;
		RxBuffer[0]=data;
	}
	else if(state==1&&data==0xAA)
	{
		state=2;
		RxBuffer[1]=data;
	}
	else if(state==2&&data<0XF1)
	{
		state=3;
		RxBuffer[2]=data;
	}
	else if(state==3&&data<50)
	{
		state = 4;
		RxBuffer[3]=data;
		_data_len = data;
		_data_cnt = 0;
	}
	else if(state==4&&_data_len>0)
	{
		_data_len--;
		RxBuffer[4+_data_cnt++]=data;
		if(_data_len==0)
			state = 5;
	}
	else if(state==5)
	{
		state = 0;
		RxBuffer[4+_data_cnt]=data;
		Motor_DT_Data_Receive_Anl(RxBuffer,_data_cnt+5);
	}
	else
		state = 0;
}
/////////////////////////////////////////////////////////////////////////////////////
//Data_Receive_Anl函数是协议数据解析函数，函数参数是符合协议格式的一个数据帧，该函数会首先对协议数据进行校验
//校验通过后对数据进行解析，实现相应功能
//此函数可以不用用户自行调用，由函数Data_Receive_Prepare自动调用
void Motor_DT_Data_Receive_Anl(u8 *data_buf,u8 num)
{
	u8 sum = 0;
	for(u8 i=0;i<(num-1);i++)
		sum += *(data_buf+i);
	if(!(sum==*(data_buf+num-1)))		
		return;		//判断sum
    if(!(*(data_buf)==0xAA && *(data_buf+1)==0xAA))
		return;		//判断帧头

    if (*(data_buf + 2) ==0x14)
    {
        float data[2];
        memcpy(&data, data_buf + 4,8);
        my_ui->lcdNumber_imu_x->display(data[1]);
        my_ui->lcdnumber_imu_y->display(data[0]);
    }
    else if(*(data_buf+2) == 0x15){
        float data[2];
        memcpy(&data, data_buf + 4,8);
        //if reach target point, stop servo
        if(data[0] ==1){
            int data[2];
            data[0]=1;
            Motor_DT_Send_Struct((uint8_t *)data,8,0x15);
        }
        //std::cout<<data[0]<<std::endl;
    }
    else if (*(data_buf + 2) == CMD_ADD_GOODS_KEY)
    {
        uint8_t data;
        memcpy(&data, data_buf + 4,1);
        data=CMD_ADD_GOODS_KEY;
        Motor_DT_Send_Struct(&data,1 ,0x12);
    }
}

/**
  * @brief  Motor_DT_Send_Struct 
  * @param  *Struct_Data  要发送的结构体
            length 结构体大小
             function     功能字
  * @retval void
  */
void Motor_DT_Send_Struct(void *Struct_Data,int length ,u8 function)
{
	u8 _cnt=0;
	u8 sum = 0;
    static uint8_t data_to_send[50];	//发送数据缓存

	data_to_send[0]=0xAA;
	data_to_send[1]=0xAF;
	data_to_send[2]=function;
	data_to_send[3]=length;
    memcpy(&data_to_send[4], Struct_Data,length);
    _cnt=data_to_send[3]+4;

	for(u8 i=0;i<_cnt;i++)
		sum += data_to_send[i];
	data_to_send[_cnt++]=sum;
	Motor_DT_Send_Data(data_to_send, _cnt);
}
void set_pos(float x,float y)
{
  float data[2];
  if(x>60)
      x=60;
  if(x<-60)
      x=-60;

  if(y>60)
      y=60;
  if(y<-60)
      y=-60;
  data[0] = y;
  data[1] = x;
  Motor_DT_Send_Struct((uint8_t *)data,8,0x13);
}

/******************* (C) COPYRIGHT 2014 Motor TECH *****END OF FILE************/
