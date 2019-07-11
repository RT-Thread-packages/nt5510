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

#include "nt5510.h"

#ifdef PKG_USING_NT5510

#define DBG_TAG "nt5510"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static rt_uint16_t set_x_table[] = {0x2A00, 0x2A01, 0x2A02, 0x2A03};
static rt_uint16_t set_y_table[] = {0x2B00, 0x2B01, 0x2B02, 0x2B03};
static rt_uint16_t write_gram_table[] = {0x2C00};
static rt_uint16_t read_gram_table[] = {0x2E00};
static rt_uint16_t display_on_table[] = {0x2900};
static rt_uint16_t table[] = {0x1100};

struct nt5510_function
{
    rt_uint16_t reg;
    rt_uint8_t  data;
};

static struct nt5510_function  nt5510_cfg_script[] =
{
    {0xF000, 0x55},
    {0xF001, 0xAA},
    {0xF002, 0x52},
    {0xF003, 0x08},
    {0xF004, 0x01},
    {0xB000, 0x0D},
    {0xB001, 0x0D},
    {0xB002, 0x0D},
    {0xB600, 0x34},
    {0xB601, 0x34},
    {0xB602, 0x34},
    {0xB100, 0x0D},
    {0xB101, 0x0D},
    {0xB102, 0x0D},
    {0xB700, 0x34},
    {0xB701, 0x34},
    {0xB702, 0x34},
    {0xB200, 0x00},
    {0xB201, 0x00},
    {0xB202, 0x00},
    {0xB800, 0x24},
    {0xB801, 0x24},
    {0xB802, 0x24},
    {0xBF00, 0x01},
    {0xB300, 0x0F},
    {0xB301, 0x0F},
    {0xB302, 0x0F},
    {0xB900, 0x34},
    {0xB901, 0x34},
    {0xB902, 0x34},
    {0xB500, 0x08},
    {0xB501, 0x08},
    {0xB502, 0x08},
    {0xC200, 0x03},
    {0xBA00, 0x24},
    {0xBA01, 0x24},
    {0xBA02, 0x24},
    {0xBC00, 0x00},
    {0xBC01, 0x78},
    {0xBC02, 0x00},
    {0xBD00, 0x00},
    {0xBD01, 0x78},
    {0xBD02, 0x00},
    {0xBE00, 0x00},
    {0xBE01, 0x64},
    {0xD100, 0x00},
    {0xD101, 0x33},
    {0xD102, 0x00},
    {0xD103, 0x34},
    {0xD104, 0x00},
    {0xD105, 0x3A},
    {0xD106, 0x00},
    {0xD107, 0x4A},
    {0xD108, 0x00},
    {0xD109, 0x5C},
    {0xD10A, 0x00},
    {0xD10B, 0x81},
    {0xD10C, 0x00},
    {0xD10D, 0xA6},
    {0xD10E, 0x00},
    {0xD10F, 0xE5},
    {0xD110, 0x01},
    {0xD111, 0x13},
    {0xD112, 0x01},
    {0xD113, 0x54},
    {0xD114, 0x01},
    {0xD115, 0x82},
    {0xD116, 0x01},
    {0xD117, 0xCA},
    {0xD118, 0x02},
    {0xD119, 0x00},
    {0xD11A, 0x02},
    {0xD11B, 0x01},
    {0xD11C, 0x02},
    {0xD11D, 0x34},
    {0xD11E, 0x02},
    {0xD11F, 0x67},
    {0xD120, 0x02},
    {0xD121, 0x84},
    {0xD122, 0x02},
    {0xD123, 0xA4},
    {0xD124, 0x02},
    {0xD125, 0xB7},
    {0xD126, 0x02},
    {0xD127, 0xCF},
    {0xD128, 0x02},
    {0xD129, 0xDE},
    {0xD12A, 0x02},
    {0xD12B, 0xF2},
    {0xD12C, 0x02},
    {0xD12D, 0xFE},
    {0xD12E, 0x03},
    {0xD12F, 0x10},
    {0xD130, 0x03},
    {0xD131, 0x33},
    {0xD132, 0x03},
    {0xD133, 0x6D},
    {0xD200, 0x00},
    {0xD201, 0x33},
    {0xD202, 0x00},
    {0xD203, 0x34},
    {0xD204, 0x00},
    {0xD205, 0x3A},
    {0xD206, 0x00},
    {0xD207, 0x4A},
    {0xD208, 0x00},
    {0xD209, 0x5C},
    {0xD20A, 0x00},
    {0xD20B, 0x81},
    {0xD20C, 0x00},
    {0xD20D, 0xA6},
    {0xD20E, 0x00},
    {0xD20F, 0xE5},
    {0xD210, 0x01},
    {0xD211, 0x13},
    {0xD212, 0x01},
    {0xD213, 0x54},
    {0xD214, 0x01},
    {0xD215, 0x82},
    {0xD216, 0x01},
    {0xD217, 0xCA},
    {0xD218, 0x02},
    {0xD219, 0x00},
    {0xD21A, 0x02},
    {0xD21B, 0x01},
    {0xD21C, 0x02},
    {0xD21D, 0x34},
    {0xD21E, 0x02},
    {0xD21F, 0x67},
    {0xD220, 0x02},
    {0xD221, 0x84},
    {0xD222, 0x02},
    {0xD223, 0xA4},
    {0xD224, 0x02},
    {0xD225, 0xB7},
    {0xD226, 0x02},
    {0xD227, 0xCF},
    {0xD228, 0x02},
    {0xD229, 0xDE},
    {0xD22A, 0x02},
    {0xD22B, 0xF2},
    {0xD22C, 0x02},
    {0xD22D, 0xFE},
    {0xD22E, 0x03},
    {0xD22F, 0x10},
    {0xD230, 0x03},
    {0xD231, 0x33},
    {0xD232, 0x03},
    {0xD233, 0x6D},
    {0xD300, 0x00},
    {0xD301, 0x33},
    {0xD302, 0x00},
    {0xD303, 0x34},
    {0xD304, 0x00},
    {0xD305, 0x3A},
    {0xD306, 0x00},
    {0xD307, 0x4A},
    {0xD308, 0x00},
    {0xD309, 0x5C},
    {0xD30A, 0x00},
    {0xD30B, 0x81},
    {0xD30C, 0x00},
    {0xD30D, 0xA6},
    {0xD30E, 0x00},
    {0xD30F, 0xE5},
    {0xD310, 0x01},
    {0xD311, 0x13},
    {0xD312, 0x01},
    {0xD313, 0x54},
    {0xD314, 0x01},
    {0xD315, 0x82},
    {0xD316, 0x01},
    {0xD317, 0xCA},
    {0xD318, 0x02},
    {0xD319, 0x00},
    {0xD31A, 0x02},
    {0xD31B, 0x01},
    {0xD31C, 0x02},
    {0xD31D, 0x34},
    {0xD31E, 0x02},
    {0xD31F, 0x67},
    {0xD320, 0x02},
    {0xD321, 0x84},
    {0xD322, 0x02},
    {0xD323, 0xA4},
    {0xD324, 0x02},
    {0xD325, 0xB7},
    {0xD326, 0x02},
    {0xD327, 0xCF},
    {0xD328, 0x02},
    {0xD329, 0xDE},
    {0xD32A, 0x02},
    {0xD32B, 0xF2},
    {0xD32C, 0x02},
    {0xD32D, 0xFE},
    {0xD32E, 0x03},
    {0xD32F, 0x10},
    {0xD330, 0x03},
    {0xD331, 0x33},
    {0xD332, 0x03},
    {0xD333, 0x6D},
    {0xD400, 0x00},
    {0xD401, 0x33},
    {0xD402, 0x00},
    {0xD403, 0x34},
    {0xD404, 0x00},
    {0xD405, 0x3A},
    {0xD406, 0x00},
    {0xD407, 0x4A},
    {0xD408, 0x00},
    {0xD409, 0x5C},
    {0xD40A, 0x00},
    {0xD40B, 0x81},
    {0xD40C, 0x00},
    {0xD40D, 0xA6},
    {0xD40E, 0x00},
    {0xD40F, 0xE5},
    {0xD410, 0x01},
    {0xD411, 0x13},
    {0xD412, 0x01},
    {0xD413, 0x54},
    {0xD414, 0x01},
    {0xD415, 0x82},
    {0xD416, 0x01},
    {0xD417, 0xCA},
    {0xD418, 0x02},
    {0xD419, 0x00},
    {0xD41A, 0x02},
    {0xD41B, 0x01},
    {0xD41C, 0x02},
    {0xD41D, 0x34},
    {0xD41E, 0x02},
    {0xD41F, 0x67},
    {0xD420, 0x02},
    {0xD421, 0x84},
    {0xD422, 0x02},
    {0xD423, 0xA4},
    {0xD424, 0x02},
    {0xD425, 0xB7},
    {0xD426, 0x02},
    {0xD427, 0xCF},
    {0xD428, 0x02},
    {0xD429, 0xDE},
    {0xD42A, 0x02},
    {0xD42B, 0xF2},
    {0xD42C, 0x02},
    {0xD42D, 0xFE},
    {0xD42E, 0x03},
    {0xD42F, 0x10},
    {0xD430, 0x03},
    {0xD431, 0x33},
    {0xD432, 0x03},
    {0xD433, 0x6D},
    {0xD500, 0x00},
    {0xD501, 0x33},
    {0xD502, 0x00},
    {0xD503, 0x34},
    {0xD504, 0x00},
    {0xD505, 0x3A},
    {0xD506, 0x00},
    {0xD507, 0x4A},
    {0xD508, 0x00},
    {0xD509, 0x5C},
    {0xD50A, 0x00},
    {0xD50B, 0x81},
    {0xD50C, 0x00},
    {0xD50D, 0xA6},
    {0xD50E, 0x00},
    {0xD50F, 0xE5},
    {0xD510, 0x01},
    {0xD511, 0x13},
    {0xD512, 0x01},
    {0xD513, 0x54},
    {0xD514, 0x01},
    {0xD515, 0x82},
    {0xD516, 0x01},
    {0xD517, 0xCA},
    {0xD518, 0x02},
    {0xD519, 0x00},
    {0xD51A, 0x02},
    {0xD51B, 0x01},
    {0xD51C, 0x02},
    {0xD51D, 0x34},
    {0xD51E, 0x02},
    {0xD51F, 0x67},
    {0xD520, 0x02},
    {0xD521, 0x84},
    {0xD522, 0x02},
    {0xD523, 0xA4},
    {0xD524, 0x02},
    {0xD525, 0xB7},
    {0xD526, 0x02},
    {0xD527, 0xCF},
    {0xD528, 0x02},
    {0xD529, 0xDE},
    {0xD52A, 0x02},
    {0xD52B, 0xF2},
    {0xD52C, 0x02},
    {0xD52D, 0xFE},
    {0xD52E, 0x03},
    {0xD52F, 0x10},
    {0xD530, 0x03},
    {0xD531, 0x33},
    {0xD532, 0x03},
    {0xD533, 0x6D},
    {0xD600, 0x00},
    {0xD601, 0x33},
    {0xD602, 0x00},
    {0xD603, 0x34},
    {0xD604, 0x00},
    {0xD605, 0x3A},
    {0xD606, 0x00},
    {0xD607, 0x4A},
    {0xD608, 0x00},
    {0xD609, 0x5C},
    {0xD60A, 0x00},
    {0xD60B, 0x81},
    {0xD60C, 0x00},
    {0xD60D, 0xA6},
    {0xD60E, 0x00},
    {0xD60F, 0xE5},
    {0xD610, 0x01},
    {0xD611, 0x13},
    {0xD612, 0x01},
    {0xD613, 0x54},
    {0xD614, 0x01},
    {0xD615, 0x82},
    {0xD616, 0x01},
    {0xD617, 0xCA},
    {0xD618, 0x02},
    {0xD619, 0x00},
    {0xD61A, 0x02},
    {0xD61B, 0x01},
    {0xD61C, 0x02},
    {0xD61D, 0x34},
    {0xD61E, 0x02},
    {0xD61F, 0x67},
    {0xD620, 0x02},
    {0xD621, 0x84},
    {0xD622, 0x02},
    {0xD623, 0xA4},
    {0xD624, 0x02},
    {0xD625, 0xB7},
    {0xD626, 0x02},
    {0xD627, 0xCF},
    {0xD628, 0x02},
    {0xD629, 0xDE},
    {0xD62A, 0x02},
    {0xD62B, 0xF2},
    {0xD62C, 0x02},
    {0xD62D, 0xFE},
    {0xD62E, 0x03},
    {0xD62F, 0x10},
    {0xD630, 0x03},
    {0xD631, 0x33},
    {0xD632, 0x03},
    {0xD633, 0x6D},
    {0xF000, 0x55},
    {0xF001, 0xAA},
    {0xF002, 0x52},
    {0xF003, 0x08},
    {0xF004, 0x00},
    {0xB100, 0xCC},
    {0xB101, 0x00},
    {0xB600, 0x05},
    {0xB700, 0x70},
    {0xB701, 0x70},
    {0xB800, 0x01},
    {0xB801, 0x03},
    {0xB802, 0x03},
    {0xB803, 0x03},
    {0xBC00, 0x02},
    {0xBC01, 0x00},
    {0xBC02, 0x00},
    {0xC900, 0xD0},
    {0xC901, 0x02},
    {0xC902, 0x50},
    {0xC903, 0x50},
    {0xC904, 0x50},
    {0x3500, 0x00},
    {0x3A00, 0x55},
};
#define CFG_SCRIPT_LEN          (sizeof(nt5510_cfg_script) / sizeof(nt5510_cfg_script[0]))

