/**
 *  @filename   :   epdif.h
 *  @brief      :   Header file of epdif.cpp providing EPD interface functions
 *                  Users have to implement all the functions in epdif.cpp
 *  @author     :   Yehui from Waveshare
 *
 *  Copyright (C) Waveshare     August 10 2017
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documnetation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to  whom the Software is
 * furished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef EPDIF_H
#define EPDIF_H

#include <arduino.h>

//在NodeMCU上的引脚连接方法：
// Pin definition on NodeMCU
//  RST<---> D4
//  DC <---> D3
//  CS <---> D8
// BUSY<---> D2
// SDA <---> D7
// SCL <---> D5

//直接使用ESP-12E或者ESP-12F模组的连接方法：
// Pin definition on NodeMCU
//  RST<---> GPIO 2
//  DC <---> GPIO 0
//  CS <---> GPIO 15
// BUSY<---> GPIO 4
// SDA <---> GPIO 13
// SCL <---> GPIO 14

//注意：以上引脚连接方式是经过各种尝试优化的结果。不建议修改。

//首先：ESP8266的模组ESP-12E/F，以及NodeMCU上，GPIO 0,2,15和启动功能密切相关，用这三个引脚来驱动墨水屏的DC，RST和CS，不会影响启动。
//市场上有一些比较廉价的NodeMCU开发板，偷工减料，没有GPIO15没有采用10k电阻来下拉，而是直接接地。这样的电路会导致GPIO15在驱动CS引脚的时候可能烧坏开发板。
//请特别注意识别GPIO 0,2,15是否采用电阻上拉或者下拉（GPIO2可能是悬空的，因为内部已经有上拉电阻），没有直接连接VCC或者GND的情况存在，以防烧坏和火灾。
//如果是自己购买的ESP-12E/F模块，也请注意这三个引脚的上下拉情况。严禁不经过上下拉电阻，直接连接VCC或者GND。

//第二：GPIO 13和GPIO 14连接SDA和SCL，是直接用ESP8266的SPI硬件接口驱动的，速率很快。如果选用别的引脚，需要采用SoftwareSPI，速度会慢一些。本程序没有适配Software SPI。

//第三：BUSY引脚可以选择GPIO 4或者GPIO 5来驱动。

#define RST_PIN         2//D4 
#define DC_PIN          0//D3 
#define CS_PIN          15//D8 
#define BUSY_PIN        4//D2 
//注意：SDA和SCL引脚无需define，因为在SPI.h中已经定义过了

class EpdIf {
public:
    EpdIf(void);
    ~EpdIf(void);

    static int  IfInit(void);
    static void DigitalWrite(int pin, int value); 
    static int  DigitalRead(int pin);
    static void DelayMs(unsigned int delaytime);
    static void SpiTransfer(unsigned char data);
};

#endif
