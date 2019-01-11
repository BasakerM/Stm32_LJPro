#include "function.h"

unsigned char usart_Buff_Send[16] = {0x00};	//串口发送缓冲区
unsigned char bottle_addr = 0xA2;
unsigned char metal_addr = 0xA3;
unsigned char paper_addr = 0xA4;
/*struct bottle_flag
{
	unsigned char bottle_open_door_flag = 0;
}*/

///////////////////////////以下为功能实现,流程逻辑/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////以下为功能实现,流程逻辑/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////以下为功能实现,流程逻辑/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////以下为功能实现,流程逻辑/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////以下为功能实现,流程逻辑/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////以下为功能实现,流程逻辑/////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////瓶子部分功能////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////瓶子部分功能////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////瓶子部分功能////////////////////////////////////////////////////////////////////////////

//
//	瓶子开门事件对应功能流程
//	e_flag : 当前事件
//	c_flag : 当前代码
//
unsigned char bottle_open_door_flag = 0;
void bottle_opendoor(enum enum_event* e_flag,unsigned char* buff)
{
	if(bottle_open_door_flag)	//非首次进入
	{
		if(device_status_get(bottle_sensor_opendoor) == open)	//检查限位器状态
		{	//已开门
			bottle_open_door_flag = 0;
			motor_ctrl(bottle_motor_door,run_s);	//停止转动
			timeout_end();	//关闭超时
			usart_ack(usart_Buff_Send,bottle_addr,0xb2,0xff,0xff);	//发送成功消息
			*e_flag = event_bottle_put;	//切换事件到放入
		}
		else if(timeout_status_get())	//检查超时状态
		{
			//已超时
			bottle_open_door_flag = 0;
			motor_ctrl(bottle_motor_door,run_s);	//停止转动
			timeout_end();
			usart_ack(usart_Buff_Send,bottle_addr,0xb2,0x00,0x00);	//发送失败消息
			*e_flag = event_none;	//切换事件到none
		}
	}
	else	//首次进入
	{
		bottle_open_door_flag = 1;
		usart_ack(usart_Buff_Send,bottle_addr,0xb1,0x00,0x00);	//发送响应
		timeout_start(OPEN_DOOR_DELAY);	//开启超时
		motor_ctrl(bottle_motor_door,run_z);	//开门--正转
	}
}

//
//	瓶子放入事件对应功能流程
//
unsigned char bottle_put_flag = 0;
void bottle_put(enum enum_event* e_flag,unsigned char* buff)
{
	if(bottle_put_flag)
	{
		if(device_status_get(bottle_sensor_one) == on)	//检查光电1状态
		{
			bottle_put_flag = 0;
			timeout_end();
			usart_ack(usart_Buff_Send,bottle_addr,0xb9,0x00,0x00);	//发送刷新消息
			*e_flag = event_bottle_scanfcode;	//切换事件到扫码
		}
		else if(timeout_status_get())	//检查超时状态
		{
			bottle_put_flag = 0;
			timeout_end();
			*e_flag = event_bottle_closedoor;	//切换事件到关门
		}
	}
	else
	{
		bottle_put_flag = 1;
		timeout_start(BOTTLE_PUT_DELAY);	//开启超时
	}
}

//
//	瓶子扫码事件对应功能流程
//
unsigned char bottle_scanfcode_flag = 0;
void bottle_scanfcode(enum enum_event* e_flag,unsigned char* buff)
{
	if(bottle_scanfcode_flag)	
	{
		if(device_status_get(bottle_sensor_two) == on)	//检查光电2状态
		{
			bottle_scanfcode_flag = 0;
			motor_ctrl(bottle_motor_recycle,run_s);	//停止转动
			timeout_end();
			usart_ack(usart_Buff_Send,bottle_addr,0xbb,0x00,0x00);	//发送获取扫码结果消息
			*e_flag = event_bottle_ack;	//切换事件到确认
		}
		else if(timeout_status_get())	//检查超时状态
		{
			bottle_scanfcode_flag = 0;
			motor_ctrl(bottle_motor_recycle,run_s);	//停止转动
			timeout_end();
			*e_flag = event_bottle_put;	//切换事件到放入
		}
	}
	else
	{
		bottle_scanfcode_flag = 1;
		motor_ctrl(bottle_motor_recycle,run_z);	//送入扫码--正转
		timeout_start(SCANF_CODE_DELAY);	//开启超时
	}
}