struct nt5510_device
{
    struct rt_device parent;
    struct rt_lcd_device *lcd;
    rt_uint8_t dir;
};
static struct nt5510_device lcd_device;

static void _nt5510_delay(rt_uint8_t i)
{
    while(i--);
}

static void _nt5510_set_cursor(rt_uint32_t x, rt_uint32_t y)
{
    rt_uint32_t send_x, send_y;

    send_x = x >> 8;
    rt_lcd_write_cmd(lcd_device.lcd->intf, &set_x_table[0], 1);
    rt_lcd_write_data(lcd_device.lcd->intf, &send_x, 1);

    send_x = x & 0xff;
    rt_lcd_write_cmd(lcd_device.lcd->intf, &set_x_table[1], 1);
    rt_lcd_write_data(lcd_device.lcd->intf, &send_x, 1);

    send_y = y >> 8;
    rt_lcd_write_cmd(lcd_device.lcd->intf,  &set_y_table[0], 1);
    rt_lcd_write_data(lcd_device.lcd->intf, &send_y, 1);

    send_y = y & 0xff;
    rt_lcd_write_cmd(lcd_device.lcd->intf, &set_y_table[1], 1);
    rt_lcd_write_data(lcd_device.lcd->intf, &send_y, 1);
}

static void _nt5510_set_dir(rt_uint8_t dir)
{
    rt_uint32_t regval = 0;

    if(lcd_device.dir == 1)
    {
        switch(dir)
        {
        case 0:
            dir = 6;
            break;
        case 1:
            dir = 7;
            break;
        case 2:
            dir = 4;
            break;
        case 3:
            dir = 5;
            break;
        case 4:
            dir = 1;
            break;
        case 5:
            dir = 0;
            break;
        case 6:
            dir = 3;
            break;
        case 7:
            dir = 2;
            break;
        }
    }

    switch(dir)
    {
    case L2R_U2D:
        regval |= (0 << 7) | (0 << 6) | (0 << 5);
        break;
    case L2R_D2U:
        regval |= (1 << 7) | (0 << 6) | (0 << 5);
        break;
    case R2L_U2D:
        regval |= (0 << 7) | (1 << 6) | (0 << 5);
        break;
    case R2L_D2U:
        regval |= (1 << 7) | (1 << 6) | (0 << 5);
        break;
    case U2D_L2R:
        regval |= (0 << 7) | (0 << 6) | (1 << 5);
        break;
    case U2D_R2L:
        regval |= (0 << 7) | (1 << 6) | (1 << 5);
        break;
    case D2U_L2R:
        regval |= (1 << 7) | (0 << 6) | (1 << 5);
        break;
    case D2U_R2L:
        regval |= (1 << 7) | (1 << 6) | (1 << 5);
        break;
    }

    rt_lcd_write_reg(lcd_device.lcd->intf, SET_DIR_CMD, regval);
    rt_lcd_write_reg(lcd_device.lcd->intf, SET_X_CMD, 0);
    rt_lcd_write_reg(lcd_device.lcd->intf, SET_X_CMD + 1, 0);
    rt_lcd_write_reg(lcd_device.lcd->intf, SET_X_CMD + 2, (lcd_device.lcd->gra_info.width - 1) >> 8);
    rt_lcd_write_reg(lcd_device.lcd->intf, SET_X_CMD + 3, (lcd_device.lcd->gra_info.width - 1) & 0x00FF);
    rt_lcd_write_reg(lcd_device.lcd->intf, SET_Y_CMD, 0);
    rt_lcd_write_reg(lcd_device.lcd->intf, SET_Y_CMD + 1, 0);
    rt_lcd_write_reg(lcd_device.lcd->intf, SET_Y_CMD + 2, (lcd_device.lcd->gra_info.height - 1) >> 8);
    rt_lcd_write_reg(lcd_device.lcd->intf, SET_Y_CMD + 3, (lcd_device.lcd->gra_info.height - 1) & 0x00FF);

    return;
}

