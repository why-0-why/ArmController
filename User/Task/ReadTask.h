#ifndef ReadTask
#define ReadTask

#include "main.h"
#include "usart.h"
#include "cmsis_os.h"

//user头文件
#include "drv_can.h"
#include "dvc_motor.h"
#include "alg_math.h"
#include "dvc_serialplot.h"

extern Class_Serialplot* serialplot;
extern Struct_Motor_C620_Object Joint3;

#endif