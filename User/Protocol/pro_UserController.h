//
// Created by why on 25-10-8.
//

#ifndef PRO_USERCONTROLLER_H
#define PRO_USERCONTROLLER_H
#include <sys/_stdint.h>

/*
 * @brief 自定义控制器信息包
 *
 * @note 共24字节，每四字节为一个float数据对应该关节的角度
 */
typedef struct
{
    uint8_t AngleOfJoint1[4];
    uint8_t AngleOfJoint2[4];
    uint8_t AngleOfJoint3[4];
    uint8_t AngleOfJoint4[4];
    uint8_t AngleOfJoint5[4];
    uint8_t AngleOfJoint6[4];
} user_package_t;

#endif //PRO_USERCONTROLLER_H