static void _nt5510_display_dir(rt_uint8_t dir)
{
    rt_uint32_t width, height;

    lcd_device.dir = dir;
    width = lcd_device.lcd->gra_info.width;
    height = lcd_device.lcd->gra_info.height;

    if(dir == 0)
    {
        lcd_device.lcd->gra_info.width = width;
        lcd_device.lcd->gra_info.height = height;
    }
    else
    {
        lcd_device.lcd->gra_info.width = height;
        lcd_device.lcd->gra_info.height = width;
    }

    _nt5510_set_dir(L2R_U2D);

    return;
}

static void _nt5510_set_windows(rt_uint32_t sx, rt_uint32_t sy, rt_uint32_t width, rt_uint32_t height)
{
    rt_uint32_t twidth;
    rt_uint32_t theight;
    rt_uint32_t send_x, send_y;
    rt_uint32_t send_w, send_h;

    twidth = sx + width;
    theight = sy + height;

    send_x = sx >> 8;
    rt_lcd_write_cmd(lcd_device.lcd->intf, &set_x_table[0], 1);
    rt_lcd_write_data(lcd_device.lcd->intf, &send_x, 1);

    send_x = sx & 0xff;
    rt_lcd_write_cmd(lcd_device.lcd->intf, &set_x_table[1], 1);
    rt_lcd_write_data(lcd_device.lcd->intf, &send_x, 1);

    send_w = twidth >> 8;
    rt_lcd_write_cmd(lcd_device.lcd->intf, &set_x_table[2], 1);
    rt_lcd_write_data(lcd_device.lcd->intf, &send_w, 1);

    send_w = twidth & 0xff;
    rt_lcd_write_cmd(lcd_device.lcd->intf, &set_x_table[3], 1);
    rt_lcd_write_data(lcd_device.lcd->intf, &twidth, 1);

    send_y = sy >> 8;
    rt_lcd_write_cmd(lcd_device.lcd->intf, &set_y_table[0], 1);
    rt_lcd_write_data(lcd_device.lcd->intf, &send_y, 1);

    send_y = sy & 0xff;
    rt_lcd_write_cmd(lcd_device.lcd->intf, &set_y_table[1], 1);
    rt_lcd_write_data(lcd_device.lcd->intf, &send_y, 1);

    send_h = theight >> 8;
    rt_lcd_write_cmd(lcd_device.lcd->intf, &set_y_table[2], 1);
    rt_lcd_write_data(lcd_device.lcd->intf, &send_h, 1);

    send_h = theight & 0xff;
    rt_lcd_write_cmd(lcd_device.lcd->intf, &set_y_table[3], 1);
    rt_lcd_write_data(lcd_device.lcd->intf, &send_h, 1);

    return;
}

