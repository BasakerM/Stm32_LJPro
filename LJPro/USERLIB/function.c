#include "function.h"


unsigned char usart_Buff_Send[16] = {0x00};	//串口发送缓冲区

//
//	瓶子部分用户的门操作
//
unsigned char door_bottle_user_flag = 1;	//用于判断是否为首次进入的标志
unsigned char scanf_code_flag = 0;
void bottle_door_user(unsigned char* a_flag,unsigned char* c_flag,enum door_status oc)
{
	switch(door_ctrl_user(door_bottle_user,oc,5))
	{
		case exeing: if(door_bottle_user_flag)
						{
							usart_ack(usart_Buff_Send,*a_flag,*c_flag);
							door_bottle_user_flag = 0;
						} break;
		case success: *c_flag = 0xaa; usart_ack(usart_Buff_Send,*a_flag,*c_flag); door_bottle_user_flag = 1;  scanf_code_flag = 1;
							//*a_flag = 0x00; *c_flag = 0x00; 
						break;
		case fail: *c_flag = 0xab; usart_ack(usart_Buff_Send,*a_flag,*c_flag); door_bottle_user_flag = 1; 
							*a_flag = 0x00; *c_flag = 0x00;
						break;
	}
	if(scanf_code_flag == 1)
		if(door_status_get(scanf_code_start) == open)
			scanf_code_flag = 2；
switch(door_ctrl_user(scanf_code_end,open,5))
			{
				case success: break;
				case fail: *a_flag = 0x00; *c_flag = 0x00; break;
			}
	//*a_flag = 0x00; *c_flag = 0x00;
}

//
//	瓶子部分管理员的门操作
//
void bottle_door_manage(unsigned char* a_flag,unsigned char* c_flag,enum door_status oc)
{
	usart_ack(usart_Buff_Send,*a_flag,*c_flag);	//发送应答
	*a_flag = 0x00; *c_flag = 0x00;
}

//
//	金属部分用户的门操作
//
void metal_door_user(unsigned char* a_flag,unsigned char* c_flag,enum door_status oc)
{
	usart_ack(usart_Buff_Send,*a_flag,*c_flag);	//发送应答
	*a_flag = 0x00; *c_flag = 0x00;
}

//
//	金属部分管理员的门操作
//
void metal_door_manage(unsigned char* a_flag,unsigned char* c_flag,enum door_status oc)
{
	usart_ack(usart_Buff_Send,*a_flag,*c_flag);	//发送应答
	*a_flag = 0x00; *c_flag = 0x00;
}

//
//	金属部分称重
//
void metal_weight(unsigned char* a_flag,unsigned char* c_flag)
{
	usart_ack(usart_Buff_Send,*a_flag,*c_flag);	//发送应答
	*a_flag = 0x00; *c_flag = 0x00;
}

//
//	纸类部分用户的门操作
//
void paper_door_user(unsigned char* a_flag,unsigned char* c_flag,enum door_status oc)
{
	usart_ack(usart_Buff_Send,*a_flag,*c_flag);	//发送应答
	*a_flag = 0x00; *c_flag = 0x00;
}

//
//	纸类部分管理员的门操作
//
void paper_door_manage(unsigned char* a_flag,unsigned char* c_flag,enum door_status oc)
{
	usart_ack(usart_Buff_Send,*a_flag,*c_flag);	//发送应答
	*a_flag = 0x00; *c_flag = 0x00;
}

//
//	纸类部分称重
//
void paper_weight(unsigned char* a_flag,unsigned char* c_flag)
{
	usart_ack(usart_Buff_Send,*a_flag,*c_flag);	//发送应答
	*a_flag = 0x00; *c_flag = 0x00;
}

///////////////////////////以下定义了各个部分的功能/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////以下定义了各个部分的功能/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////以下定义了各个部分的功能/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////以下定义了各个部分的功能/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////以下定义了各个部分的功能/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////以下定义了各个部分的功能/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////以下定义了各个部分的功能/////////////////////////////////////////////////////////////////////////////////////

//
//	瓶子部分的功能
//
unsigned char c_flag_old = 0x00;
void bottle_function(unsigned char* a_flag,unsigned char* c_flag)
{
	if(c_flag_old)
	event_select(*c_flag);
	/*switch(*c_flag)
	{
		case 0xB1: bottle_door_user(a_flag,c_flag,open); break;	//用户开门操作码
		case 0xB2: bottle_door_user(a_flag,c_flag,close); break;	//用户关门操作码
		case 0xB3: bottle_door_manage(a_flag,c_flag,open); break;	//管理员开门操作码
		case 0xB4: bottle_door_manage(a_flag,c_flag,close); break;	//管理员关门操作码
	}*/
}

//
//	金属部分的功能
//

void metal_function(unsigned char* a_flag,unsigned char* c_flag)
{
	switch(*c_flag)
	{
		case 0xB1: metal_door_user(a_flag,c_flag,open); break;	//用户开门操作码
		case 0xB2: metal_door_user(a_flag,c_flag,close); break;	//用户关门操作码
		case 0xB3: metal_door_manage(a_flag,c_flag,open); break;	//管理员开门操作码
		case 0xB4: metal_door_manage(a_flag,c_flag,close); break;	//管理员关门操作码
		case 0xD1: metal_weight(a_flag,c_flag); break;	//称重
	}
}

//
//	纸类部分的功能
//

