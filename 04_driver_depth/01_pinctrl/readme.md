# pinctrl

## pinctrl的作用
1. 引脚的枚举与命名
2. 引脚功能复用
    要让引脚用于GPIO，需要设置IOMUX让它们连接到GPIO
    要让引脚用于I2C，需要设置IOMUX让它们连接到I2C
3. 引脚的配置（上下拉，输入/输出，驱动强度，推挽/开漏）

## pinctrl的概念
因为很多芯片的GPIO里面就实现了对引脚的功能复用/引脚配置，所以需要我们将IOMUX抽象出来，所以pinctrl更像是一个软件的概念

## pinctrl的重要结构体
```c
//pinctrl_desc
struct pinctrl_desc {
	const char *name;                   // 控制器名称（标识符）
	const struct pinctrl_pin_desc *pins;// 引脚描述数组
	unsigned int npins;                 // 引脚数量
	const struct pinctrl_ops *pctlops;  // 控制器级操作函数集
	const struct pinmux_ops *pmxops;    // 引脚复用操作函数集
	const struct pinconf_ops *confops;  // 引脚配置操作函数集
	struct module *owner;               // 拥有者设备（通常为 THIS_MODULE）
#ifdef CONFIG_GENERIC_PINCONF
	unsigned int num_custom_params;
	const struct pinconf_generic_params *custom_params;
	const struct pin_config_item *custom_conf_items;
#endif
};

//pinctrl_pin_desc
struct pinctrl_pin_desc {
    unsigned number;           // 引脚的硬件编号（唯一标识）
    const char *name;          // 引脚的名称（可读字符串）
};

## pinctrl的调用过程

## 举例
```shell
pincontroller {
    state_0_node_a = {
        function = "uart0";             //复用功能
        groups = "u0rxtx", "u0rtscts";  //用到哪些引脚
    };
    state_1_node_a = {
        function = "gpio";
        groups = "u0rxtx", "u0rtscts";
    };
}

device {
    pinctrl-names = "default", "sleep"; //设备有两个状态
    pinctrl-0 = <&state0_node>;         //状态0
    pinctrl-1 = <&state1_node>;         //状态1
};
```