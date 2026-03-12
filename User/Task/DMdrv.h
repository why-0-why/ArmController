#pragma once
#include "main.h"
#include "drv_can.h"
#define MIT_MODE 			0x000
#define POS_MODE			0x100
#define SPEED_MODE		0x200

#define P_MIN -12.5f
#define P_MAX 12.5f
#define V_MIN -30.0f
#define V_MAX 30.0f
#define KP_MIN 0.0f
#define KP_MAX 500.0f
#define KD_MIN 0.0f
#define KD_MAX 5.0f
#define T_MIN -10.0f
#define T_MAX 10.0f

    // 电机回传信息结构体
    typedef struct
    {
        int id;
        int state;
        int p_int;
        int v_int;
        int t_int;
        int kp_int;
        int kd_int;
        float pos;
        float vel;
        float tor;
        float Kp;
        float Kd;
        float Tmos;
        float Tcoil;
    }motor_fbpara_t;

// 电机参数设置结构体
typedef struct
{
    int8_t mode;
    float pos_set;
    float vel_set;
    float tor_set;
    float kp_set;
    float kd_set;
}motor_ctrl_t;

typedef struct
{
    int8_t id;
    uint8_t start_flag;
    motor_fbpara_t para;
    motor_ctrl_t ctrl;
    motor_ctrl_t cmd;
}motor_t;

void COMM_DM4310EnableMotor();
void COMM_DM4310LockMotor();
void COMM_DM4310SetZero();
void dm4310_fbdata(motor_t *motor, uint8_t *rx_data);
void mit_ctrl(float pos, float vel,float kp, float kd, float torq);