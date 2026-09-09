/* ST-LAB (ESP32) - Example Code
LAB08 : OLED 128x64 (0x3C)
*/
#include <Wire.h> // เรียกใช้งานไลบรารีที่จำเป็น
#include <Adafruit_GFX.h> // เรียกใช้งานไลบรารีที่จำเป็น
#include <Adafruit_SSD1306.h> // เรียกใช้งานไลบรารีที่จำเป็น

#define I2C_SDA 21 // กำหนดค่าคงที่/ชื่อพินเพื่อใช้งานสะดวก
#define I2C_SCL 22 // กำหนดค่าคงที่/ชื่อพินเพื่อใช้งานสะดวก
#define OLED_ADDR 0x3C // กำหนดค่าคงที่/ชื่อพินเพื่อใช้งานสะดวก
#define SCREEN_WIDTH 128 // กำหนดค่าคงที่/ชื่อพินเพื่อใช้งานสะดวก
#define SCREEN_HEIGHT 64 // กำหนดค่าคงที่/ชื่อพินเพื่อใช้งานสะดวก
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // คำสั่ง/การตั้งค่าในโปรแกรม

void setup()
{ // ทำงานครั้งเดียวเมื่อเปิดเครื่องหรือรีเซตบอร์ด
Serial.begin(115200); // เริ่มต้นการสื่อสาร Serial ที่ความเร็ว 115200 bps
Wire.begin(I2C_SDA, I2C_SCL); // เริ่มต้นบัส I2C โดยกำหนดขา SDA และ SCL
if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR))
{
// เริ่มต้นจอ OLED และตรวจสอบว่าเชื่อมต่อสำเร็จหรือไม่
Serial.println("SSD1306 init failed!"); // แสดงข้อความแจ้งเตือนหากเริ่มต้นไม่สำเร็จ
while (true)
delay(100); // หยุดโปรแกรมไว้ตรงนี้หากจอไม่ทำงาน
}
display.clearDisplay(); // ล้างข้อมูลทั้งหมดในบัฟเฟอร์หน้าจอ
display.setTextSize(1); // กำหนดขนาดตัวอักษร (1 = ขนาดปกติ)
display.setTextColor(SSD1306_WHITE); // กำหนดสีตัวอักษรเป็นสีขาว
display.setCursor(0, 0); // ตั้งตำแหน่งเริ่มพิมพ์ที่พิกเซล (0,0)
display.println("ST-LAB v2.0"); // แสดงข้อความบรรทัดแรก
display.println("OLED 128x64 (0x3C)"); // แสดงข้อความบรรทัดที่สอง
display.display(); // ส่งข้อมูลจากบัฟเฟอร์ไปแสดงผลจริงบนจอ
} // จบฟังก์ชัน setup()

void loop()
{ // ทำงานวนซ้ำตลอดเวลาที่บอร์ดยังเปิดอยู่
static int counter = 0; // ตัวแปรนับค่า และเก็บค่าไว้แม้ loop() จะวนใหม่
display.clearDisplay(); // ล้างหน้าจอในบัฟเฟอร์ก่อนวาดข้อมูลใหม่
display.setCursor(0, 0); // ตั้งตำแหน่งเริ่มพิมพ์ที่มุมซ้ายบน
display.println("OLED Demo"); // แสดงหัวข้อ
display.print("Counter: "); // แสดงข้อความนำหน้า
display.println(counter++); // แสดงค่าตัวนับ แล้วเพิ่มค่า 1
display.display(); // อัปเดตข้อมูลทั้งหมดไปยังหน้าจอ OLED
delay(300); // หน่วงเวลา 300 ms ก่อนอัปเดตค่าครั้งถัดไป
} // จบฟังก์ชัน loop()