#ifndef DRV_MOTOR_H
#define DRV_MOTOR_H

/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx_hal.h"
#include "../Drive/drv_can.h"
#include "alg_math.h"

/* Exported macros -----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/**
 * @brief 电机状态
 *
 */
typedef  enum Enum_CAN_Motor_Status
{
    CAN_Motor_Status_DISABLE = 0,
    CAN_Motor_Status_ENABLE,
} Enum_CAN_Motor_Status;

/**
 * @brief CAN电机的ID枚举类型
 *
 */
typedef enum Enum_CAN_Motor_ID
{
    CAN_Motor_ID_UNDEFINED = 0,
    CAN_Motor_ID_0x201,
    CAN_Motor_ID_0x202,
    CAN_Motor_ID_0x203,
    CAN_Motor_ID_0x204,
    CAN_Motor_ID_0x205,
    CAN_Motor_ID_0x206,
    CAN_Motor_ID_0x207,
    CAN_Motor_ID_0x208,
    CAN_Motor_ID_0x209,
    CAN_Motor_ID_0x20A,
    CAN_Motor_ID_0x20B,
} Enum_CAN_Motor_ID;

/**
 * @brief CAN电机的ID分配情况
 *
 */
typedef enum Enum_CAN_Motor_ID_Status
{
    CAN_Motor_ID_Status_FREE = 0,
    CAN_Motor_ID_Status_ALLOCATED,
} Enum_CAN_Motor_ID_Status;

/**
 * @brief 电机控制方式
 *
 */
typedef enum Enum_Control_Method
{
    Control_Method_OPENLOOP = 0,
    Control_Method_TORQUE,
    Control_Method_OMEGA,
    Control_Method_ANGLE,
} Enum_Control_Method;
/**
 * @brief 3508电机结构体
 *
 */

typedef struct Struct_Motor_C620_Object{

    void (*CAN_RxCpltCallback)(struct Struct_Motor_C620_Object *motor, const uint8_t *Rx_Data);
    void (*Output)(struct Struct_Motor_C620_Object *motor);
    /*常量*/
    // 绑定的CAN
    Struct_CAN_Manage_Object *CAN_Manage_Object;
    // 收数据绑定的CAN ID, C6系列0x201~0x208, GM系列0x205~0x20b
    Enum_CAN_Motor_ID CAN_ID;
    // 发送缓存区
    uint8_t *CAN_Tx_Data;

    float Gearbox_Rate;// 减速比, 默认带减速箱
    float Torque_Max;// 最大扭矩, 需根据不同负载测量后赋值, 也就开环和扭矩环输出用得到, 不过我感觉应该没有奇葩喜欢开环输出这玩意

    uint16_t Encoder_Num_Per_Round;// 一圈编码器刻度
    // 最大输出扭矩
    uint16_t Output_Max;

    // 当前时刻的电机接收flag
    uint32_t Flag;
    // 前一时刻的电机接收flag
    uint32_t Pre_Flag;
    /*接收缓存*/
    uint16_t Rx_Encoder;// 接收的编码器位置, 0~8191
    int16_t Rx_Omega;// 接收的速度, rpm
    int16_t Rx_Torque;// 接收的扭矩, 目标的扭矩, -30000~30000
    uint16_t Rx_Temperature;// 接收的温度, 摄氏度

    /*数据缓存*/
    uint16_t Pre_Encoder;// 之前的编码器位置

    /*当前状态*/
    int32_t Total_Encoder;// 总编码器位置
    int32_t Total_Round;// 总圈数
    // 电机状态
    Enum_CAN_Motor_Status CAN_Motor_Status;

    float Now_Angle;// 当前的角度, rad
    float Now_Omega;// 当前的速度, rad/s
    float Now_Torque;// 当前的扭矩, 直接采用反馈值
    uint8_t Now_Temperature;// 当前的温度, 摄氏度

    // 电机控制方式
    Enum_Control_Method Control_Method;
    // 目标的角度, rad
    float Target_Angle;
    // 目标的速度, rad/s
    float Target_Omega;
    // 目标的扭矩, 直接采用反馈值
    float Target_Torque;
    // 输出量
    float Out;
    // CAN通信接收回调函数指针


}Struct_Motor_C620_Object;

/* 接口函数声明 */
void Motor_C620_Output(Struct_Motor_C620_Object *motor);
void Motor_C620_CAN_RxCpltCallback(Struct_Motor_C620_Object *motor, const uint8_t *Rx_Data);
void Motor_C620_Init(Struct_Motor_C620_Object *motor);
// 电机结构体定义

#endif