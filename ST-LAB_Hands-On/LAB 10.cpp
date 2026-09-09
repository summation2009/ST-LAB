/* ST-LAB (ESP32) - Example Code
 LAB10 : MAX7219 4DIG
*/
#include <LedControl.h> // ไลบรารีควบคุม MAX7219 (7-segment/LED matrix)
#include <DHT.h> // ไลบรารีสำหรับเซนเซอร์ DHT11/DHT22

#define MAX_DIN 23 // ขา Data In (DIN) ของ MAX7219
#define MAX_LOAD 5 // ขา LOAD/CS ของ MAX7219
#define MAX_CLK 18 // ขา Clock (CLK) ของ MAX7219
#define DHT_PIN 32 // ขา GPIO ที่ต่อกับ DHT11
#define DHT_TYPE DHT11 // กำหนดชนิดเซนเซอร์เป็น DHT11
DHT dht(DHT_PIN, DHT_TYPE); // สร้างอ็อบเจกต์สำหรับควบคุม DHT11
LedControl lc = LedControl(MAX_DIN, MAX_CLK, MAX_LOAD, 1);

// สร้างอ็อบเจกต์ควบคุม MAX7219 (ใช้งาน 1 โมดูล)
static const byte SEG_A = 0x01; // บิตควบคุม segment จุดที่ 1
static const byte SEG_B = 0x02; // บิตควบคุม segment จุดที่ 2
static const byte SEG_C = 0x04; // บิตควบคุม segment จุดที่ 3

// กำหนดโหมดการทำงานของจอแสดงผล
enum Mode
{
MODE_NUMBER = 0, // โหมดแสดงตัวเลขนับเพิ่ม
MODE_CLOCK = 1, // โหมดแสดงเวลา (HHMM)
MODE_TEMP = 2 // โหมดแสดงอุณหภูมิ
};

void setup()
{
Serial.begin(115200); // เปิดใช้งาน Serial Monitor
dht.begin(); // เริ่มต้นการทำงานของ DHT11
lc.shutdown(0, false); // ปลุก MAX7219 ให้ออกจากโหมดประหยัดพลังงาน
lc.setIntensity(0, 8); // ตั้งค่าความสว่างระดับ 0–15
lc.clearDisplay(0); // ล้างหน้าจอแสดงผล
Serial.println("LAB10: MAX7219 Started");
}
// แสดงตัวเลข 4 หลัก (0000–9999)
void show4DigitNumber(int value)
{
value = constrain(value, 0, 9999); // จำกัดค่าไม่ให้เกินช่วงที่แสดงได้
int d0 = (value / 1000) % 10; // หลักพัน
int d1 = (value / 100) % 10; // หลักร้อย
int d2 = (value / 10) % 10; // หลักสิบ
int d3 = value % 10; // หลักหน่วย
lc.setDigit(0, 0, d0, false); // แสดงหลักพัน
lc.setDigit(0, 1, d1, false); // แสดงหลักร้อย
lc.setDigit(0, 2, d2, false); // แสดงหลักสิบ
lc.setDigit(0, 3, d3, false); // แสดงหลักหน่วย
}
// ควบคุมการแสดง ":" ระหว่างเวลา
void setColon(bool on)
{
byte seg = on ? (SEG_A | SEG_B) : 0x00;
// ถ้า on = true → เปิด segment A และ B
lc.setRow(0, 4, seg);
// ส่งข้อมูลไปยังตำแหน่ง row 4 (ตำแหน่งจุดพิเศษ)
}

// ควบคุมการแสดงจุด ° สำหรับอุณหภูมิ
void setDegreeDot(bool on)
{
byte seg = on ? SEG_C : 0x00;
// ถ้า on = true → เปิด segment C
lc.setRow(0, 4, seg);
// ส่งข้อมูลไปยังตำแหน่ง row 4
}
void loop()
{
static unsigned long lastSwitch = 0; // เก็บเวลาเปลี่ยนโหมดล่าสุด
// เปลี่ยนโหมดทุก 10 วินาที
if (millis() - lastSwitch > 10000)
{
lastSwitch = millis(); // บันทึกเวลาใหม่
mode = (Mode)((mode + 1) % 3); // วนโหมด 0→1→2→0
lc.clearDisplay(0); // ล้างหน้าจอเมื่อเปลี่ยนโหมด
}
// ================= MODE 1: นับเลข =================
if (mode == MODE_NUMBER)
{
static int n = 0; // ตัวเลขนับเพิ่ม
show4DigitNumber(n); // แสดงค่า
setColon(false); // ปิด colon
n = (n + 1) % 10000; // เพิ่มค่าและวนกลับที่ 10000
delay(50);
}

// ================= MODE 2: นาฬิกา =================
else if (mode == MODE_CLOCK)
{
static int hh = 12, mm = 0; // เวลาเริ่มต้น 12:00
static unsigned long lastTick = 0; // เก็บเวลาอัปเดตล่าสุด
if (millis() - lastTick >= 1000)
{ // ทุก 1 วินาที
lastTick += 1000;
mm++; // เพิ่มนาที
if (mm >= 60)
{
mm = 0;
hh = (hh + 1) % 24; // ชั่วโมงวน 0–23
}
}
int value = (hh * 100) + mm; // รวมเป็นรูปแบบ HHMM
show4DigitNumber(value);
setColon((millis() / 500) % 2); // กระพริบ colon ทุก 0.5 วิ
delay(20);
}

// ================= MODE 3: อุณหภูมิ =================
else if (mode == MODE_TEMP)
{
float t = dht.readTemperature(); // อ่านค่าอุณหภูมิ (°C)
if (isnan(t))
{ // ถ้าอ่านค่าไม่ได้
show4DigitNumber(0);
setDegreeDot(false);
delay(500);
return;
}
int ti = (int)(t * 10.0f); // คูณ 10 เพื่อแสดงทศนิยม 1 ตำแหน่ง
show4DigitNumber(ti);
setDegreeDot(true); // เปิดจุดแสดง °C
delay(500);
}
}