#include "drv_RefereeSystem.h"
#include "string.h"
#include "alg_crc.h"

static referee_frame_processer_t referee_frame_processer; // 数据解包结构体

/*
 * @brief 打包裁判系统数据包
 *
 * @param cmd_id 命令号
 * @param data 数据数组
 * @param data_len 数据长度
 * @return 打包完成的数组
 */
uint8_t *referee_pack_data(uint16_t cmd_id, uint8_t *data, uint16_t data_len)
{
    referee_frame_processer.sent_data_len = REF_HEADER_CRC_CMDID_LEN + data_len;

    memset(referee_frame_processer.sent_package, 0, REF_PROTOCOL_FRAME_MAX_SIZE);

    referee_frame_processer.sent_frame_header.SOF = HEADER_SOF;

    referee_frame_processer.sent_frame_header.data_length[0] = data_len;
    referee_frame_processer.sent_frame_header.data_length[1] = 0x00;

    memcpy(referee_frame_processer.sent_package, &referee_frame_processer.sent_frame_header,
           REF_PROTOCOL_HEADER_SIZE - 1);

    referee_frame_processer.sent_frame_header.CRC8 =
        get_CRC8_check_sum(referee_frame_processer.sent_package, REF_PROTOCOL_HEADER_SIZE - 1, 0xff);

    memcpy(referee_frame_processer.sent_package, &referee_frame_processer.sent_frame_header, REF_PROTOCOL_HEADER_SIZE);

    referee_frame_processer.sent_frame_header.seq++;

    referee_frame_processer.sent_package[5] = cmd_id & 0xff;
    referee_frame_processer.sent_package[6] = (cmd_id >> 8) & 0xff;

    memcpy(referee_frame_processer.sent_package + REF_HEADER_CMDID_LEN, data, data_len);

    append_CRC16_check_sum(referee_frame_processer.sent_package, referee_frame_processer.sent_data_len);

    return referee_frame_processer.sent_package;
}

/*
 * @brief 返回当前帧长度
 *
 * @return 当前帧长度
 */
uint16_t getRefSentDataLen(void)
{
    return referee_frame_processer.sent_data_len;
}