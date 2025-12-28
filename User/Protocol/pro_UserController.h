//
// Created by why on 25-10-8.
//

#ifndef PRO_USERCONTROLLER_H
#define PRO_USERCONTROLLER_H
#include <sys/_stdint.h>

#pragma pack(push, 1)
/*
 * @brief 自定义控制器信息包
 *
 * @note 共24字节，每四字节为一个float数据对应该关节的角度
 */
typedef struct
{
    float AngleOfJoint1;
    float AngleOfJoint2;
    float AngleOfJoint3;
    float AngleOfJoint4;
    float AngleOfJoint5;
    float AngleOfJoint6;
    uint8_t Button_J6;
    uint8_t Button_red;
    uint8_t Button_green;
    uint8_t Button_orange;
    uint8_t Button_black;
    uint8_t null_field;
} user_package_t;
#pragma pack(pop)

#endif //PRO_USERCONTROLLER_H
