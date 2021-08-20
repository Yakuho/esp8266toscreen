本项目是使用esp8266驱动点亮微雪家的2.13寸墨水屏代码教程 (有更新的话会持续更新)

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
  
</details>

<details open>
<summary>5. 选择开发板</summary>

  - 依次点击 工具 -> 开发板 -> Generic ESP8266 Module
  - 依次点击 工具 -> 开发板 -> Upload Speed -> 115200
  - 依次点击 工具 -> 开发板 -> Flash Mode -> QIO
  - 依次点击 工具 -> 开发板 -> Flash Frequency -> 40MHz
  - 依次点击 工具 -> 开发板 -> Erase Flash -> Only Sketch
  - 依次点击 工具 -> 开发板 -> 端口 -> 在第2步查看到的那个端口
  
</details>

6. 开始编程
