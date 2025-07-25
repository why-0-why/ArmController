/**
* @file alg_pid_capi.cpp
 * @author why
 * @brief pid对象的C语言接口
 * @date 2025-07-25
 *
 */
#include "alg_pid.h"

/* 创建与销毁 */
Class_PID* PID_Create()
{
    return new Class_PID();
}

void PID_Destory(Class_PID* pid)
{
    delete pid;
}

/* 初始化 */
void PID_Init(
    Class_PID* pid,
    float k_p,
    float k_i,
    float k_d,
    float k_f,
    float i_out_max,
    float out_max,
    float d_t,
    float dead_zone,
    float i_variable_speed_a,
    float i_variable_speed_b,
    float i_separate_threshold,
    enum Enum_PID_D_First d_first)
{
    if (!pid) return;
    pid->Init(k_p, k_i, k_d, k_f, i_out_max, out_max, d_t, dead_zone,
              i_variable_speed_a, i_variable_speed_b, i_separate_threshold, d_first);
}

/* 获取函数 */
float PID_Get_Integral_Error(Class_PID* pid)
{
    return pid ? pid->Get_Integral_Error() : 0.0f;
}

float PID_Get_Out(Class_PID* pid)
{
    return pid ? pid->Get_Out() : 0.0f;
}

/* 设置函数 */
void PID_Set_K_P(Class_PID* pid, float k_p)
{
    if (pid) pid->Set_K_P(k_p);
}

void PID_Set_K_I(Class_PID* pid, float k_i)
{
    if (pid) pid->Set_K_I(k_i);
}

void PID_Set_K_D(Class_PID* pid, float k_d)
{
    if (pid) pid->Set_K_D(k_d);
}

void PID_Set_K_F(Class_PID* pid, float k_f)
{
    if (pid) pid->Set_K_F(k_f);
}

void PID_Set_I_Out_Max(Class_PID* pid, float i_out_max)
{
    if (pid) pid->Set_I_Out_Max(i_out_max);
}

void PID_Set_Out_Max(Class_PID* pid, float out_max)
{
    if (pid) pid->Set_Out_Max(out_max);
}

void PID_Set_I_Variable_Speed_A(Class_PID* pid, float a)
{
    if (pid) pid->Set_I_Variable_Speed_A(a);
}

void PID_Set_I_Variable_Speed_B(Class_PID* pid, float b)
{
    if (pid) pid->Set_I_Variable_Speed_B(b);
}

void PID_Set_I_Separate_Threshold(Class_PID* pid, float threshold)
{
    if (pid) pid->Set_I_Separate_Threshold(threshold);
}

void PID_Set_Target(Class_PID* pid, float target)
{
    if (pid) pid->Set_Target(target);
}

void PID_Set_Now(Class_PID* pid, float now)
{
    if (pid) pid->Set_Now(now);
}

void PID_Set_Integral_Error(Class_PID* pid, float integral_error)
{
    if (pid) pid->Set_Integral_Error(integral_error);
}

/* 定时器回调 */
void PID_TIM_Adjust_PeriodElapsedCallback(Class_PID* pid)
{
    if (pid) pid->TIM_Adjust_PeriodElapsedCallback();
}
