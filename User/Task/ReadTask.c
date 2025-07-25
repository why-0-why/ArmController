#include "ReadTask.h"

#include "dvc_motor.h"

Class_Motor_C610* Joint1;
Class_Motor_C610* Joint2;
Class_Motor_C610* Joint3;

float Angle3;

/**
 * @brief CAN报文回调函数
 *
 * @param Rx_Buffer CAN接收的信息结构体
 */
void CAN_Motor_Call_Back(Struct_CAN_Rx_Buffer* Rx_Buffer)
{
    switch (Rx_Buffer->Header.StdId)
    {
    case (0x201):
        {
            Motor_C610_CAN_RxCpltCallback(Joint1, Rx_Buffer->Data);
        }
        break;
    case (0x202):
        {
            Motor_C610_CAN_RxCpltCallback(Joint2, Rx_Buffer->Data);
        }
        break;
    case (0x203):
        {
            Motor_C610_CAN_RxCpltCallback(Joint3, Rx_Buffer->Data);
        }
        break;
    default:
        break;
    }
}

void StartReadTask(void const* argument)
{
    CAN_Init(&hcan1, CAN_Motor_Call_Back);
    //类创建与初始化
    Joint1=Motor_C610_Creat();
    Joint2=Motor_C610_Creat();
    Joint3=Motor_C610_Creat();
    Motor_C610_Init(Joint1,&hcan1,CAN_Motor_ID_0x201,Control_Method_TORQUE,36.0f,10000.0f);
    Motor_C610_Init(Joint2,&hcan1,CAN_Motor_ID_0x202,Control_Method_TORQUE,36.0f,10000.0f);
    Motor_C610_Init(Joint3,&hcan1,CAN_Motor_ID_0x203,Control_Method_TORQUE,36.0f,10000.0f);
    //test类内类调用
    PID_Set_K_D(Motor_C610_Get_PID_Angle(Joint3),10.0);
    for (;;)
    {
        Angle3=Motor_C610_Get_Now_Angle(Joint3);
        if (HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin) == GPIO_PIN_RESET)
        {
            HAL_GPIO_WritePin(GasValve_GPIO_Port,GasValve_Pin,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(GasValve_GPIO_Port, GasValve_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_SET);
        }
    }
}


