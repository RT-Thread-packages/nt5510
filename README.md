# NT5510

## 简介

nt5510 软件包提供了使用液晶显示的基本功能，并且本软件包已经对接到了 LCD 框架，通过 LCD 框架，开发者可以快速的将此液晶芯片驱动起来。
## 支持情况

| 包含设备           | 液晶芯片 |  
| ----------------     | -------- | 
| **通讯接口**      |          |      
| 8080 并口              | √        | 
      

## 使用说明

### 依赖

- RT-Thread 4.0.0+
- LCD 组件
- LCD 接口驱动：nt5510 设备使用 LCD 接口设备进行数据通讯，需要系统 LCD 接口驱动支持；

### 获取软件包

使用 nt5510 软件包需要在 RT-Thread 的包管理中选中它，具体路径如下：

```
RT-Thread online packages  --->
  peripheral libraries and drivers  --->
    lcd drivers  --->
      nt5510: lcd ic nt5510 for rt-thread
              Version (latest)  --->
```
**Version**：软件包版本选择

### 使用软件包

nt5510 软件包初始化函数如下所示：

```
int rt_hw_nt5510_init(struct rt_lcd_config *config, const char *name)
```

该函数需要由用户调用，函数主要完成的功能有，

- 设备配置和初始化（根据传入的配置信息，配置接口设备）；
- 注册相应的 LCD 设备，完成 nt5510 设备的注册；

#### 初始化示例

```.c
int rt_hw_nt5510_port(void)
{
  struct rt_lcd_config config;

  config.gra_info.bits_per_pixel = 16;
  config.gra_info.framebuffer = RT_NULL;
  config.gra_info.height = 800;
  config.gra_info.width = 480;
  config.gra_info.pixel_format = RTGRAPHIC_PIXEL_FORMAT_RGB565;

  config.hw_info.bl_pin = 21;
  config.hw_info.bl_type = RT_LCD_BACKLIGHT_TYPE_PIN;
  config.hw_info.dir = RT_LCD_DIRECTION_VERTIAL;
  config.hw_info.lcd_type = RT_LCD_DISPLAT_TYPE_PIXEL;
  config.dev_name = "lcd_intf";

  rt_hw_nt5510_init(&config, "lcd");

  return 0;
}
INIT_ENV_EXPORT(rt_hw_nt5510_port);
```

## 注意事项

暂无

## 联系人信息

维护人:

- [tyustli](https://github.com/tyustli) 

- 主页：<https://github.com/tyustli/nt5510>