//
//	瓶子确认事件对应功能流程
//
unsigned char bottle_ack_flag = 0;
void bottle_ack(enum enum_event* e_flag,unsigned char* buff)
{
	if(bottle_ack_flag)	
	{
		if(buff[REC_BUFF_INDEX_CODE] == 0xbc && buff[REC_BUFF_INDEX_DAT0] == 0xff && buff[REC_BUFF_INDEX_DAT1] == 0xff)	//成功
		{
			bottle_ack_flag = 0;
			usart_ack(usart_Buff_Send,bottle_addr,0xbc,0xff,0xff);	//发送响应
			timeout_end();
			buff[1] = 0x00; buff[2] = 0x00; buff[3] = 0x00;
			*e_flag = event_bottle_recycle;	//切换事件到回收
		}
		else if(buff[REC_BUFF_INDEX_CODE] == 0xbc && buff[REC_BUFF_INDEX_DAT0] == 0x00 && buff[REC_BUFF_INDEX_DAT1] == 0x00)	//失败
		{
			bottle_ack_flag = 0;
			usart_ack(usart_Buff_Send,bottle_addr,0xbc,0x00,0x00);	//发送响应
			timeout_end();
			buff[1] = 0x00; buff[2] = 0x00; buff[3] = 0x00;
			*e_flag = event_bottle_fail;	//切换事件到失败
		}
		else if(timeout_status_get())	//检查超时状态
		{
			bottle_ack_flag = 0;
			timeout_end();
			usart_ack(usart_Buff_Send,bottle_addr,0xbd,0x00,0x00);	//发送自己判断为失败的消息
			*e_flag = event_bottle_fail;	//切换事件到失败
		}
	}
	else
	{
		bottle_ack_flag = 1;
		timeout_start(SCANF_CODE_ACK_DELAY);	//开启超时
	}
}

//
//	瓶子回收事件对应功能流程
//
unsigned char bottle_recycle_flag = 0;
void bottle_recycle(enum enum_event* e_flag,unsigned char* buff)
{
	bottle_recycle_flag = 1;
	if(buff[REC_BUFF_INDEX_CODE] == 0xc1) usart_ack(usart_Buff_Send,bottle_addr,0xc1,0x00,0x00);	//强制回收情况下发送应答消息
	timeout_start(RECYCLE_DELAY);	//开启超时
	while(bottle_recycle_flag)	
	{
		motor_ctrl(bottle_motor_recycle,run_z);	//送入扫码--正转
		if(device_status_get(bottle_sensor_three) == on)	//检查光电3状态
		{
			bottle_recycle_flag = 0;
			timeout_end();
			motor_ctrl(bottle_motor_recycle,run_s);	//送入扫码--停止
			if(buff[REC_BUFF_INDEX_CODE] == 0xc1)
			{
				usart_ack(usart_Buff_Send,bottle_addr,0xc2,0xff,0xff);	//强制回收情况下的成功消息
				*e_flag = event_none;	//切换事件到none
			}
			else 
			{
				usart_ack(usart_Buff_Send,bottle_addr,0xBF,0x00,0x00);	//正常回收情况下发送回收成功的消息
				*e_flag = event_bottle_put;	//切换事件到放入
			}
			
		}
		else if(timeout_status_get())	//检查超时状态
		{
			bottle_recycle_flag = 0;
			timeout_end();
			motor_ctrl(bottle_motor_recycle,run_s);	//送入扫码--停止
			if(buff[REC_BUFF_INDEX_CODE] == 0xc1)
			{
				usart_ack(usart_Buff_Send,bottle_addr,0xc2,0x00,0x00);	//强制回收情况下的失败消息
				*e_flag = event_none;	//切换事件到none
			}
			else
			{
				usart_ack(usart_Buff_Send,bottle_addr,0xBF,0x00,0x02);	//正常回收情况下发送回收失败的消息
				*e_flag = event_bottle_put;	//切换事件到放入
			}
		}
	}
}

//
//	瓶子失败事件对应功能流程
//
unsigned char bottle_fail_flag = 0;
void bottle_fail(enum enum_event* e_flag,unsigned char* buff)
{
	if(bottle_fail_flag)
	{
		if(device_status_get(bottle_sensor_two) == off)	//检查光电2状态
		{
			bottle_fail_flag = 0;
			timeout_end();
			usart_ack(usart_Buff_Send,bottle_addr,0xBF,0x00,0x01);	//发送用户取回物品的消息
			*e_flag = event_bottle_put;	//切换事件到放入
		}
		else if(device_status_get(bottle_sensor_two) == on)	//检查光电2状态
		{
			bottle_fail_flag = 0;
			timeout_end();
		}
	}
	else
	{
		bottle_fail_flag = 1;
		timeout_start(FAIL_DELAY);	//开启超时
	}
}

