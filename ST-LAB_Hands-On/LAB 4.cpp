/* ST-LAB (ESP32) - Example Code
 LAB04 : Potentiometer/ADC
*/
#include <Arduino.h> // รวมไลบรารีหลักของ Arduino สำหรับใช้งานฟังก์ชันพื้นฐาน
#define POT_PIN 35 // กำหนดขา GPIO35 สำหรับอ่านค่า ADC จาก Potentiometer
#define LED_PIN 2 // กำหนดขา GPIO2 สำหรับควบคุม LED

void setup()
{ // ทำงานครั้งเดียวเมื่อเปิดเครื่องหรือรีเซตบอร์ด
Serial.begin(115200); // เริ่มต้นการสื่อสาร Serial ที่ความเร็ว 115200 bps
pinMode(LED_PIN, OUTPUT); // ตั้งค่า LED_PIN เป็นขาเอาต์พุต
// ตั้งความละเอียด ADC (ESP32 ค่าเริ่มต้นคือ 12 บิต = 0–4095)
analogReadResolution(12); // กำหนดให้ ADC อ่านค่าแบบ 12-bit
Serial.println("LAB04: Potentiometer ADC Started"); // แสดงข้อความเริ่มต้นบน Serial Monitor
} // จบฟังก์ชัน setup()

void loop()
{ // ทำงานวนซ้ำตลอดเวลาที่บอร์ดยังทำงานอยู่
int v = analogRead(POT_PIN); // อ่านค่าแรงดันจาก POT (ช่วงค่า 0–4095)
float percent = (v / 4095.0f) * 100.0f; // แปลงค่าที่อ่านได้เป็นเปอร์เซ็นต์ (0–100%)
// ถ้าค่ามากกว่า 50% ให้เปิด LED ถ้าน้อยกว่าหรือเท่ากับให้ปิด
digitalWrite(LED_PIN, (percent > 50.0f) ? HIGH : LOW); // ควบคุม LED ตามระดับการหมุนของ POT
Serial.print("POT=");
Serial.print(v); // แสดงค่าดิบที่อ่านได้จาก ADC
Serial.print(" (");
Serial.print(percent, 1); // แสดงค่าเปอร์เซ็นต์ทศนิยม 1 ตำแหน่ง
Serial.println("%)"); // แสดงเครื่องหมาย % และขึ้นบรรทัดใหม่
delay(200); // หน่วงเวลา 200 ms เพื่อลดความถี่ในการอ่านค่าและแสดงผล
} // จบฟังก์ชัน loop()