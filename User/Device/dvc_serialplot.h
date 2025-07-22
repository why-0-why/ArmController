#ifndef DVC_SERIALPLOT_H
#define DVC_SERIALPLOT_H

/* Includes ------------------------------------------------------------------*/

#include <stdarg.h>
#include <string.h>
#include <math.h>
#include "drv_uart.h"

/* Exported macros -----------------------------------------------------------*/

// 串口绘图单条指令最大长度
#define SERIALPLOT_RX_VARIABLE_ASSIGNMENT_MAX_LENGTH (100)

/* Exported types ------------------------------------------------------------*/

/**
 * @brief 串口绘图传输数据类型
 */
enum Enum_Serialplot_Data_Type {
    Serialplot_Data_Type_UINT8 = 0,
    Serialplot_Data_Type_UINT16,
    Serialplot_Data_Type_UINT32,
    Serialplot_Data_Type_INT8,
    Serialplot_Data_Type_INT16,
    Serialplot_Data_Type_INT32,
    Serialplot_Data_Type_FLOAT,
    Serialplot_Data_Type_DOUBLE,
};

// 前向声明（C兼容）
typedef struct Class_Serialplot Class_Serialplot;

// C兼容接口声明
#ifdef __cplusplus
extern "C" {
#endif

// 创建串口绘图对象
Class_Serialplot* Serialplot_Create(void);

// 初始化串口绘图
void Serialplot_Init(
    Class_Serialplot* obj,
    UART_HandleTypeDef* huart,
    uint8_t __Serialplot_Rx_Variable_Assignment_Num,
    char** __Serialplot_Rx_Variable_Assignment_List,
    enum Enum_Serialplot_Data_Type __Serialplot_Data_Type,
    uint8_t __Frame_Header
);

// 获取变量索引
int8_t Serialplot_Get_Variable_Index(Class_Serialplot* obj);

// 获取变量值
double Serialplot_Get_Variable_Value(Class_Serialplot* obj);

// 设置数据
void Serialplot_Set_Data(Class_Serialplot* obj, uint8_t Number, ...);

// UART接收回调
void Serialplot_UART_RxCpltCallback(Class_Serialplot* obj, uint8_t* Rx_Data);

// 定时器中断回调
void Serialplot_TIM_Write_PeriodElapsedCallback(Class_Serialplot* obj);

// 销毁对象
void Serialplot_Destroy(Class_Serialplot* obj);

#ifdef __cplusplus
}
#endif

/* C++部分 */
#ifdef __cplusplus

/**
 * @brief 串口绘图工具, 最多支持12个通道
 */
class Class_Serialplot {
public:
    void Init(UART_HandleTypeDef* huart, uint8_t __Serialplot_Rx_Variable_Assignment_Num = 0, 
              char** __Serialplot_Rx_Variable_Assignment_List = NULL, 
              Enum_Serialplot_Data_Type __Serialplot_Data_Type = Serialplot_Data_Type_FLOAT, 
              uint8_t __Frame_Header = 0xab);

    int8_t Get_Variable_Index();
    double Get_Variable_Value();

    void Set_Data(uint8_t Number, ...);

    void UART_RxCpltCallback(uint8_t* Rx_Data);
    void TIM_Write_PeriodElapsedCallback();

protected:
    // 初始化相关常量
    Struct_UART_Manage_Object* UART_Manage_Object;
    uint8_t UART_Rx_Variable_Num;
    char** UART_Rx_Variable_List;
    Enum_Serialplot_Data_Type UART_Tx_Data_Type;
    uint8_t Frame_Header;

    // 内部变量
    const void* Data[12];
    uint8_t Data_Number = 0;
    int8_t Variable_Index = 0;
    float Variable_Value = 0.0f;

    // 内部函数
    uint8_t Judge_Variable_Name();
    void Judge_Variable_Value(int flag);
    void Output();
};

#endif /* __cplusplus */

/* Exported variables --------------------------------------------------------*/

/* Exported function declarations --------------------------------------------*/

#endif