//
//	瓶子关门事件对应功能流程
//
unsigned char bottle_closedoor_flag = 0;
void bottle_closedoor(enum enum_event* e_flag,unsigned char* buff)
{
	if(bottle_closedoor_flag)	//非首次进入
	{
		if(device_status_get(bottle_sensor_closedoor) == close)	//检查限位器状态
		{
			bottle_closedoor_flag = 0;
			motor_ctrl(bottle_motor_door,run_s);	//停止转动
			timeout_end();	//关闭超时
			if(buff[REC_BUFF_INDEX_DAT1] == 0x01) usart_ack(usart_Buff_Send,bottle_addr,0xb4,0xee,0xee);	//发送成功消息(强制回收情况下)
			else usart_ack(usart_Buff_Send,bottle_addr,0xb4,0xff,0xff);	//发送成功消息(正常回收情况下)
			*e_flag = event_none;	//切换事件到none
		}
		else if(timeout_status_get())	//检查超时状态
		{
			bottle_closedoor_flag = 0;
			motor_ctrl(bottle_motor_door,run_s);	//停止转动
			timeout_end();
			if(buff[REC_BUFF_INDEX_DAT1] == 0x01) usart_ack(usart_Buff_Send,bottle_addr,0xb4,0x11,0x11);	//发送失败消息(强制回收情况下)
			else usart_ack(usart_Buff_Send,bottle_addr,0xb4,0x00,0x00);	//发送失败消息(正常回收情况下)
			*e_flag = event_none;	//切换事件到none
		}
	}
	else	//首次进入
	{
		if(device_status_get(bottle_sensor_one) == on)	//检查光电1状态
		{
			usart_ack(usart_Buff_Send,bottle_addr,0xb9,0x00,0x00);	//发送刷新消息
			*e_flag = event_none;	//切换事件到none
			return;
		}
		bottle_closedoor_flag = 1;
		if(buff[REC_BUFF_INDEX_DAT1] == 0x01) usart_ack(usart_Buff_Send,bottle_addr,0xb3,0x00,0x01);	//发送响应(强制回收情况下)
		else usart_ack(usart_Buff_Send,bottle_addr,0xb3,0x00,0x00);	//发送响应
		timeout_start(CLOSE_DOOR_DELAY);	//开启超时
		motor_ctrl(bottle_motor_door,run_f);	//关门--反转
	}
}

//
//	瓶子管理员门开门事件
//
unsigned char bottle_openmanagedoor_flag = 0;
void bottle_manage_opendoor(enum enum_event* e_flag,unsigned char* buff)
{
	if(bottle_openmanagedoor_flag)	//非首次进入
	{
		if(timeout_status_get())
		{
			bottle_openmanagedoor_flag = 0;
			usart_ack(usart_Buff_Send,bottle_addr,0xb6,0xff,0xff);	//发送成功消息
			timeout_end();
			*e_flag = event_none;	//切换事件到none
		}
	}
	else	//首次进入
	{
		bottle_openmanagedoor_flag = 1;
		usart_ack(usart_Buff_Send,bottle_addr,0xb5,0x00,buff[REC_BUFF_INDEX_DAT1]);	//发送响应
		motor_ctrl(bottle_lock,open);	//开管理员门
		timeout_start(1);	//开启超时
	}
}

//
//	瓶子管理员门关门事件
//
unsigned char bottle_closemanagedoor_flag = 0;
void bottle_manage_closedoor(enum enum_event* e_flag,unsigned char* buff)
{
	if(bottle_closemanagedoor_flag)	//非首次进入
	{
		if(timeout_status_get())
		{
			bottle_closemanagedoor_flag = 0;
			usart_ack(usart_Buff_Send,bottle_addr,0xb8,0xff,0xff);	//发送成功消息
			timeout_end();
			*e_flag = event_none;	//切换事件到none
		}
	}
	else	//首次进入
	{
		bottle_closemanagedoor_flag = 1;
		usart_ack(usart_Buff_Send,bottle_addr,0xb7,0x00,buff[REC_BUFF_INDEX_DAT1]);	//发送响应
		motor_ctrl(bottle_lock,close);	//关管理员门
		timeout_start(1);	//开启超时
	}
}

//////////////////////////////////////////////金属部分功能////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////金属部分功能////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////金属部分功能////////////////////////////////////////////////////////////////////////////

//
//	金属开门事件对应功能流程
//	e_flag : 当前事件
//	c_flag : 当前代码
//
unsigned char metal_open_door_flag = 0;
void metal_opendoor(enum enum_event* e_flag,unsigned char* buff)
{
	if(metal_open_door_flag)	//非首次进入
	{
		if(timeout_status_get())	//检查超时状态
		{
			//已超时
			metal_open_door_flag = 0;
			motor_ctrl(metal_motor,run_s);	//停止转动
			timeout_end();
			usart_ack(usart_Buff_Send,metal_addr,0xb2,0xff,0xff);	//发送失败消息
			*e_flag = event_metal_put;	//切换事件到put
		}
	}
	else	//首次进入
	{
		metal_open_door_flag = 1;
		usart_ack(usart_Buff_Send,metal_addr,0xb1,0x00,buff[REC_BUFF_INDEX_DAT1]);	//发送响应
		timeout_start(METAL_OPEN_DOOR_DELAY);	//开启超时
		motor_ctrl(metal_motor,run_z);	//开门--正转
	}
}

