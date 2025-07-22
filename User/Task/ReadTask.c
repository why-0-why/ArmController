#include "ReadTask.h"
Struct_Motor_C620_Object Joint1;
Struct_Motor_C620_Object Joint2;
Struct_Motor_C620_Object Joint3;

char* variable_list[] = {"setpoint"};

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
            Joint1.CAN_RxCpltCallback(&Joint1, Rx_Buffer->Data);
        }
        break;
    case (0x202):
        {
            Joint2.CAN_RxCpltCallback(&Joint2, Rx_Buffer->Data);
        }
        break;
    case (0x203):
        {
            Joint3.CAN_RxCpltCallback(&Joint3, Rx_Buffer->Data);
        }
        break;
    default:
        break;
    }
}

void StartReadTask(void const* argument)
{
    CAN_Init(&hcan1, CAN_Motor_Call_Back);
    Motor_C620_Init(&Joint1);
    Motor_C620_Init(&Joint2);
    Motor_C620_Init(&Joint3);

    for (;;)
    {
        if (HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin) == GPIO_PIN_RESET)
        {
            HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_SET);
        }
    }
}


