/* ST-LAB (ESP32) - Example Code
 LAB01 : Blink LED
*/
#define LED_PIN 2 // Built-in LED (ESP32) หรือ ESP32 บางรุ่นอยู่ที่ IO 1
void setup() { // ฟังก์ชันเริ่มต้น ทำงานครั้งเดียวเมื่อบอร์ดเริ่มทำงาน
pinMode(LED_PIN, OUTPUT); // กำหนดโหมดการทำงานของขา GPIO
} // ขอบเขตบล็อกคำสั่ง
void loop() { // ฟังก์ชันหลัก ทำงานวนซ้ำตลอดเวลา
digitalWrite(LED_PIN, HIGH); // สั่งให้ขา GPIO ออกค่า HIGH/LOW
delay(500); // หน่วงเวลา (มิลลิวินาที)
digitalWrite(LED_PIN, LOW); // สั่งให้ขา GPIO ออกค่า HIGH/LOW
delay( 500 ); // หน่วงเวลา (มิลลิวินาที)
} // ขอบเขตบล็อกคำสั่ง