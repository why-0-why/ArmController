#include "ReadTask.h"

Class_Motor_C620 Joint1;
Class_Motor_C620 Joint2;
Class_Motor_C610 Joint3;

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
            Joint1.CAN_RxCpltCallback(Rx_Buffer->Data);
        }
        break;
    case (0x202):
        {
            Joint2.CAN_RxCpltCallback(Rx_Buffer->Data);
        }
        break;
    case (0x203):
        {
            Joint3.CAN_RxCpltCallback(Rx_Buffer->Data);
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
    Joint1.Init(&hcan1,CAN_Motor_ID_0x201,Control_Method_ANGLE);
    Joint2.Init(&hcan1,CAN_Motor_ID_0x202,Control_Method_ANGLE);
    Joint3.Init(&hcan1,CAN_Motor_ID_0x203,Control_Method_ANGLE);
    for (;;)
    {
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