static rt_err_t _nt5510_init_display(struct rt_device *lcd_dev)
{
    rt_uint32_t index;

    for (index = 0; index < CFG_SCRIPT_LEN; index++)
    {
        rt_lcd_write_reg(lcd_device.lcd->intf, nt5510_cfg_script[index].reg, nt5510_cfg_script[index].data);
    }

    rt_lcd_write_cmd(lcd_device.lcd->intf, &table[0], 1);
    rt_thread_mdelay(1);
    rt_lcd_write_cmd(lcd_device.lcd->intf, &display_on_table[0], 1);         /* display on */

    return RT_EOK;
}

static void _nt5510_set_pixel(const char *pixel, int x, int y)
{
    _nt5510_set_cursor(x, y);
    rt_lcd_write_cmd(lcd_device.lcd->intf, &write_gram_table[0], 1);
    rt_lcd_write_data(lcd_device.lcd->intf, (rt_uint32_t *)pixel, 1);        /* rgb565 */

    return;
}

static void _nt5510_get_pixel(char *pixel, int x, int y)
{
    rt_uint16_t r = 0;
    rt_uint16_t g = 0;
    rt_uint16_t b = 0;

    if(x >= lcd_device.lcd->gra_info.width || y >= lcd_device.lcd->gra_info.height)
        return ;

    _nt5510_set_cursor(x, y);
    rt_lcd_write_cmd(lcd_device.lcd->intf, &read_gram_table[0], 1);
    r = rt_lcd_read_data(lcd_device.lcd->intf, 0xffff);                       /* dummy data */
    _nt5510_delay(2);
    r = rt_lcd_read_data(lcd_device.lcd->intf, 0xffff);
    _nt5510_delay(2);
    b = rt_lcd_read_data(lcd_device.lcd->intf, 0xffff);
    g = r & 0xFF;
    g <<= 8;

    *(rt_uint32_t *)pixel = (((r >> 11) << 11) | ((g >> 10) << 5) | (b >> 11));  /* rgb565 */

    return;
}

