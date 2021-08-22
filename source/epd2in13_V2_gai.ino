#include "epd2in13_V2.h"
#include "imagedata.h"
#include "epdpaint.h"
#include <SPI.h>
Epd epd;  // 初始化操纵屏幕对象

void setup()  // 此区域代码硬件只执行一次
{
  Serial.begin(115200);
  epd.Clear();
  epd.Init(FULL);
  epd.Display(IMAGE_DATA);
  epd.Sleep();
}

void loop()
{

}