//
//	金属放入事件对应功能流程
//
unsigned char metal_put_flag = 0;
void metal_put(enum enum_event* e_flag,unsigned char* buff)
{
	if(metal_put_flag)
	{
		if(device_status_get(metal_sensor) == on && metal_put_flag == 1)	//检查光电1状态
		{
			metal_put_flag = 2;
			timeout_start(2);	//开启超时
			usart_ack(usart_Buff_Send,metal_addr,0xb9,0x00,0x00);	//发送刷新消息
			//*e_flag = event_bottle_scanfcode;	//切换事件到扫码
		}
		else if(timeout_status_get() && metal_put_flag == 2)
		{
			if(device_status_get(metal_sensor) == off)
			{
				metal_put_flag = 1;
				timeout_start(METAL_PUT_DELAY);	//开启超时
			}
			else
			{
				timeout_start(2);	//开启超时
				usart_ack(usart_Buff_Send,metal_addr,0xb9,0x00,0x00);	//发送刷新消息
			}
		}
		else if(timeout_status_get() && metal_put_flag == 1)	//检查超时状态
		{
			metal_put_flag = 0;
			timeout_end();
			*e_flag = event_metal_closedoor;	//切换事件到关门
		}
	}
	else
	{
		metal_put_flag = 1;
		timeout_start(METAL_PUT_DELAY);	//开启超时
	}
}

//
//	金属关门事件对应功能流程
//
unsigned char metal_closedoor_flag = 0;
void metal_closedoor(enum enum_event* e_flag,unsigned char* buff)
{
	if(metal_closedoor_flag)	//非首次进入
	{
		if(timeout_status_get())	//检查超时状态
		{
			metal_closedoor_flag = 0;
			motor_ctrl(metal_motor,run_s);	//停止转动
			timeout_end();
			usart_ack(usart_Buff_Send,metal_addr,0xb4,0xDD,0xDD);	//发送成功消息(正常回收情况下)
			*e_flag = event_none;	//切换事件到none
		}
	}
	else	//首次进入
	{
		metal_closedoor_flag = 1;
		usart_ack(usart_Buff_Send,metal_addr,0xb3,0x00,buff[REC_BUFF_INDEX_DAT1]);	//发送响应
		timeout_start(METAL_CLOSE_DOOR_DELAY);	//开启超时
		motor_ctrl(metal_motor,run_f);	//关门--反转
	}
}

//
//	金属称重事件对应功能流程
//
unsigned long weight_base = 0;
void metal_weigh(enum enum_event* e_flag,unsigned char* buff)
{
	unsigned char s_buff[12] = {0x19,0x19,0x0A,0xA0,0xA1,0xC4,0x00,0x00,0x00,0x00,0x00,0x00};
	unsigned long weight = 0;
	usart_ack(usart_Buff_Send,metal_addr,0xC3,0x00,buff[REC_BUFF_INDEX_DAT1]);	//发送响应
	s_buff[3] = metal_addr;
	s_buff[7] = buff[REC_BUFF_INDEX_DAT1];

	unsigned char times_flag = 0;
	timeout_start(1);	//开启超时
	while(!timeout_status_get())	//等待超时
	{
		if(times_flag == 0)
		{
			times_flag++;
			if((weight = get_weight()) == 0)	//称重失败
			{
				s_buff[8] = 0xff;
				s_buff[9] = 0xff;
				unsigned short crc_result = crc(&s_buff[2],8);
				s_buff[10] = (unsigned char)(crc_result>>8);
				s_buff[11] = (unsigned char)(crc_result&0x00ff);
				usart_send(USART_M,s_buff,12);	//发送失败消息
				return;
			}

		}
	}
	timeout_end();

	if(buff[REC_BUFF_INDEX_DAT1])	//关门后的称重
	{
		weight = get_weight() - weight_base;
		weight *= 41;
		s_buff[8] = (unsigned char)weight>>8;
		s_buff[9] = (unsigned char)(weight&0x00ff);
	}
	else	//开门前的称重
	{
		weight_base = get_weight();	//获取开门前的基准重量
		s_buff[8] = 0x00;	//(unsigned char)weight>>8;
		s_buff[9] = 0x00;	//(unsigned char)(weight&0x00ff);
	}

	unsigned short crc_result = crc(&s_buff[2],8);
	s_buff[10] = (unsigned char)(crc_result>>8);
	s_buff[11] = (unsigned char)(crc_result&0x00ff);
	usart_send(USART_M,s_buff,12);
	*e_flag = event_none;	//切换事件到none
}