static void _nt5510_draw_hline(const char *pixel, int x1, int x2, int y)
{
    rt_uint16_t width = x2 - x1;
    _nt5510_set_windows(x1, y, width, 0);
    rt_lcd_write_cmd(lcd_device.lcd->intf, &write_gram_table[0], 1);

    while(width--)
    {
        rt_lcd_write_data(lcd_device.lcd->intf, (rt_uint32_t *)pixel, 1);   /* pixel is fix */
    }

    return;
}

static void _nt5510_draw_vline(const char *pixel, int x, int y1, int y2)
{

    rt_uint16_t height = y2 - y1;
    _nt5510_set_windows(x, y1, 0, height);
    rt_lcd_write_cmd(lcd_device.lcd->intf, &write_gram_table[0], 1);

    while(height--)
    {
        rt_lcd_write_data(lcd_device.lcd->intf, (rt_uint32_t *)pixel, 1);     /* pixel is fix */
    }

    return;
}

static void _nt5510_blit_line(const char *pixel, int x, int y, rt_size_t size)
{
    rt_uint32_t *ptr;
    rt_size_t index;

    ptr = (rt_uint32_t *)pixel;
    _nt5510_set_cursor(x, y);
    rt_lcd_write_cmd(lcd_device.lcd->intf, &write_gram_table[0], 1);

    for(index = 0; index < size; index++)
    {
        rt_lcd_write_data(lcd_device.lcd->intf, ptr++, 1);                   /* pixel is change */
    }

    return;
}

