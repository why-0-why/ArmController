#include "dvc_motor.h"

// 初始化电机结构体
void Motor_C620_Init(Struct_Motor_C620_Object *motor)
{
    // 设置默认值
    motor->Gearbox_Rate = 3591.0f / 187.0f;
    motor->Torque_Max = 16384.0f;
    motor->Output_Max = 10000;
    motor->Flag = 0;
    motor->Pre_Flag = 0;
    motor->Encoder_Num_Per_Round = 8192;
    motor->Rx_Encoder = 0;
    motor->Rx_Omega = 0;
    motor->Rx_Torque = 0;
    motor->Rx_Temperature = 0;
    motor->Pre_Encoder = 0;
    motor->Total_Encoder = 0;
    motor->Total_Round = 0;
    motor->CAN_Motor_Status = CAN_Motor_Status_DISABLE;
    motor->Now_Angle = 0.0f;
    motor->Now_Omega = 0.0f;
    motor->Now_Torque = 0.0f;
    motor->Now_Temperature = 0;
    motor->Control_Method = Control_Method_ANGLE;
    motor->Target_Angle = 0.0f;
    motor->Target_Omega = 0.0f;
    motor->Target_Torque = 0.0f;
    motor->Out=0.0f;

    motor->Output = Motor_C620_Output;
    // 设置回调函数指针
    motor->CAN_RxCpltCallback = Motor_C620_CAN_RxCpltCallback;
}
void Motor_C620_Output(Struct_Motor_C620_Object *motor)
{
    motor->CAN_Tx_Data[0] = (int16_t)motor->Out >> 8;
    motor->CAN_Tx_Data[1] = (int16_t)motor->Out;
}
// CAN通信接收回调函数实现
void Motor_C620_CAN_RxCpltCallback(Struct_Motor_C620_Object *motor, const uint8_t *Rx_Data)
{
    motor->Pre_Encoder = motor->Rx_Encoder;

    // 使用无符号中间变量避免窄化转换警告
    const uint16_t raw_encoder = (Rx_Data[0] << 8) | Rx_Data[1];
    const uint16_t raw_omega = (Rx_Data[2] << 8) | Rx_Data[3];
    const uint16_t raw_torque = (Rx_Data[4] << 8) | Rx_Data[5];

    motor->Rx_Encoder = (int16_t)raw_encoder;
    motor->Rx_Omega = (int16_t)raw_omega;
    motor->Rx_Torque = (int16_t)raw_torque;
    motor->Rx_Temperature = Rx_Data[6];

    const int16_t delta_encoder = (int16_t)(motor->Rx_Encoder - motor->Pre_Encoder);
    if (delta_encoder < -4096)
    {
        // 正方向转过了一圈
        motor->Total_Round++;
    }
    else if (delta_encoder > 4096)
    {
        // 反方向转过了一圈
        motor->Total_Round--;
    }
    motor->Total_Encoder = motor->Total_Round * motor->Encoder_Num_Per_Round + motor->Rx_Encoder;

    motor->Now_Angle = (float)motor->Total_Encoder /
                      (float)motor->Encoder_Num_Per_Round *
                      2.0f * PI / motor->Gearbox_Rate;

    motor->Now_Omega = (float)motor->Rx_Omega * RPM_TO_RADPS / motor->Gearbox_Rate;
    motor->Now_Torque = (float)motor->Rx_Torque;
    motor->Now_Temperature = (uint8_t)motor->Rx_Temperature;
}

