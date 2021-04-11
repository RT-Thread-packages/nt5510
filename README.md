# NT5510

## 简介

nt5510 软件包提供了使用液晶显示的基本功能，并且本软件包已经对接到了 LCD 接口框架，通过 LCD 接口框架，开发者可以快速的将此液晶芯片驱动起来。
## 支持情况

| 包含设备           | 液晶芯片 |  
| ----------------     | -------- | 
| **通讯接口**      |          |      
| 8080 并口              | √        | 
      

## 使用说明

### 依赖

- RT-Thread 4.0.0+
- LCD 接口组件
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
int rt_hw_nt5510_init(struct rt_lcd_mcu *mcu, void *user_data);
```

该函数需要由用户调用，函数主要完成的功能有，

- 根据已经配置好的 LCD 接口设备来初始化 LCD 显示，并注册相应的 LCD 设备，完成 nt5510 设备的注册；

#### 初始化示例

```.c
#define BL_PIN       21

int rt_hw_nt5510_port(void)
{
    rt_lcd_mcu_t mcu;
    rt_uint16_t bl_pin;

    bl_pin = BL_PIN;
    /* config lcd interface device */
    ......
    rt_lcd_mcu_config(mcu, &mcu->mcu_config);

    /* init and register lcd device*/
    rt_hw_nt5510_init(mcu, &bl_pin);

  return 0;
}
INIT_ENV_EXPORT(rt_hw_nt5510_port);
```

## 注意事项

暂无

## 联系人信息

维护人:

- [tyustli](https://github.com/tyustli) 

- 主页：<https://github.com/RT-Thread-packages/nt5510>