//
//	金属管理员门开门事件
//
unsigned char metal_openmanagedoor_flag = 0;
void metal_manage_opendoor(enum enum_event* e_flag,unsigned char* buff)
{
	if(metal_openmanagedoor_flag)	//非首次进入
	{
		if(timeout_status_get())
		{
			metal_openmanagedoor_flag = 0;
			usart_ack(usart_Buff_Send,metal_addr,0xb6,0xff,0xff);	//发送成功消息
			timeout_end();
			*e_flag = event_none;	//切换事件到none
		}
	}
	else	//首次进入
	{
		metal_openmanagedoor_flag = 1;
		usart_ack(usart_Buff_Send,metal_addr,0xb5,0x00,buff[REC_BUFF_INDEX_DAT1]);	//发送响应
		motor_ctrl(metal_lock,open);	//开管理员门
		timeout_start(1);	//开启超时
	}
}

//
//	金属管理员门关门事件
//
unsigned char metal_closemanagedoor_flag = 0;
void metal_manage_closedoor(enum enum_event* e_flag,unsigned char* buff)
{
	if(metal_closemanagedoor_flag)	//非首次进入
	{
		if(timeout_status_get())
		{
			metal_closemanagedoor_flag = 0;
			usart_ack(usart_Buff_Send,metal_addr,0xb8,0xff,0xff);	//发送成功消息
			timeout_end();
			*e_flag = event_none;	//切换事件到none
		}
	}
	else	//首次进入
	{
		metal_closemanagedoor_flag = 1;
		usart_ack(usart_Buff_Send,metal_addr,0xb7,0x00,buff[REC_BUFF_INDEX_DAT1]);	//发送响应
		motor_ctrl(metal_lock,close);	//关管理员门
		timeout_start(1);	//开启超时
	}
}

//////////////////////////////////////////////纸类部分功能////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////纸类部分功能////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////纸类部分功能////////////////////////////////////////////////////////////////////////////

//
//	纸类开门事件对应功能流程
//	e_flag : 当前事件
//	c_flag : 当前代码
//
unsigned char paper_open_door_flag = 0;
void paper_opendoor(enum enum_event* e_flag,unsigned char* buff)
{
	if(paper_open_door_flag)	//非首次进入
	{
		if(timeout_status_get())	//检查超时状态
		{
			//已超时
			paper_open_door_flag = 0;
			motor_ctrl(paper_motor,run_s);	//停止转动
			timeout_end();
			usart_ack(usart_Buff_Send,paper_addr,0xb2,0xff,0xff);	//发送失败消息
			*e_flag = event_metal_put;	//切换事件到put
		}
	}
	else	//首次进入
	{
		paper_open_door_flag = 1;
		usart_ack(usart_Buff_Send,paper_addr,0xb1,0x00,buff[REC_BUFF_INDEX_DAT1]);	//发送响应
		timeout_start(METAL_OPEN_DOOR_DELAY);	//开启超时
		motor_ctrl(paper_motor,run_z);	//开门--正转
	}
}

//
//	纸类放入事件对应功能流程
//
unsigned char paper_put_flag = 0;
void paper_put(enum enum_event* e_flag,unsigned char* buff)
{
	if(paper_put_flag)
	{
		if(device_status_get(paper_sensor) == on)	//检查光电1状态
		{
			paper_put_flag = 0;
			timeout_end();
			usart_ack(usart_Buff_Send,paper_addr,0xb9,0x00,0x00);	//发送刷新消息
			//*e_flag = event_bottle_scanfcode;	//切换事件到扫码
		}
		else if(timeout_status_get())	//检查超时状态
		{
			paper_put_flag = 0;
			timeout_end();
			*e_flag = event_paper_closedoor;	//切换事件到关门
		}
	}
	else
	{
		paper_put_flag = 1;
		timeout_start(BOTTLE_PUT_DELAY);	//开启超时
	}
}

//
//	纸类关门事件对应功能流程
//
unsigned char paper_closedoor_flag = 0;
void paper_closedoor(enum enum_event* e_flag,unsigned char* buff)
{
	if(paper_closedoor_flag)	//非首次进入
	{
		if(timeout_status_get())	//检查超时状态
		{
			paper_closedoor_flag = 0;
			motor_ctrl(paper_motor,run_s);	//停止转动
			timeout_end();
			usart_ack(usart_Buff_Send,paper_addr,0xb4,0xDD,0xDD);	//发送失败消息(正常回收情况下)
			*e_flag = event_none;	//切换事件到none
		}
	}
	else	//首次进入
	{
		paper_closedoor_flag = 1;
		usart_ack(usart_Buff_Send,paper_addr,0xb3,0x00,buff[REC_BUFF_INDEX_DAT1]);	//发送响应
		timeout_start(METAL_CLOSE_DOOR_DELAY);	//开启超时
		motor_ctrl(paper_motor,run_f);	//关门--反转
	}
}

