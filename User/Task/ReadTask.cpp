#include "ReadTask.h"

extern "C"{
#include "main.h"
#include "cmsis_os.h"
#include "usart.h"
#include "drv_can.h"
#include "drv_uart.h"
#include "drv_RefereeSystem.h"
}// C实现函数，只要用到C函数就要extern，否则编译器会认为这是两个函数，因为Cpp编译器给函数的命名与C编译器给函数命名不一样
#include "dvc_motor.h"
#include "pro_UserController.h"

uint8_t* float_To_uint8_t(float fnum);

/*
 * @brief 电机轴对象
 */
Class_Motor_C610 Joint1;
Class_Motor_C610 Joint2;//有减速
Class_Motor_C610 Joint3;//有减速
Class_Motor_C620 Joint4;
Class_Motor_C610 Joint5;
Class_Motor_C610 Joint6;

bool buttonJ6_flag = false;
bool buttonred_flag = false;
bool buttongre_flag = false;
bool buttonora_flag = false;
bool buttonbla_flag = false;

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
    case (0x204):
        {
            Joint4.CAN_RxCpltCallback(Rx_Buffer->Data);
        }
        break;
    case (0x205):
        {
            Joint5.CAN_RxCpltCallback(Rx_Buffer->Data);
        }
        break;
    case (0x206):
        {
            Joint6.CAN_RxCpltCallback(Rx_Buffer->Data);
        }
        break;
    default:
        break;
    }
}

/**
 * @brief UART报文回调函数,点亮LED展示收到消息
 * @param Buffer
 * @param Length
 */
void UART_RefereeSystem_Call_Back(uint8_t* Buffer, uint16_t Length)
{
    HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET);
}

/**
 * @brief 启动任务
 * @param argument
 */
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

        Package.AngleOfJoint1 = Joint1.Get_Now_Angle()*36.0f;//2006无减速器
        Package.AngleOfJoint2 =Joint2.Get_Now_Angle();//2006有减速器
        Package.AngleOfJoint3 =-Joint3.Get_Now_Angle();//2006有减速器
        Package.AngleOfJoint4 =-Joint4.Get_Now_Angle()* 3591.0f / 187.0f;//3508无减速器
        Package.AngleOfJoint5 =Joint5.Get_Now_Angle()*36.0f;//2006无减速器
        Package.AngleOfJoint6 =Joint6.Get_Now_Angle()*36.0f;//2006无减速器

        //清楚按键标志位
        Package.Button_J6 = 0;
        Package.Button_red = 0;
        Package.Button_green = 0;
        Package.Button_orange = 0;
        Package.Button_black = 0;
        Package.null_field = 0;

        //J6
        if (HAL_GPIO_ReadPin(Button_J6_GPIO_Port, Button_J6_Pin) == GPIO_PIN_SET)//10ms消抖
        {
            if (buttonJ6_flag == true)
                Package.Button_J6 = true;
            else
                buttonJ6_flag=true;
        }
        else
            buttonJ6_flag=false;

        //red
        if (HAL_GPIO_ReadPin(Button_red_GPIO_Port, Button_red_Pin) == GPIO_PIN_SET)//10ms消抖
        {
            if (buttonred_flag == true)
                Package.Button_red = true;
            else
                buttonred_flag=true;
        }
        else
            buttonred_flag=false;

        //gre
        if (HAL_GPIO_ReadPin(Button_green_GPIO_Port, Button_green_Pin) == GPIO_PIN_SET)//10ms消抖
        {
            if (buttongre_flag == true)
                Package.Button_green = true;
            else
                buttongre_flag=true;
        }
        else
            buttongre_flag=false;

        //ora
        if (HAL_GPIO_ReadPin(Button_orange_GPIO_Port, Button_orange_Pin) == GPIO_PIN_SET)//10ms消抖
        {
            if (buttonora_flag == true)
                Package.Button_orange = true;
            else
                buttonora_flag=true;
        }
        else
            buttonora_flag=false;

        //bla
        if (HAL_GPIO_ReadPin(Button_black_GPIO_Port, Button_black_Pin) == GPIO_PIN_SET)//10ms消抖
        {
            if (buttonbla_flag == true)
                Package.Button_black = true;
            else
                buttonbla_flag=true;
        }
        else
            buttonbla_flag=false;

        //发送数据
        UART_Send_Data(&huart6,referee_pack_data(CUSTOM_ROBOT_DATA_CMD_ID,(uint8_t*)&Package,30),getRefSentDataLen());

        HAL_GPIO_TogglePin(LED_B_GPIO_Port, LED_B_Pin);
        osDelay(40);//25hz
    }
}


uint8_t* float_To_uint8_t(float fnum)
{
    static float temp;
    temp = fnum;
    return reinterpret_cast<uint8_t*>(&temp);
}