void paper_function(unsigned char* a_flag,unsigned char* c_flag)
{
	switch(*c_flag)
	{
		case 0xB1: paper_door_user(a_flag,c_flag,open); break;	//用户开门操作码
		case 0xB2: paper_door_user(a_flag,c_flag,close); break;	//用户关门操作码
		case 0xB3: paper_door_manage(a_flag,c_flag,open); break;	//管理员开门操作码
		case 0xB4: paper_door_manage(a_flag,c_flag,close); break;	//管理员关门操作码
		case 0xD1: paper_weight(a_flag,c_flag); break;	//称重
	}
}

////////////////////////////以下为具体功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为具体功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为具体功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为具体功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为具体功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为具体功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为具体功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为具体功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为具体功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为具体功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为具体功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为具体功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为具体功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为具体功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为具体功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为具体功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为具体功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为具体功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为具体功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为具体功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为具体功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为具体功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为具体功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为具体功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为具体功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为具体功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为具体功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为具体功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为具体功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为具体功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////以下为具体功能实现,无需关注/////////////////////////////////////////////////////////////////////////////////////

//
//	事件函数
//
void event(enum enum_event e)
{
	switch(e)
	{
		case bottle_open_door: break;
	}
}



//
//	用户门控制
//	door : 选择门(door_metal_user,,door_paper_user,,door_bottle_user)
//	oc : 对门的操作,开门 : open,关门 : close
//	sec ： 操作时间，例如 5, 则最多操作 5s ,超过 5s 则视为操作失败
//	return : 操作中 : exeing , 成功 : success , 失败 : fail
//
unsigned door_ctrl_user_flag = 1;	//用于判断是否为首次进入的标志
enum exe_status door_ctrl_user(enum door_device door,enum door_status oc,float sec)
{
	enum motor_device md = door_to_motor(door);
	if(door_ctrl_user_flag)
	{
		door_ctrl_user_flag = 0;
		timeout_start(sec);	//开启超时
		if(oc == open) motor_ctrl(md,run_z);	//开门--正转
		else if(oc == close) motor_ctrl(md,run_f);	//关门--反转
	}
	else
	{
		if(door_status_get(door) == oc)	//获取门状态
		{	//已开门
			door_ctrl_user_flag = 1;
			motor_ctrl(md,run_s);	//停止转动
			timeout_end();	//关闭超时
			return success;
		}
		else if(timeout_status_get())	//获取超时状态
		{
			//已超时
			door_ctrl_user_flag = 1;
			motor_ctrl(md,run_s);
			timeout_end();
			return fail;
		}
	}
	return exeing;
}

//
//	管理员门控制(管理员门在对门操作的时候只有 open,没有 close)
//	door : 选择门(door_metal_manage,,door_paper_manage,,door_bottle_manage)
//	oc : 对门的操作,开门 : open,关门 : close
//	sec ： 操作时间，例如 5, 则最多操作 5s ,超过 5s 则视为操作失败
//	return : 操作中 : exeing , 成功 : success , 失败 : fail
//
unsigned door_ctrl_manage_flag = 1;	//用于判断是否为首次进入的标志
enum exe_status door_ctrl_manage(enum door_device door,enum door_status oc,float sec)
{
	enum motor_device md = door_to_motor(door);
	if(door_ctrl_manage_flag)
	{
		door_ctrl_manage_flag = 0;
		timeout_start(sec);	//开启超时
		if(oc == open) motor_ctrl(md,run_z);	//开始控制电控锁
	}
	else
	{
		if(door_status_get(door) == oc)	//获取门状态
		{	//已开门
			door_ctrl_manage_flag = 1;
			motor_ctrl(md,run_s);	//停止控制电控锁
			timeout_end();	//关闭超时
			return success;
		}
		else if(timeout_status_get())	//获取超时状态
		{
			//已超时
			door_ctrl_manage_flag = 1;
			motor_ctrl(md,run_s);
			timeout_end();
			return fail;
		}
	}
	return exeing;
}

//
//	往串口发送应答(该函数也用于发送数据包内容皆位0的指令,例如光电信号的反馈)
//	buff : 发送缓冲区
//	a_flag : 目标地址(值安卓发送至STM32的数据包中的目标地址,即本模块的地址)
//	c_flag : 操作码
//
void usart_ack(unsigned char* buff,unsigned char a_flag,unsigned char c_flag)
{
	usart_buff_init(buff,a_flag,c_flag);	//初始化发送缓冲区
	unsigned short crc_result = crc(&buff[2],6);
	buff[8] = crc_result>>8;
	buff[9] = (unsigned char)(crc_result&0x00ff);
	usart_send(USART_M,buff,10);
}

//
//	往串口发送指令(该函数用于发送数据包包含执行状态的指令，例如开门的执行结果反馈)
//	前三个参数表同上
//	stat : 执行状态(success , fail)(这是一个枚举，定义于 drive.h 中)
//
void usart_cmd(unsigned char* buff,unsigned char a_flag,unsigned char c_flag,enum exe_status stat)
{
	usart_buff_init(buff,a_flag,c_flag);	//初始化发送缓冲区
	unsigned short crc_result = crc(&buff[2],6);
	buff[8] = crc_result>>8;
	buff[9] = (unsigned char)(crc_result&0x00ff);
	usart_send(USART_M,buff,10);
}

//
//	串口数据缓冲区初始化
//	参数表同上
//
void usart_buff_init(unsigned char* buff,unsigned char a_flag,unsigned char c_flag)
{
	buff[0] = 0x19;
	buff[1] = 0x19;
	buff[2] = 0x08;
	buff[3] = a_flag;
	buff[4] = 0xA1;
	buff[5] = c_flag;
	buff[6] = 0x00;
	buff[7] = 0x00;
	buff[8] = 0x00;
	buff[9] = 0x00;
}

void function_init(void)
{
	usart_init();
	driver_init();
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
