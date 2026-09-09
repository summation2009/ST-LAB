/*
  ST-LAB v2.0 (ESP32) - Example Code (Thai Commented)  // คำสั่ง/การตั้งค่าในโปรแกรม
  หมายเหตุ:  // คำสั่ง/การตั้งค่าในโปรแกรม
  - กรุณาแก้ค่า WiFi / Broker / Server ให้ตรงกับหน้างานก่อนใช้งานจริง  // คำสั่ง/การตั้งค่าในโปรแกรม
  - ผังขา (GPIO) ยึดตามสเปกที่ล็อกไว้ในเอกสารประกอบการสอน  // คำสั่ง/การตั้งค่าในโปรแกรม
*/


#include <Wire.h>  // เรียกใช้งานไลบรารีที่จำเป็น
#include <Adafruit_GFX.h>  // เรียกใช้งานไลบรารีที่จำเป็น
#include <Adafruit_SSD1306.h>  // เรียกใช้งานไลบรารีที่จำเป็น

#define I2C_SDA 21  // กำหนดค่าคงที่/ชื่อพินเพื่อใช้งานสะดวก
#define I2C_SCL 22  // กำหนดค่าคงที่/ชื่อพินเพื่อใช้งานสะดวก
#define OLED_ADDR 0x3C  // กำหนดค่าคงที่/ชื่อพินเพื่อใช้งานสะดวก

#define SCREEN_WIDTH 128  // กำหนดค่าคงที่/ชื่อพินเพื่อใช้งานสะดวก
#define SCREEN_HEIGHT 64  // กำหนดค่าคงที่/ชื่อพินเพื่อใช้งานสะดวก

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);  // คำสั่ง/การตั้งค่าในโปรแกรม

void setup() {  // ฟังก์ชันเริ่มต้น ทำงานครั้งเดียวเมื่อบอร์ดเริ่มทำงาน
  Serial.begin(115200);  // เริ่มต้นพอร์ต Serial สำหรับดีบัก
  Wire.begin(I2C_SDA, I2C_SCL);  // เริ่มต้นบัส I2C ด้วยขา SDA/SCL ที่กำหนด

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {  // สั่งงานจอ OLED ผ่านไลบรารี
    Serial.println("SSD1306 init failed!");  // คำสั่ง/การตั้งค่าในโปรแกรม
    while (true) delay(100);  // หน่วงเวลา (มิลลิวินาที)
  }  // ขอบเขตบล็อกคำสั่ง

  display.clearDisplay();  // สั่งงานจอ OLED ผ่านไลบรารี
  display.setTextSize(1);  // สั่งงานจอ OLED ผ่านไลบรารี
  display.setTextColor(SSD1306_WHITE);  // สั่งงานจอ OLED ผ่านไลบรารี

  display.setCursor(0, 0);  // สั่งงานจอ OLED ผ่านไลบรารี
  display.println("ST-LAB v2.0");  // สั่งงานจอ OLED ผ่านไลบรารี
  display.println("OLED 128x64 (0x3C)");  // สั่งงานจอ OLED ผ่านไลบรารี
  display.display();  // สั่งงานจอ OLED ผ่านไลบรารี
}  // ขอบเขตบล็อกคำสั่ง

void loop() {  // ฟังก์ชันหลัก ทำงานวนซ้ำตลอดเวลา
  static int counter = 0;  // คำสั่ง/การตั้งค่าในโปรแกรม

  display.clearDisplay();  // สั่งงานจอ OLED ผ่านไลบรารี
  display.setCursor(0, 0);  // สั่งงานจอ OLED ผ่านไลบรารี
  display.println("OLED Demo");  // สั่งงานจอ OLED ผ่านไลบรารี
  display.print("Counter: ");  // สั่งงานจอ OLED ผ่านไลบรารี
  display.println(counter++);  // สั่งงานจอ OLED ผ่านไลบรารี
  display.display();  // สั่งงานจอ OLED ผ่านไลบรารี

  delay(300);  // หน่วงเวลา (มิลลิวินาที)
}  // ขอบเขตบล็อกคำสั่ง
