/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-07-01     tyustli     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define LCD_DEVICE_NAME  "lcd"

int nt5510_sample(void)
{
    struct rt_lcd_device *lcd;
    struct rt_device_graphic_ops *test_ops;
    rt_uint32_t color;

    lcd = (struct rt_lcd_device *)rt_device_find(LCD_DEVICE_NAME);
    if (lcd == RT_NULL)
    {
        rt_kprintf("find a lcd device failed \n");
        return -RT_ERROR;
    }
    rt_kprintf("%d %d\r\n", lcd->gra_info.width, lcd->gra_info.height);

    test_ops = lcd->parent.user_data;
    color = 0x1234; /* random num*/
    test_ops->set_pixel((const char *)&color, 211, 322);
    test_ops->get_pixel((char *)&color, 211, 322);

    if (color == 0x1234)
    {
        rt_kprintf("test set/get pixel success pixel = %x\n", color);
    }
    else
    {
        rt_kprintf("test set/get pixel failed read pixel = %x\n", color);
    }

    color = 0xF800;   /* red */
    test_ops->draw_hline((const char *)&color, 100, 240, 200);
    color = 0x07E0;   /* green */
    test_ops->draw_vline((const char *)&color, 100, 200, 400);
    color = 0xFFE0;   
    test_ops->blit_line((const char *)&color, 200, 200, 100);

    return RT_EOK;

}

MSH_CMD_EXPORT(nt5510_sample, nt5510 sample);

/******************* end of file **************************/