static struct rt_device_graphic_ops _nt5510_ops =
{
    _nt5510_set_pixel,
    _nt5510_get_pixel,
    _nt5510_draw_hline,
    _nt5510_draw_vline,
    _nt5510_blit_line,
};

static rt_err_t _nt5510_control(struct rt_device *device, int cmd, void *args)
{
    RT_ASSERT(device != RT_NULL);

    switch (cmd)
    {
    case RTGRAPHIC_CTRL_RECT_UPDATE:
        break;

    case RTGRAPHIC_CTRL_POWERON:
        rt_pin_write(lcd_device.lcd->bl_pin, PIN_HIGH);
        break;

    case RTGRAPHIC_CTRL_POWEROFF:
        rt_pin_write(lcd_device.lcd->bl_pin, PIN_LOW);
        break;

    case RTGRAPHIC_CTRL_GET_INFO:
    {
        *(struct rt_device_graphic_info *)args = lcd_device.lcd->gra_info;
    }
    break;

    case RTGRAPHIC_CTRL_SET_MODE:
        break;

    case RTGRAPHIC_CTRL_GET_EXT:
        break;
    }

    return RT_EOK;
}


#ifdef RT_USING_DEVICE_OPS
static const struct rt_device_ops lcd_device_ops =
{
    _nt5510_init_display,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    _nt5510_control,
};
#endif /* RT_USING_DEVICE_OPS */

