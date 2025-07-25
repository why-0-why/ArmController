/**
 * @file dvc_motor_capi.cpp
 * @author why
 * @brief motor对象的C语言接口
 * @date 2025-07-25
 *
 */
#include "dvc_motor.h"

/* 创建/销毁/初始化对象 */
Class_Motor_C610* Motor_C610_Creat(void)
{
    return new Class_Motor_C610();
}

void Motor_C610_Init(
    Class_Motor_C610* motor,
    CAN_HandleTypeDef* hcan,
    Enum_CAN_Motor_ID motor_id,
    Enum_Control_Method control_method,
    float gearbox_rate,
    float torque_max
)
{
    if (motor)
    {
        motor->Init(
            hcan,
            motor_id,
            control_method,
            gearbox_rate,
            torque_max);
    }
}


void Motor_C610_Destroy(Class_Motor_C610* motor)
{
    delete motor;
}

/* 类内类指针获取 */
Class_PID* Motor_C610_Get_PID_Angle(Class_Motor_C610* motor)
{
    if (motor)
    {
        return &(motor->PID_Angle);
    }
}

Class_PID* Motor_C610_Get_PID_Omega(Class_Motor_C610* motor)
{
    if (motor)
    {
        return &(motor->PID_Omega);
    }
}

/* 类函数 */
uint16_t Motor_C610_Get_Output_Max(Class_Motor_C610* motor)
{
    if (motor)
    {
        return motor->Get_Output_Max();
    }
}

enum Enum_CAN_Motor_Status Motor_C610_Get_CAN_Motor_Status(Class_Motor_C610* motor)
{
    if (motor)
    {
        return motor->Get_CAN_Motor_Status();
    }
}

float Motor_C610_Get_Now_Angle(Class_Motor_C610* motor)
{
    if (motor)
    {
        return motor->Get_Now_Angle();
    }
}

float Motor_C610_Get_Now_Omega(Class_Motor_C610* motor)
{
    if (motor)
    {
        return motor->Get_Now_Omega();
    }
}

float Motor_C610_Get_Now_Torque(Class_Motor_C610* motor)
{
    if (motor)
    {
        return motor->Get_Now_Torque();
    }
}

uint8_t Motor_C610_Get_Now_Temperature(Class_Motor_C610* motor)
{
    if (motor)
    {
        return motor->Get_Now_Temperature();
    }
}

enum Enum_Control_Method Motor_C610_Get_Control_Method(Class_Motor_C610* motor)
{
    if (motor)
    {
        return motor->Get_Control_Method();
    }
}

float Motor_C610_Get_Target_Angle(Class_Motor_C610* motor)
{
    if (motor)
    {
        return motor->Get_Target_Angle();
    }
}

float Motor_C610_Get_Target_Omega(Class_Motor_C610* motor)
{
    if (motor)
    {
        return motor->Get_Target_Omega();
    }
}

float Motor_C610_Get_Target_Torque(Class_Motor_C610* motor)
{
    if (motor)
    {
        return motor->Get_Target_Torque();
    }
}

float Motor_C610_Get_Out(Class_Motor_C610* motor)
{
    if (motor)
    {
        return motor->Get_Out();
    }
}

void Motor_C610_Set_Control_Method(Class_Motor_C610* motor, enum Enum_Control_Method control_method)
{
    if (motor)
    {
        motor->Set_Control_Method(control_method);
    }
}

void Motor_C610_Set_Target_Angle(Class_Motor_C610* motor, float target_angle)
{
    if (motor)
    {
        motor->Set_Target_Angle(target_angle);
    }
}

void Motor_C610_Set_Target_Omega(Class_Motor_C610* motor, float target_omega)
{
    if (motor)
    {
        motor->Set_Target_Omega(target_omega);
    }
}

void Motor_C610_Set_Target_Torque(Class_Motor_C610* motor, float target_torque)
{
    if (motor)
    {
        motor->Set_Target_Torque(target_torque);
    }
}

void Motor_C610_Set_Out(Class_Motor_C610* motor, float out)
{
    if (motor)
    {
        motor->Set_Out(out);
    }
}

void Motor_C610_CAN_RxCpltCallback(Class_Motor_C610* motor, uint8_t* rx_data)
{
    if (motor)
    {
        motor->CAN_RxCpltCallback(rx_data);
    }
}

void Motor_C610_TIM_Alive_PeriodElapsedCallback(Class_Motor_C610* motor)
{
    if (motor)
    {
        motor->TIM_Alive_PeriodElapsedCallback();
    }
}

void Motor_C610_TIM_PID_PeriodElapsedCallback(Class_Motor_C610* motor)
{
    if (motor)
    {
        motor->TIM_PID_PeriodElapsedCallback();
    }
}