//
//	纸类称重事件对应功能流程
//
void paper_weigh(enum enum_event* e_flag,unsigned char* buff)
{
	unsigned char s_buff[12] = {0x19,0x19,0x0A,0xA0,0xA1,0xC4,0x00,0x00,0x00,0x00,0x00,0x00};
	unsigned short weight = 0;
	usart_ack(usart_Buff_Send,paper_addr,0xC3,0x00,buff[REC_BUFF_INDEX_DAT1]);	//发送响应
	s_buff[3] = paper_addr;
	s_buff[7] = buff[REC_BUFF_INDEX_DAT1];

	unsigned char times_flag = 0;
	timeout_start(1);	//开启超时
	while(!timeout_status_get())	//等待超时
	{
		if(times_flag == 0)
		{
			times_flag++;
			if((weight = get_weight()) == 0)	//称重失败
			{
				s_buff[8] = 0xff;
				s_buff[9] = 0xff;
				unsigned short crc_result = crc(&s_buff[2],8);
				s_buff[10] = (unsigned char)(crc_result>>8);
				s_buff[11] = (unsigned char)(crc_result&0x00ff);
				usart_send(USART_M,s_buff,12);	//发送失败消息
				return;
			}

		}
	}
	timeout_end();

	if(buff[REC_BUFF_INDEX_DAT1])	//关门后的称重
	{
		weight = get_weight() - weight_base;
		weight *= 41;
		s_buff[8] = (unsigned char)weight>>8;
		s_buff[9] = (unsigned char)(weight&0x00ff);
	}
	else	//开门前的称重
	{
		weight_base = get_weight();	//获取开门前的基准重量
		s_buff[8] = 0x00;	//(unsigned char)weight>>8;
		s_buff[9] = 0x00;	//(unsigned char)(weight&0x00ff);
	}

	unsigned short crc_result = crc(&s_buff[2],8);
	s_buff[10] = (unsigned char)(crc_result>>8);
	s_buff[11] = (unsigned char)(crc_result&0x00ff);
	usart_send(USART_M,s_buff,12);
	*e_flag = event_none;	//切换事件到none
}

//
//	纸类管理员门开门事件
//
unsigned char paper_openmanagedoor_flag = 0;
void paper_manage_opendoor(enum enum_event* e_flag,unsigned char* buff)
{
	if(paper_openmanagedoor_flag)	//非首次进入
	{
		if(timeout_status_get())
		{
			paper_openmanagedoor_flag = 0;
			usart_ack(usart_Buff_Send,paper_addr,0xb6,0xff,0xff);	//发送成功消息
			timeout_end();
			*e_flag = event_none;	//切换事件到none
		}
	}
	else	//首次进入
	{
		paper_openmanagedoor_flag = 1;
		usart_ack(usart_Buff_Send,paper_addr,0xb5,0x00,buff[REC_BUFF_INDEX_DAT1]);	//发送响应
		motor_ctrl(paper_lock,open);	//开管理员门
		timeout_start(1);	//开启超时
	}
}

//
//	纸类管理员门关门事件
//
unsigned char paper_closemanagedoor_flag = 0;
void paper_manage_closedoor(enum enum_event* e_flag,unsigned char* buff)
{
	if(paper_closemanagedoor_flag)	//非首次进入
	{
		if(timeout_status_get())
		{
			paper_closemanagedoor_flag = 0;
			usart_ack(usart_Buff_Send,paper_addr,0xb8,0xff,0xff);	//发送成功消息
			timeout_end();
			*e_flag = event_none;	//切换事件到none
		}
	}
	else	//首次进入
	{
		paper_closemanagedoor_flag = 1;
		usart_ack(usart_Buff_Send,paper_addr,0xb7,0x00,buff[REC_BUFF_INDEX_DAT1]);	//发送响应
		motor_ctrl(paper_lock,close);	//关管理员门
		timeout_start(1);	//开启超时
	}
}


///////////////////////////以下为结构框架/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////以下为结构框架/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////以下为结构框架/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////以下为结构框架/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////以下为结构框架/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////以下为结构框架/////////////////////////////////////////////////////////////////////////////////////

