本项目是使用esp8266驱动点亮微雪家的2.13寸墨水屏代码教程 (有更新的话会持续更新)

# 目录简介

<details>
<summary>source: 源代码文件分布</summary>

- font(8,12,16,20,24): 字体格式文件;数字代表字体大小
- epdpaint: 画布文件;矩形、线段、圆等绘图函数
- epdif: 引脚定义
- imagedata: 存放图片矩阵
- epd2in13_V2: 控制命令
  
</details>

# 前期物品准备

<details open>
<summary>需要准备的硬件物品</summary>

- esp8266板子(屏幕24排线)
- 24排线墨水屏
- 老式安卓数据线

</details>

<details open>
<summary>需要准备的软件以及代码</summary>

- Arduino IDE

</details>


# 环境搭建

下面我们一起开始从零开始吧

1. 拿出一块esp8266板子插上老式安卓数据线至电脑USB插口

<details>
<summary>2. 打开电脑设备管理器，查看端口(COM和LPT)是否有设备，并记录下来</summary>

  - 寻找 端口(COM和LPT) 看是否被识别出端口如:-> USB-SERIAL CH340(COM4)
  - 若电脑无法识别该端口，上搜索平台下载CH340驱动，安装以后基本上就能检测出端口了
  - 出现设备如上述USB-SERIAL CH340(COM4)即可进行下一步
  - 如果实在不行检查一下板子是不是烧了 (●'◡'●)
  
</details>

<details open>
<summary>3. 打开Arduino IDE</summary>

  - 依次点击 文件 -> 首选项 -> 找到附加开发板管理器网站
  - 输入网址 http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - 依次点击 工具 -> 开发板 -> 开发板管理器 -> 搜索esp -> 安装
  
</details>

<details>
<summary>4. 开发板定义文件安装完成</summary>

  - 在安装中有可能因为科学原因，下载失败等信息报错了使用科学方式重试
  - 重试还是不行以后，找到Arduino IDE下方的调试台，将调试文件翻上去顶上，找到文件地址手动下载
  - 从Arduino IDE依次点击 文件 -> 首选项 从下方找到文件路径如 C:\Users\Yakuho\AppData\Local\Arduino15
  - 将下载的压缩包放至 C:\Users\Yakuho\AppData\Local\Arduino15\staging\packages 目录下
  - 重启Arduino IDE
  - 因为要下载多个安装包，后面出现下载失败，仍然手动下载，放在目录中直到全部下载完毕
  - 进行安装并无报错说明成功
  
</details>

<details open>
<summary>5. 选择开发板</summary>

  - 依次点击 工具 -> 开发板 -> Generic ESP8266 Module
  - 依次点击 工具 -> 开发板 -> Upload Speed -> 115200  (按照板子参数进行设置, 一般都是115200这个波特率)
  - 依次点击 工具 -> 开发板 -> Flash Mode -> QIO
  - 依次点击 工具 -> 开发板 -> Flash Frequency -> 40MHz
  - 依次点击 工具 -> 开发板 -> Erase Flash -> Only Sketch
  - 依次点击 工具 -> 开发板 -> 端口 -> 在第2步查看到的那个端口
  
</details>

# 开始编程
以下编程都是基于Arduino IDE上进行, 该分支仅是要求点亮屏幕

1. 在原代码目录下新建一个Ariduino文件 ****.ino
<details>
<summary>2. 导入头文件</summary>

```c
#include <SPI.h>
#include "epd2in13_V2.h"
#include "epdpaint.h"
Epd epd;
```
  
</details>

<details>
<summary>3. 选择一块区域进行编程</summary>

```c
void setup()
{
  // 此区域在硬件中只执行一次
}

void loop()
{
  // 此区域在硬件中会重复执行
}
```

</details>

  
<details>
<summary>4. 程序猿老规矩 打印一下hello world</summary>

```c
#include <SPI.h>
#include "epd2in13_V2.h"
#include "epdpaint.h"
Epd epd;


void setup()
{
  Serial.begin(115200);   // 开启串行通信接口并设置通信波特率, 与环境搭建5. 开发板选择中的Upload Speed一致
  epd.Clear();            // 屏幕情况
  epd.Init(FULL);         // 屏幕刷新 FULL全屏 PART部分
  int all_pixel = 104 * 212 / 8;   // 定义画布大小
  unsigned char image[all_pixel];  // 定义画布矩阵
  for (int i = 0; i < all_pixel; i++) {
    image[i] = 0Xff;       // 初始化画布矩阵 亮度为255=0xff
  }
  Paint paint(image, 104, 212);   // 初始化画布对象  width should be the multiple of 8
  paint.SetRotate(3);             // 设置画布旋转角度
  paint.DrawStringAt(0, 0, "Hello world", &Font20, 0);  // 输出字符串
  char s, e;
  for (int x = 0; x < paint.GetWidth() / 8; x++) {          // 将矩阵与输出相匹配 否则会出现字体反转
    for (int y = 0; y < paint.GetHeight() / 2; y++) {
        s = image[x + y * paint.GetWidth() / 8];
        e = image[x + (paint.GetHeight() - 1 - y) * paint.GetWidth() / 8];
        image[x + y * paint.GetWidth() / 8] = e;
        image[x + (paint.GetHeight() - 1 - y) * paint.GetWidth() / 8] = s;
    }
  }
  epd.Display(image);
}

void loop()
{
  // 此区域在硬件中会重复执行
}
```

</details>

<details>
<summary>5. 找到Arduino IDE 依次点击 项目 -> 上传, 观察下方控制台 安静等待 (ง •_•)ง</summary>

```
项目使用了 272753 字节，占用了 (28%) 程序存储空间。最大为 958448 字节。
全局变量使用了28272字节，(34%)的动态内存，余留53648字节局部变量。最大为81920字节。
esptool.py v3.0
Serial port COM3
Connecting....
Chip is ESP8266EX
Features: WiFi
Crystal is 26MHz
MAC: 3c:71:bf:39:0a:28
Uploading stub...
Running stub...
Stub running...
Configuring flash size...
Auto-detected Flash size: 4MB
Flash params set to 0x0040
Compressed 276912 bytes to 201576...
Writing at 0x00000000... (7 %)
Writing at 0x00004000... (15 %)
Writing at 0x00008000... (23 %)
Writing at 0x0000c000... (30 %)
Writing at 0x00010000... (38 %)
Writing at 0x00014000... (46 %)
Writing at 0x00018000... (53 %)
Writing at 0x0001c000... (61 %)
Writing at 0x00020000... (69 %)
Writing at 0x00024000... (76 %)
Writing at 0x00028000... (84 %)
Writing at 0x0002c000... (92 %)
Writing at 0x00030000... (100 %)
Wrote 276912 bytes (201576 compressed) at 0x00000000 in 17.8 seconds (effective 124.5 kbit/s)...
Hash of data verified.

Leaving...
Hard resetting via RTS pin...
```
  
</details>

6. 若发现屏幕闪烁并输出 "Hello world", 说明你成功入门了 (●'◡'●)
  
# 更多函数详细介绍
<details>
<summary>屏幕的输出方向</summary>

  不知道你是否注意到在 "Hello world" 代码中, 设置了一个屏幕方向代码如: 
  ```c
  paint.SetRotate(3);
  ```
  这是可以让屏幕旋转90°的函数, 并让坐标原点函数也会相应跟着旋转, 下面是图像方向与坐标原点之间的关系

</details>
