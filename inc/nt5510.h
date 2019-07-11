/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-07-01     tyustli      the first version
 *
 */

#ifndef __NT_5510_H_
#define __NT_5510_H_

#include "rtdevice.h"
#include "rtthread.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SET_X_CMD          0x2A00
#define SET_Y_CMD          0x2B00
#define WRITE_GRAM_CMD     0x2C00
#define READ_GRAM_CMD      0x2E00
#define SET_DIR_CMD        0x3600
#define DISPLAY_ON         0x2900
#define DISPLAY_OFF        0x2800
#define READ_ID1           0xDA00
#define READ_ID2           0xDB00
#define READ_ID3           0xDC00

#define L2R_U2D            0x00
#define L2R_D2U            0x01
#define R2L_U2D            0x02
#define R2L_D2U            0x03
#define U2D_L2R            0x04
#define U2D_R2L            0x05
#define D2U_L2R            0x06
#define D2U_R2L            0x07

#define WHITE              0xFFFF
#define BLACK              0x0000
#define RED                0xF800
#define GREEN              0x07E0
#define YELLOW             0xFFE0

int rt_hw_nt5510_init(rt_uint16_t width, rt_uint16_t height, void *user_data);

#ifdef __cplusplus
}
#endif

#endif /* __NT_5510_H_ */

/***************** end of file *********************/
