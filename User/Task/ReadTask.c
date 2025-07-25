#include "ReadTask.h"

#include "dvc_motor.h"

Class_Motor_C610* Joint3;
float Angle3;

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
        }
        break;
    case (0x202):
        {
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
    Joint3=Motor_C610_Creat();
    Motor_C610_Init(Joint3,&hcan1,CAN_Motor_ID_0x203,Control_Method_TORQUE,36.0f,10000.0f);
    PID_Set_K_D(Motor_C610_Get_PID_Angle(Joint3),10.0);
    for (;;)
    {
        Angle3=Motor_C610_Get_Now_Angle(Joint3);
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


