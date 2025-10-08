#include "ReadTask.h"

extern "C"{
#include "main.h"
#include "cmsis_os.h"
#include "usart.h"
#include "drv_can.h"
#include "drv_uart.h"
#include "drv_RefereeSystem.h"
}// C实现函数
#include "dvc_motor.h"
#include "pro_UserController.h"

uint8_t* float_To_uint8_t(float fnum);

/*
 * @brief 电机轴对象
 */
Class_Motor_C620 Joint1;
Class_Motor_C620 Joint2;
Class_Motor_C620 Joint3;
Class_Motor_C620 Joint4;

/*
 * @brief 自定义控制器信息包
 */
user_package_t Package;

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
void UART_RefereeSystem_Call_Back(uint8_t* Buffer, uint16_t Length)
{
    HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET);
}
void StartReadTask(void const* argument)
{
    CAN_Init(&hcan1, CAN_Motor_Call_Back);
    UART_Init(&huart6,UART_RefereeSystem_Call_Back,10);
    //类创建与初始化
    Joint1.Init(&hcan1,CAN_Motor_ID_0x201,Control_Method_ANGLE);
    Joint2.Init(&hcan1,CAN_Motor_ID_0x202,Control_Method_ANGLE);
    Joint3.Init(&hcan1,CAN_Motor_ID_0x203,Control_Method_ANGLE);
    Joint4.Init(&hcan1,CAN_Motor_ID_0x204,Control_Method_ANGLE);
    for (;;)
    {
        uint8_t* ptemp = float_To_uint8_t(Joint1.Get_Now_Angle());
        for (uint8_t i = 0; i<4;i++)
        {
            Package.AngleOfJoint1[i] = ptemp[i];
        }
        ptemp = float_To_uint8_t(Joint2.Get_Now_Angle());
        for (uint8_t i = 0; i<4;i++)
        {
            Package.AngleOfJoint2[i] = ptemp[i];
        }
        ptemp = float_To_uint8_t(Joint3.Get_Now_Angle());
        for (uint8_t i = 0; i<4;i++)
        {
            Package.AngleOfJoint3[i] = ptemp[i];
        }
        ptemp = float_To_uint8_t(Joint4.Get_Now_Angle());
        for (uint8_t i = 0; i<4;i++)
        {
            Package.AngleOfJoint4[i] = ptemp[i];
        }

        UART_Send_Data(&huart6,referee_pack_data(CUSTOM_ROBOT_DATA_CMD_ID,Package.AngleOfJoint1,24),getRefSentDataLen());

        HAL_GPIO_TogglePin(LED_B_GPIO_Port, LED_B_Pin);
        osDelay(100);
    }
}


uint8_t* float_To_uint8_t(float fnum)
{
    static float temp;
    temp = fnum;
    return reinterpret_cast<uint8_t*>(&temp);
}