//
//	事件选择函数		////////考虑事件切换时是否初始化设备状态,避免在一个事件未结束前 代码强行切换事件,导致上一个事件中启动的设备依旧运行 造成异常////////////////
//	e_flag : 事件
//	buff : 存储了数据包中的 目标地址、操作码、数据0、数据1 的缓冲区
//
unsigned char old_code_bottle = 0x00;	//用于记录上次触发事件的code,避免同一个code重复触发事件
void event_select_bottle(enum enum_event* e_flag,unsigned char* buff)
{
	if(buff[REC_BUFF_INDEX_CODE] != 0x00 && buff[REC_BUFF_INDEX_CODE] != old_code_bottle)	//code 变更
	{
		old_code_bottle = buff[REC_BUFF_INDEX_CODE];
		switch(buff[REC_BUFF_INDEX_CODE])
		{
			case 0xb1: clear_flag(buff); *e_flag = event_bottle_opendoor; break;	//开门事件
			case 0xb3: clear_flag(buff); *e_flag = event_bottle_closedoor; break;	//关门事件
			case 0xc1: clear_flag(buff); *e_flag = event_bottle_recycle; break;	//强制回收事件
			case 0xb5: clear_flag(buff); *e_flag = event_bottle_openmanagedoor; break;	//管理员开门事件
			case 0xb7: clear_flag(buff); *e_flag = event_bottle_closemanagedoor; break;	//管理员关门事件
		}
	}
}
unsigned char old_code_metal = 0x00;
void event_select_metal(enum enum_event* e_flag,unsigned char* buff)
{
	if(buff[REC_BUFF_INDEX_CODE] != 0x00 && buff[REC_BUFF_INDEX_CODE] != old_code_metal)	//code 变更
	{
		old_code_metal = buff[REC_BUFF_INDEX_CODE];
		switch(buff[REC_BUFF_INDEX_CODE])
		{
			case 0xb1: clear_flag(buff); *e_flag = event_metal_opendoor; break;	//开门事件
			case 0xb3: clear_flag(buff); *e_flag = event_metal_closedoor; break;	//关门事件
			case 0xc3: clear_flag(buff); *e_flag = event_metal_weigh; break;	//称重事件
			case 0xb5: clear_flag(buff); *e_flag = event_metal_openmanagedoor; break;	//管理员开门事件
			case 0xb7: clear_flag(buff); *e_flag = event_metal_closemanagedoor; break;	//管理员关门事件
		}
	}
}
unsigned char old_code_paper = 0x00;
void event_select_paper(enum enum_event* e_flag,unsigned char* buff)
{
	if(buff[REC_BUFF_INDEX_CODE] != 0x00 && buff[REC_BUFF_INDEX_CODE] != old_code_paper)	//code 变更
	{
		old_code_paper = buff[REC_BUFF_INDEX_CODE];
		switch(buff[REC_BUFF_INDEX_CODE])
		{
			case 0xb1: clear_flag(buff); *e_flag = event_paper_opendoor; break;	//开门事件
			case 0xb3: clear_flag(buff); *e_flag = event_paper_closedoor; break;	//关门事件
			case 0xc3: clear_flag(buff); *e_flag = event_paper_weigh; break;	//称重事件
			case 0xb5: clear_flag(buff); *e_flag = event_paper_openmanagedoor; break;	//管理员开门事件
			case 0xb7: clear_flag(buff); *e_flag = event_paper_closemanagedoor; break;	//管理员关门事件
		}
	}
}

//
//	事件执行函数
//	c_falg : 当前代码
//	e_flag : 当前事件
//
void event_exe(enum enum_event* e_flag,unsigned char* buff)
{
	switch(*e_flag)
	{
		//瓶子
		case event_bottle_opendoor: bottle_opendoor(e_flag,buff); break;
		case event_bottle_put: bottle_put(e_flag,buff); break;
		case event_bottle_scanfcode: bottle_scanfcode(e_flag,buff); break;
		case event_bottle_ack: bottle_ack(e_flag,buff); break;
		case event_bottle_recycle: bottle_recycle(e_flag,buff); break;
		case event_bottle_fail: bottle_fail(e_flag,buff); break;
		case event_bottle_closedoor: bottle_closedoor(e_flag,buff); break;
		case event_bottle_openmanagedoor: bottle_manage_opendoor(e_flag,buff); break;
		case event_bottle_closemanagedoor: bottle_manage_closedoor(e_flag,buff); break;
		//金属
		case event_metal_opendoor: metal_opendoor(e_flag,buff); break;
		case event_metal_put: metal_put(e_flag,buff); break;
		case event_metal_closedoor: metal_closedoor(e_flag,buff); break;
		case event_metal_weigh: metal_weigh(e_flag,buff); break;
		case event_metal_openmanagedoor: metal_manage_opendoor(e_flag,buff); break;
		case event_metal_closemanagedoor: metal_manage_closedoor(e_flag,buff); break;
		//纸类
		case event_paper_opendoor: paper_opendoor(e_flag,buff); break;
		case event_paper_put: paper_put(e_flag,buff); break;
		case event_paper_closedoor: paper_closedoor(e_flag,buff); break;
		case event_paper_weigh: paper_weigh(e_flag,buff); break;
		case event_paper_openmanagedoor: paper_manage_opendoor(e_flag,buff); break;
		case event_paper_closemanagedoor: paper_manage_closedoor(e_flag,buff); break;
		//
		case event_none: buff[REC_BUFF_INDEX_CODE] = 0x00; old_code_bottle = 0x00; 
						 old_code_metal = 0x00; old_code_paper = 0x00; break;
	}
}

enum enum_event run_event = event_none;	//程序当前运行的事件,所有部分共用该事件变量,如此则可以在事件选择部分做地址意外切换导致的事件强行变更问题
//
//
//
void function(unsigned char* buff)
{
	switch(buff[REC_BUFF_INDEX_ADDR])
	{
		#ifdef BOTTLE
			case 0xA2: event_select_bottle(&run_event,buff); event_exe(&run_event,buff); break;
		#endif
		#ifdef METAL_PAPER
			case 0xA3: event_select_metal(&run_event,buff); event_exe(&run_event,buff); break;
			case 0xA4: event_select_paper(&run_event,buff); event_exe(&run_event,buff); break;
		#endif
	}
}