int rt_hw_nt5510_init(struct rt_lcd_device *config, const char *name)
{
    rt_err_t result;
    struct rt_device *device;

    result = RT_EOK;
    device = RT_NULL;
    /* create lcd device */
    lcd_device.lcd = (struct rt_lcd_device *)rt_malloc(sizeof(struct rt_lcd_device));
    if (lcd_device.lcd == RT_NULL)
    {
        LOG_E("malloc memory failed\n");
        return -RT_ERROR;
    }

    lcd_device.lcd->gra_info.width = config->gra_info.width;
    lcd_device.lcd->gra_info.height = config->gra_info.height;
    lcd_device.lcd->gra_info.pixel_format = RTGRAPHIC_PIXEL_FORMAT_RGB565;
    lcd_device.lcd->gra_info.bits_per_pixel = 16;
    lcd_device.lcd->gra_info.framebuffer = RT_NULL;
    lcd_device.lcd->bl_pin = config->bl_pin;

    /* find a interface device */
    lcd_device.lcd->intf = (rt_lcd_intf_t)rt_device_find("lcd_intf");
    if (lcd_device.lcd->intf == RT_NULL)
    {
        LOG_E("can't find device\n");
        return -RT_ERROR;
    }

    if (rt_device_open((rt_device_t)lcd_device.lcd->intf, RT_DEVICE_FLAG_RDWR) != RT_EOK)
    {
        LOG_E("open lcd interface device failed\n");
        return -RT_ERROR;
    }
    /* config interface */
    rt_lcd_config(lcd_device.lcd->intf, &lcd_device.lcd->gra_info);
    rt_pin_mode(lcd_device.lcd->bl_pin, PIN_MODE_OUTPUT);
    /* bl on */
    rt_pin_write(lcd_device.lcd->bl_pin, PIN_HIGH);
    /* set direction */
    _nt5510_display_dir(1);

    device = &(lcd_device.lcd->parent);

#ifdef RT_USING_DEVICE_OPS
    device->ops = &lcd_device_ops;
#else
    device->init = _nt5510_init_display;
    device->open = RT_NULL;
    device->close = RT_NULL;
    device->read  = RT_NULL;
    device->write = RT_NULL;
    device->control = _nt5510_control;
#endif /* RT_USING_DEVICE_OPS */

    device->type         = RT_Device_Class_Graphic;
    device->user_data    = &_nt5510_ops;
    /* register lcd device */
    result = rt_device_register(device, name, RT_DEVICE_FLAG_STANDALONE);

    if (result != RT_EOK)
    {
        LOG_E("register lcd device failed\n");
        return -RT_ERROR;
    }

    return result;
}

#enfif /* PKG_USING_NT5510 */

/*************** end of file ********/
