#ifndef softwarelayer_h
#define softwarelayer_h

#include "hardwarelayer.h"

typedef enum
{
	false,true
}bool;

typedef struct struct_Device
{
	enum_hardware_status open;
	enum_hardware_status close;
}Device;
static Device device = 
{
	enum_hs_open,enum_hs_close
};

//////////////declaration function/////////////////////
void Bottle_Door(Device de);

//////////////struct bottle/////////////////////
//////////////struct bottle/////////////////////
typedef struct struct_Bottle
{
	enum_hardware_type door_motor;
	enum_hardware_type recycle_motor;
	enum_hardware_type opendoor_sensor;
	enum_hardware_type closedoor_sensor;
	enum_hardware_type safehand0_sensor;
	enum_hardware_type safehand1_sensor;
	enum_hardware_type put_sensor;
	enum_hardware_type ack_sensor;
	enum_hardware_type recycle_sensor;

	void (*opendoor)(enum_hardware_status);
	bool (*isopen)(void);
	bool (*isclose)(void);
	void (*put)(void);
	bool (*isput)(void);
	void (*scanfcode)(void);
	bool (*isscanfcode)(void);
	void (*ack)(void);
	void (*recycle)(void);
	void (*fail)(void);
}Bottle;
static Bottle bottle = 
{
	enum_ht_motor_0,enum_ht_motor_1,enum_ht_signal_sensor_0,enum_ht_signal_sensor_1,enum_ht_signal_sensor_2,
	enum_ht_signal_sensor_3,enum_ht_signal_sensor_4,enum_ht_signal_sensor_5,enum_ht_signal_sensor_6,
	Bottle_Door
};

//////////////struct metal/////////////////////
//////////////struct metal/////////////////////
typedef struct struct_Metal
{
	void (*opendoor)(void);
	void (*closedoor)(void);
}Metal;
static Metal metal;

//////////////struct paper/////////////////////
//////////////struct paper/////////////////////
typedef struct struct_Paper
{
	void (*opendoor)(void);
	void (*closedoor)(void);
}Paper;
static Paper paper;

//////////////struct new/////////////////////
//////////////struct new/////////////////////
typedef struct struct_New
{
	Bottle (*bottle_init)(void);
	Bottle (*metal_init)(void);
	Bottle (*paper_init)(void);
}New;
static New new;



#endif