//
//	清除事件相关变量
//
void clear_flag(unsigned char* buff)
{
	//buff[REC_BUFF_INDEX_ADDR] = 0x00; buff[REC_BUFF_INDEX_CODE] = 0x00;
	//buff[REC_BUFF_INDEX_DAT0] = 0x00; buff[REC_BUFF_INDEX_DAT1] = 0x00;
	bottle_open_door_flag = 0;
	bottle_put_flag = 0;
	bottle_scanfcode_flag = 0;
	bottle_ack_flag = 0;
	bottle_recycle_flag = 0;
	bottle_fail_flag = 0;
	bottle_closedoor_flag = 0;

	metal_open_door_flag = 0;
	metal_put_flag = 0;
	metal_closedoor_flag = 0;

	paper_open_door_flag = 0;
	paper_put_flag = 0;
	paper_closedoor_flag = 0;
}

//
//	查询操作码,若无规定的操作码则返回0x00
//	code : 要查询的操作码
//	return : 返回已规定的操作码或返回0x00
//
unsigned char optin_code_get(unsigned char code)
{
	switch(code)
	{
		case 0xB1: return 0xB1;
		case 0xB2: return 0xB2;
		case 0xB3: return 0xB3;
		case 0xB4: return 0xB4;
		case 0xB5: return 0xB5;
		case 0xB6: return 0xB6;
		case 0xB7: return 0xB7;
		case 0xB8: return 0xB8;
		case 0xB9: return 0xB9;
		case 0xBA: return 0xBA;
		case 0xBB: return 0xBB;
		case 0xBC: return 0xBC;
		case 0xBD: return 0xBD;
		case 0xBE: return 0xBE;
		case 0xBF: return 0xBF;
		case 0xC1: return 0xC1;
		case 0xC3: return 0xC3;
		default: return 0x00;
	}
}

//
//	往串口发送消息
//	buff : 发送缓冲区
//	a_flag : 目标地址(值安卓发送至STM32的数据包中的目标地址,即本模块的地址)
//	c_flag : 操作码
//
void usart_ack(unsigned char* buff,unsigned char a_flag,unsigned char c_flag,unsigned char dat1,unsigned char dat2)
{
	buff[0] = 0x19;
	buff[1] = 0x19;
	buff[2] = 0x08;
	buff[3] = a_flag;
	buff[4] = 0xA1;
	buff[5] = c_flag;
	buff[6] = dat1;
	buff[7] = dat2;
	buff[8] = 0x00;
	buff[9] = 0x00;
	unsigned short crc_result = crc(&buff[2],6);
	buff[8] = crc_result>>8;
	buff[9] = (unsigned char)(crc_result&0x00ff);
	usart_send(USART_M,buff,10);
}

////////////////////////////以下为基础功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为基础功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为基础功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为基础功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为基础功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为基础功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////

//
//	初始化函数
//
void function_init(void)
{
	driver_init();

	
	
	/*unsigned char num[11] = {'0','.','0','0','0',' ','V','\r','\n','\0'};
	num[0] = sum/1000 + '0';
	num[2] = (sum/100)%10 + '0';
	num[3] = (sum/10)%10 + '0';
	num[4] = (sum/1)%10 + '0';
	usart_send_str(USART_M,"now voltage: ");
	usart_send_str(USART_M,num);*/

	/*unsigned int weight = 0;
	unsigned long weight_base = 0;
	get_weight();
	get_weight();
	weight_base = get_weight();

	while(1)
	{
		//get_weight();
		weight = get_weight() - weight_base;
		weight *= 31.6667;
		
		unsigned char num[8] = {'0','0','0',' ','g','\r','\n','\0'};
		num[0] = (weight/100)%10 + '0';
		num[1] = (weight/10)%10 + '0';
		num[2] = (weight)%10 + '0';
		usart_send_str(USART_M,"Weight: ");
		usart_send_str(USART_M,num);
		
	}*/
}

//
//	计算CRC
//	buff: 需要计算的数据缓冲区,从缓冲区的第一个元素开始到第 len 元素停止
//	len: 数据长度
//	return: 返回 CRC-CCITT (XModem) 类型的CRC校验码
//
unsigned short crc(unsigned char* buff,unsigned char len)
{
	unsigned short crcin = 0x0000;
	unsigned short crc = 0x1021;
	while(len--)
	{
		crcin = ((crcin&0xff00)^((*buff++)<<8))|(crcin&0x00ff);
		unsigned char bi = 8;
		while(bi--)
		{
			if((crcin & 0x8000) > 0){crcin <<= 1; crcin ^= crc;}
			else crcin <<= 1;
		}
	}
	return crcin;
}
